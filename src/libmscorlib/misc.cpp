/******************************************************************************/
/*																              */
/* File: misc.cpp                                                             */
/* Author: bkenwright@xbdev.net                                               */
/* Desc: Misc functions, making our usb/gamepad code lib independent          */
/*                                                                            */
/******************************************************************************/

#include <System/misc.h>
#include <xboxkrnl/xboxkrnl.h>

/******************************************************************************/
/*                                                                            */
/* Debug Function                                                             */
/*                                                                            */
/* Its a simple, but useful function to provide essential feedback during     */
/* the early development stages....especially when your developing an app     */
/* like the ohci-usb :-/                                                      */
/*                                                                            */
/******************************************************************************/

//#include <stdlib.h>
//#include <stdio.h>

//extern void op_txt(char* str); // top of main.cpp

char buf[500];
void dbg(char* str)
{
	//FILE *fp = fopen("d:\\output.txt", "a+");
	//fprintf(fp, "%s", str);
	//fclose(fp);

	//char buffer[500];
	//sprintf(buffer, "%s", str);
	//op_txt(str);
}// End dbg(..)

/******************************************************************************/

// Might want to look into using this kernel api at a later date for xSleep(..)
// extern "C" void __stdcall KeDelayExecutionThread(__u32 a, __u32 b, __u32 c);
void Sleep(long timemilliseconds)
{
	//Sleep(timemilliseconds);

	unsigned long long nowTime = KeTickCount;
	unsigned long long oldTime = KeTickCount;

	while( nowTime < (oldTime + timemilliseconds) )
		nowTime = (int)KeTickCount;
}

#define small_memcpy(dest, src, count)\
{\
	register unsigned long dummy;\
	__asm__ __volatile__(\
	"rep; movsb"\
	:"=&D"(dest), "=&S"(src), "=&c"(dummy)\
	:"0"(dest), "1" (src),"2" (count)\
	: "memory");\
}

void *__memcpy(void *dest, const void *src, size_t count)
{
	int d0, d1, d2;

	if (count < 4)
	{
		small_memcpy(dest, src, count);
	}
	else
		__asm__ __volatile__(
			"rep ; mvsl\n\t"
			"testb $2,%b4\n\t"
			"je 1f\n\t"
			"movsw\n"
			"1:\ttestb $1,%b4\n\t"
			"je 2f\n\t"
			"movsb\n"
			"2:"
			: "=&c" (d0), "=&D" (d1), "=&S" (d2)
			:"0" (count/4), "q" (count),"1" ((long) dest),"2" ((long) src)
			: "memory");
	return dest;
}

void *memcpy(void *dest, const void *src, size_t count)
{
	void *retval;
	size_t i;
	retval = dest;

	/* prefetch has effect, even for movsb instruction */
	__asm__ __volatile__ (
		"prefetchnta (%0)\n"
		"prefetchnta 64(%0)\n"
		"prefetchnta 128(%0)\n"
		"prefetchnta 192(%0)\n"
		"prefetchnta 256(%0)\n"
		: : "r" (src) );

	if(count >= 0x40) 
	{
		register unsigned long delta;
		/* Align destination to 16 - boundary */
		delta = ((unsigned long)dest)&(15);
		if(delta)
		{
			delta = 16 - delta;
			count -= delta;
			small_memcpy(dest, src, delta);
		}
		i = count >> 6; /* count / 64 */
		count &=63;
		if (((unsigned long)src) & 15)
			/* If src is misaligned */
			for (; i > 0; i--)
			{
				__asm__ __volatile__ (
					"prefetchnta 320(%0)\n"
					"movups (%0), %%xmm0\n"
					"movups 16(%0), %%xmm1\n"
					"movups 32(%0), %%xmm2\n"
					"movups 48(%0), %%xmm3\n"
					"movntps %%xmm0, (%1)\n"
					"movntps %%xmm1, 16(%1)\n"
					"movntps %%xmm2, 32(%1)\n"
					"movntps %%xmm3, 48(%1)\n"
					:: "r" (src), "r" (dest) : "memory");
				src = ((const unsigned char *)src)+64;
				dest = ((unsigned char*)dest)+64;
			}
		else
			/*  Only if src is aligned on 16-byte boundary.
				It allows to use movaps instead of movups, which required
				data to be aligned or a general protection exception (#GP)
				is generated.
			*/
			for (; i > 0; i--)
			{
				__asm__ __volatile__ (
					"prefetchnta 320(%0)\n"
					"movaps (%0), %%xmm0\n"
					"movaps 16(%0), %%xmm1\n"
					"movaps 32(%0), %%xmm2\n"
					"movaps 48(%0), %%xmm3\n"
					"movntps %%xmm0, (%1)\n"
					"movntps %%xmm1, 16(%1)\n"
					"movntps %%xmm2, 32(%1)\n"
					"movntps %%xmm3, 48(%1)\n"
					:: "r" (src), "r" (dest) : "memory");
				src = ((const unsigned char *)src)+64;
				dest = ((unsigned char*)dest)+64;
			}
			/*  since movntq is weakly-ordered, a "sfence"
			 *	is needed to become aligned again. */
			__asm__ __volatile__ ("sfence":::"memory");
			/* enables to use FPU */
			__asm__ __volatile__ ("ems":::"memory");
	}
	/* Now, do the tail of the block */
	if (count) __memcpy(dest, src, count);
	return retval;
}

void *malloc(size_t size)
{
	return (void*)MmAllocateContiguousMemory(size);
}

void *memset(void *s, char c, size_t count)
{
	int d0, d1;
	__asm__ __volatile__(
			"rep\n\t"
			"stosb"
			: "=&c" (d0), "=&D" (d1)
			:"a" (c),"1" (s),"0" (count)
			:"memory");
	return s;
}
