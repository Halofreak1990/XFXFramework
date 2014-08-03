/*****************************************************************************
 *	intrin.h																 *
 *																			 *
 *		Copyright (c) XFX Team. All rights reserved.						 *
 *																			 *
 *	Purpose:																 *
 *		This include file contains the declarations for x86-specific		 *
 *		intrinsic functions.												 *
 *																			 *
 *	Original code by ReactOS project (http://www.reactos.org/)  			 *
 *****************************************************************************/
#ifndef _INTRIN_H
#define _INTRIN_H

#if _MSC_VER
#  define __INTRIN_INLINE   extern __inline
#elif __GNUC__
#  define __ATTRIBUTE_ARTIFICIAL   __attribute__((artificial))
#  define __INTRIN_INLINE   extern __inline__ __attribute__((__always_inline__,__gnu_inline__)) __ATTRIBUTE_ARTIFICIAL
#else
#  pragma error "Unsupported Compiler"
#endif

#include <stddef.h>
#include <stdint.h>

__INTRIN_INLINE void _mm_lfence(void);
__INTRIN_INLINE void _mm_sfence(void);
__INTRIN_INLINE void _ReadWriteBarrier(void);
__INTRIN_INLINE char _InterlockedCompareExchange8(volatile char *const Destination, const char Exchange, const char Comperand);
__INTRIN_INLINE short _InterlockedCompareExchange16(volatile short *const Destination, const short Exchange, const short Comperand);
__INTRIN_INLINE long _InterlockedCompareExchange(volatile long *const Destination, const long Exchange, const long Comperand);
__INTRIN_INLINE void * _InterlockedCompareExchangePointer(void *volatile *const Destination, void *const Exchange, void *const Comperand);
__INTRIN_INLINE long _InterlockedExchange(volatile long *const Target, const long Value);
__INTRIN_INLINE void * _InterlockedExchangePointer(void *volatile *const Target, void *const Value);
__INTRIN_INLINE short _InterlockedExchangeAdd16(volatile short *const Addend, const short Value);
__INTRIN_INLINE long _InterlockedExchangeAdd(volatile long *const Addend, const long Value);
__INTRIN_INLINE char _InterlockedAnd8(volatile char *const value, const char mask);
__INTRIN_INLINE short _InterlockedAnd16(volatile short *const value, const short mask);
__INTRIN_INLINE long _InterlockedAnd(volatile long *const value, const long mask);
__INTRIN_INLINE char _InterlockedOr8(volatile char *const value, const char mask);
__INTRIN_INLINE short _InterlockedOr16(volatile short *const value, const short mask);
__INTRIN_INLINE long _InterlockedOr(volatile long *const value, const long mask);
__INTRIN_INLINE char _InterlockedXor8(volatile char *const value, const char mask);
__INTRIN_INLINE short _InterlockedXor16(volatile short *const value, const short mask);
__INTRIN_INLINE long _InterlockedXor(volatile long *const value, const long mask);
__INTRIN_INLINE long long _InterlockedCompareExchange64(volatile long long *const Destination, const long long Exchange, const long long Comperand);
__INTRIN_INLINE long _InterlockedAddLargeStatistic(volatile long long *const Addend, const long Value);
__INTRIN_INLINE long _InterlockedDecrement(volatile long *const lpAddend);
__INTRIN_INLINE long _InterlockedIncrement(volatile long *const lpAddend);
__INTRIN_INLINE short _InterlockedDecrement16(volatile short *const lpAddend);
__INTRIN_INLINE short _InterlockedIncrement16(volatile short *const lpAddend);
__INTRIN_INLINE unsigned char _interlockedbittestandreset(volatile long *a, const long b);
__INTRIN_INLINE unsigned char _interlockedbittestandset(volatile long *a, const long b);
__INTRIN_INLINE void __stosb(unsigned char *Dest, const unsigned char Data, size_t Count);
__INTRIN_INLINE void __stosw(unsigned short *Dest, const unsigned short Data, size_t Count);
__INTRIN_INLINE void __stosd(unsigned long *Dest, const unsigned long Data, size_t Count);
__INTRIN_INLINE void __movsb(unsigned char *Destination, const unsigned char *Source, size_t Count);
__INTRIN_INLINE void __movsw(unsigned short *Destination, const unsigned short *Source, size_t Count);
__INTRIN_INLINE void __movsd(unsigned long *Destination, const unsigned long *Source, size_t Count);
__INTRIN_INLINE void __writefsbyte(const unsigned long Offset, const unsigned char Data);
__INTRIN_INLINE void __writefsword(const unsigned long Offset, const unsigned short Data);
__INTRIN_INLINE void __writefsdword(const unsigned long Offset, const unsigned long Data);
__INTRIN_INLINE unsigned char __readfsbyte(const unsigned long Offset);
__INTRIN_INLINE unsigned short __readfsword(const unsigned long Offset);
__INTRIN_INLINE unsigned long __readfsdword(const unsigned long Offset);
__INTRIN_INLINE void __incfsbyte(const unsigned long Offset);
__INTRIN_INLINE void __incfsword(const unsigned long Offset);
__INTRIN_INLINE void __incfsdword(const unsigned long Offset);
__INTRIN_INLINE void __addfsbyte(const unsigned long Offset, const unsigned char Data);
__INTRIN_INLINE void __addfsword(const unsigned long Offset, const unsigned short Data);
__INTRIN_INLINE void __addfsdword(const unsigned long Offset, const unsigned int Data);
__INTRIN_INLINE unsigned char _BitScanForward(unsigned long *const Index, const unsigned long Mask);
__INTRIN_INLINE unsigned char _BitScanReverse(unsigned long *const Index, const unsigned long Mask);
__INTRIN_INLINE unsigned char _bittest(const long *const a, const long b);
__INTRIN_INLINE unsigned char _bittestandcomplement(long *const a, const long b);
__INTRIN_INLINE unsigned char _bittestandreset(long *const a, const long b);
__INTRIN_INLINE unsigned char _bittestandset(long *const a, const long b);
__INTRIN_INLINE unsigned char _rotl8(unsigned char value, unsigned char shift);
__INTRIN_INLINE unsigned short _rotl16(unsigned short value, unsigned char shift);
__INTRIN_INLINE unsigned int _rotl(unsigned int value, int shift);
__INTRIN_INLINE unsigned int _rotr(unsigned int value, int shift);
__INTRIN_INLINE unsigned char _rotr8(unsigned char value, unsigned char shift);
__INTRIN_INLINE unsigned short _rotr16(unsigned short value, unsigned char shift);
__INTRIN_INLINE unsigned long long __ll_lshift(const unsigned long long Mask, const int Bit);
__INTRIN_INLINE long long __ll_rshift(const long long Mask, const int Bit);
__INTRIN_INLINE unsigned long long __ull_rshift(const unsigned long long Mask, int Bit);
__INTRIN_INLINE unsigned short _byteswap_ushort(unsigned short value);
__INTRIN_INLINE unsigned long _byteswap_ulong(unsigned long value);
__INTRIN_INLINE unsigned long long _byteswap_uint64(unsigned long long value);
__INTRIN_INLINE long long __emul(const int a, const int b);
__INTRIN_INLINE unsigned long long __emulu(const unsigned int a, const unsigned int b);
__INTRIN_INLINE unsigned char __inbyte(const unsigned short Port);
__INTRIN_INLINE unsigned short __inword(const unsigned short Port);
__INTRIN_INLINE unsigned long __indword(const unsigned short Port);
__INTRIN_INLINE void __inbytestring(unsigned short Port, unsigned char *Buffer, unsigned long Count);
__INTRIN_INLINE void __inwordstring(unsigned short Port, unsigned short *Buffer, unsigned long Count);
__INTRIN_INLINE void __indwordstring(unsigned short Port, unsigned long *Buffer, unsigned long Count);
__INTRIN_INLINE void __outbyte(unsigned short const Port, const unsigned char Data);
__INTRIN_INLINE void __outword(unsigned short const Port, const unsigned short Data);
__INTRIN_INLINE void __outdword(unsigned short const Port, const unsigned long Data);
__INTRIN_INLINE void __outbytestring(unsigned short const Port, const unsigned char *const Buffer, const unsigned long Count);
__INTRIN_INLINE void __outwordstring(unsigned short const Port, const unsigned short *const Buffer, const unsigned long Count);
__INTRIN_INLINE void __outdwordstring(unsigned short const Port, const unsigned long *const Buffer, const unsigned long Count);
__INTRIN_INLINE int _inp(unsigned short Port);
__INTRIN_INLINE unsigned short _inpw(unsigned short Port);
__INTRIN_INLINE unsigned long _inpd(unsigned short Port);
__INTRIN_INLINE int _outp(unsigned short Port, int databyte);
__INTRIN_INLINE unsigned short _outpw(unsigned short Port, unsigned short dataword);
__INTRIN_INLINE unsigned long _outpd(unsigned short Port, unsigned long dataword);
__INTRIN_INLINE void __cpuid(int CPUInfo[], const int InfoType);
__INTRIN_INLINE unsigned long long __rdtsc(void);
__INTRIN_INLINE void __writeeflags(uintptr_t Value);
__INTRIN_INLINE uintptr_t __readeflags(void);
__INTRIN_INLINE void __debugbreak(void);
__INTRIN_INLINE void __int2c(void);
__INTRIN_INLINE void _disable(void);
__INTRIN_INLINE void _enable(void);
__INTRIN_INLINE void __halt(void);
__INTRIN_INLINE void __writecr0(const unsigned long long Data);
__INTRIN_INLINE void __writecr3(const unsigned long long Data);
__INTRIN_INLINE void __writecr4(const unsigned long long Data);
#if !defined(__amd64__)
__INTRIN_INLINE unsigned long __readcr0(void);
__INTRIN_INLINE unsigned long __readcr2(void);
__INTRIN_INLINE unsigned long __readcr3(void);
__INTRIN_INLINE unsigned long __readcr4(void);
__INTRIN_INLINE unsigned int __readdr(unsigned int reg);
__INTRIN_INLINE void __writedr(unsigned reg, unsigned int value);
#endif
__INTRIN_INLINE void __invlpg(void *const Address);
__INTRIN_INLINE unsigned long long __readmsr(const int reg);
__INTRIN_INLINE void __writemsr(const unsigned long Register, const unsigned long long Value);
__INTRIN_INLINE unsigned long long __readpmc(const int counter);
__INTRIN_INLINE unsigned long __segmentlimit(const unsigned long a);
__INTRIN_INLINE void __wbinvd(void);
__INTRIN_INLINE void __lidt(void *Source);
__INTRIN_INLINE void __sidt(void *Destination);
__INTRIN_INLINE void _mm_pause(void);

#if __GNUC__
__INTRIN_INLINE void _ReadWriteBarrier(void)
{
	__asm__ __volatile__("" : : : "memory");
}

#define _ReadBarrier _ReadWriteBarrier
#define _WriteBarrier _ReadWriteBarrier

__INTRIN_INLINE void _mm_lfence(void)
{
	_ReadBarrier();
	__asm__ __volatile__("lfence");
	_ReadBarrier();
}

__INTRIN_INLINE void _mm_sfence(void)
{
	_WriteBarrier();
	__asm__ __volatile__("sfence");
	_WriteBarrier();
}

__INTRIN_INLINE char _InterlockedCompareExchange8(volatile char *const Destination, const char Exchange, const char Comperand)
{
	char retval = Comperand;
	__asm__("lock; cmpxchgb %b[Exchange], %[Destination]" : [retval] "+a" (retval) : [Destination] "m" (*Destination), [Exchange] "q" (Exchange) : "memory");
	return retval;
}

__INTRIN_INLINE short _InterlockedCompareExchange16(volatile short *const Destination, const short Exchange, const short Comperand)
{
	short retval = Comperand;
	__asm__("lock; cmpxchgw %w[Exchange], %[Destination]" : [retval] "+a" (retval) : [Destination] "m" (*Destination), [Exchange] "q" (Exchange): "memory");
	return retval;
}

__INTRIN_INLINE long _InterlockedCompareExchange(volatile long *const Destination, const long Exchange, const long Comperand)
{
	long retval = Comperand;
	__asm__("lock; cmpxchgl %k[Exchange], %[Destination]" : [retval] "+a" (retval) : [Destination] "m" (*Destination), [Exchange] "q" (Exchange): "memory");
	return retval;
}

__INTRIN_INLINE void * _InterlockedCompareExchangePointer(void *volatile *const Destination, void *const Exchange, void *const Comperand)
{
	void * retval = (void *)Comperand;
	__asm__("lock; cmpxchgl %k[Exchange], %[Destination]" : [retval] "=a" (retval) : "[retval]" (retval), [Destination] "m" (*Destination), [Exchange] "q" (Exchange) : "memory");
	return retval;
}

__INTRIN_INLINE long _InterlockedExchange(volatile long *const Target, const long Value)
{
	long retval = Value;
	__asm__("xchgl %[retval], %[Target]" : [retval] "+r" (retval) : [Target] "m" (*Target) : "memory");
	return retval;
}

__INTRIN_INLINE void * _InterlockedExchangePointer(void *volatile *const Target, void *const Value)
{
	void * retval = Value;
	__asm__("xchgl %[retval], %[Target]" : [retval] "+r" (retval) : [Target] "m" (*Target) : "memory");
	return retval;
}

__INTRIN_INLINE short _InterlockedExchangeAdd16(volatile short *const Addend, const short Value)
{
	long retval = Value;
	__asm__("lock; xaddw %[retval], %[Addend]" : [retval] "+r" (retval) : [Addend] "m" (*Addend) : "memory");
	return (short)retval;
}

__INTRIN_INLINE long _InterlockedExchangeAdd(volatile long *const Addend, const long Value)
{
	long retval = Value;
#if __x86_64__
	__asm__("lock; xaddq %[retval], %[Addend]" : [retval] "+r" (retval) : [Addend] "m" (*Addend) : "memory");
#else
	__asm__("lock; xaddl %[retval], %[Addend]" : [retval] "+r" (retval) : [Addend] "m" (*Addend) : "memory");
#endif
	return retval;
}

__INTRIN_INLINE char _InterlockedAnd8(volatile char *const value, const char mask)
{
	char x;
	char y;

	y = *value;

	do
	{
		x = y;
		y = _InterlockedCompareExchange8(value, x & mask, x);
	}
	while(y != x);

	return y;
}

__INTRIN_INLINE short _InterlockedAnd16(volatile short *const value, const short mask)
{
	short x;
	short y;

	y = *value;

	do
	{
		x = y;
		y = _InterlockedCompareExchange16(value, x & mask, x);
	}
	while(y != x);

	return y;
}

__INTRIN_INLINE long _InterlockedAnd(volatile long *const value, const long mask)
{
	long x;
	long y;

	y = *value;

	do
	{
		x = y;
		y = _InterlockedCompareExchange(value, x & mask, x);
	}
	while(y != x);

	return y;
}

__INTRIN_INLINE char _InterlockedOr8(volatile char *const value, const char mask)
{
	char x;
	char y;

	y = *value;

	do
	{
		x = y;
		y = _InterlockedCompareExchange8(value, x | mask, x);
	}
	while(y != x);

	return y;
}

__INTRIN_INLINE short _InterlockedOr16(volatile short *const value, const short mask)
{
	short x;
	short y;

	y = *value;

	do
	{
		x = y;
		y = _InterlockedCompareExchange16(value, x | mask, x);
	}
	while(y != x);

	return y;
}

__INTRIN_INLINE long _InterlockedOr(volatile long *const value, const long mask)
{
	long x;
	long y;

	y = *value;

	do
	{
		x = y;
		y = _InterlockedCompareExchange(value, x | mask, x);
	}
	while(y != x);

	return y;
}

__INTRIN_INLINE char _InterlockedXor8(volatile char *const value, const char mask)
{
	char x;
	char y;

	y = *value;

	do
	{
		x = y;
		y = _InterlockedCompareExchange8(value, x ^ mask, x);
	}
	while(y != x);

	return y;
}

__INTRIN_INLINE short _InterlockedXor16(volatile short *const value, const short mask)
{
	short x;
	short y;

	y = *value;

	do
	{
		x = y;
		y = _InterlockedCompareExchange16(value, x ^ mask, x);
	}
	while(y != x);

	return y;
}

__INTRIN_INLINE long _InterlockedXor(volatile long *const value, const long mask)
{
	long x;
	long y;

	y = *value;

	do
	{
		x = y;
		y = _InterlockedCompareExchange(value, x ^ mask, x);
	}
	while(y != x);

	return y;
}

__INTRIN_INLINE long long _InterlockedCompareExchange64(volatile long long *const Destination, const long long Exchange, const long long Comperand)
{
#if (__GNUC__ * 10000 + __GNUC_MINOR__ * 100 + __GNUC_PATCHLEVEL__) > 40100 && defined(__x86_64__)
	return __sync_val_compare_and_swap(Destination, Comperand, Exchange);
#else
	long long retval = Comperand;

	__asm__
	(
		"lock; cmpxchg8b %[Destination]" :
		[retval] "+A" (retval) :
		[Destination] "m" (*Destination),
		"b" ((unsigned long)((Exchange >>  0) & 0xFFFFFFFF)),
		"c" ((unsigned long)((Exchange >> 32) & 0xFFFFFFFF)) :
		"memory"
	);

	return retval;
#endif
}

__INTRIN_INLINE long _InterlockedAddLargeStatistic(volatile long long *const Addend, const long Value)
{
	__asm__
	(
		"lock; add %[Value], %[Lo32];"
		"jae LABEL%=;"
		"lock; adc $0, %[Hi32];"
		"LABEL%=:;" :
		[Lo32] "+m" (*((volatile long *)(Addend) + 0)), [Hi32] "+m" (*((volatile long *)(Addend) + 1)) :
		[Value] "ir" (Value) :
		"memory"
	);

	return Value;
}

__INTRIN_INLINE long _InterlockedDecrement(volatile long *const lpAddend)
{
	return _InterlockedExchangeAdd(lpAddend, -1) - 1;
}

__INTRIN_INLINE long _InterlockedIncrement(volatile long *const lpAddend)
{
	return _InterlockedExchangeAdd(lpAddend, 1) + 1;
}

__INTRIN_INLINE short _InterlockedDecrement16(volatile short *const lpAddend)
{
	return (short)(_InterlockedExchangeAdd16(lpAddend, -1) - 1);
}

__INTRIN_INLINE short _InterlockedIncrement16(volatile short *const lpAddend)
{
	return (short)(_InterlockedExchangeAdd16(lpAddend, 1) + 1);
}

__INTRIN_INLINE unsigned char _interlockedbittestandreset(volatile long *a, const long b)
{
	unsigned char retval;
	__asm__("lock; btrl %[b], %[a]; setb %b[retval]" : [retval] "=q" (retval), [a] "+m" (*a) : [b] "Ir" (b) : "memory");
	return retval;
}

__INTRIN_INLINE unsigned char _interlockedbittestandset(volatile long *a, const long b)
{
	unsigned char retval;
	__asm__("lock; btsl %[b], %[a]; setc %b[retval]" : [retval] "=q" (retval), [a] "+m" (*a) : [b] "Ir" (b) : "memory");
	return retval;
}

__INTRIN_INLINE void __stosb(unsigned char *Dest, const unsigned char Data, size_t Count)
{
	__asm__ __volatile__
	(
		"rep; stosb" :
		[Dest] "=D" (Dest), [Count] "=c" (Count) :
		"[Dest]" (Dest), "a" (Data), "[Count]" (Count)
	);
}

__INTRIN_INLINE void __stosw(unsigned short *Dest, const unsigned short Data, size_t Count)
{
	__asm__ __volatile__
	(
		"rep; stosw" :
		[Dest] "=D" (Dest), [Count] "=c" (Count) :
		"[Dest]" (Dest), "a" (Data), "[Count]" (Count)
	);
}

__INTRIN_INLINE void __stosd(unsigned long * Dest, const unsigned long Data, size_t Count)
{
	__asm__ __volatile__
	(
		"rep; stosl" :
		[Dest] "=D" (Dest), [Count] "=c" (Count) :
		"[Dest]" (Dest), "a" (Data), "[Count]" (Count)
	);
}

__INTRIN_INLINE void __movsb(unsigned char *Destination, const unsigned char *Source, size_t Count)
{
	__asm__ __volatile__
	(
		"rep; movsb" :
		[Destination] "=D" (Destination), [Source] "=S" (Source), [Count] "=c" (Count) :
		"[Destination]" (Destination), "[Source]" (Source), "[Count]" (Count)
	);
}

__INTRIN_INLINE void __movsw(unsigned short *Destination, const unsigned short *Source, size_t Count)
{
	__asm__ __volatile__
	(
		"rep; movsw" :
		[Destination] "=D" (Destination), [Source] "=S" (Source), [Count] "=c" (Count) :
		"[Destination]" (Destination), "[Source]" (Source), "[Count]" (Count)
	);
}

__INTRIN_INLINE void __movsd(unsigned long *Destination, const unsigned long *Source, size_t Count)
{
    __asm__ __volatile__
    (
        "rep; movsd" :
        [Destination] "=D" (Destination), [Source] "=S" (Source), [Count] "=c" (Count) :
        "[Destination]" (Destination), "[Source]" (Source), "[Count]" (Count)
    );
}

__INTRIN_INLINE void __writefsbyte(const unsigned long Offset, const unsigned char Data)
{
	__asm__ __volatile__("movb %b[Data], %%fs:%a[Offset]" : : [Offset] "ir" (Offset), [Data] "iq" (Data) : "memory");
}

__INTRIN_INLINE void __writefsword(const unsigned long Offset, const unsigned short Data)
{
	__asm__ __volatile__("movw %w[Data], %%fs:%a[Offset]" : : [Offset] "ir" (Offset), [Data] "ir" (Data) : "memory");
}

__INTRIN_INLINE void __writefsdword(const unsigned long Offset, const unsigned long Data)
{
	__asm__ __volatile__("movl %k[Data], %%fs:%a[Offset]" : : [Offset] "ir" (Offset), [Data] "ir" (Data) : "memory");
}

__INTRIN_INLINE unsigned char __readfsbyte(const unsigned long Offset)
{
	unsigned char value;
	__asm__ __volatile__("movb %%fs:%a[Offset], %b[value]" : [value] "=q" (value) : [Offset] "ir" (Offset));
	return value;
}

__INTRIN_INLINE unsigned short __readfsword(const unsigned long Offset)
{
	unsigned short value;
	__asm__ __volatile__("movw %%fs:%a[Offset], %w[value]" : [value] "=r" (value) : [Offset] "ir" (Offset));
	return value;
}

__INTRIN_INLINE unsigned long __readfsdword(const unsigned long Offset)
{
	unsigned long value;
	__asm__ __volatile__("movl %%fs:%a[Offset], %k[value]" : [value] "=r" (value) : [Offset] "ir" (Offset));
	return value;
}

__INTRIN_INLINE void __incfsbyte(const unsigned long Offset)
{
	__asm__ __volatile__("incb %%fs:%a[Offset]" : : [Offset] "ir" (Offset) : "memory");
}

__INTRIN_INLINE void __incfsword(const unsigned long Offset)
{
	__asm__ __volatile__("incw %%fs:%a[Offset]" : : [Offset] "ir" (Offset) : "memory");
}

__INTRIN_INLINE void __incfsdword(const unsigned long Offset)
{
	__asm__ __volatile__("incl %%fs:%a[Offset]" : : [Offset] "ir" (Offset) : "memory");
}

__INTRIN_INLINE void __addfsbyte(const unsigned long Offset, const unsigned char Data)
{
	if(!__builtin_constant_p(Offset))
		__asm__ __volatile__("addb %b[Offset], %%fs:%a[Offset]" : : [Offset] "r" (Offset) : "memory");
	else
		__asm__ __volatile__("addb %b[Data], %%fs:%a[Offset]" : : [Offset] "ir" (Offset), [Data] "iq" (Data) : "memory");
}

__INTRIN_INLINE void __addfsword(const unsigned long Offset, const unsigned short Data)
{
	if(!__builtin_constant_p(Offset))
		__asm__ __volatile__("addw %w[Offset], %%fs:%a[Offset]" : : [Offset] "r" (Offset) : "memory");
	else
		__asm__ __volatile__("addw %w[Data], %%fs:%a[Offset]" : : [Offset] "ir" (Offset), [Data] "iq" (Data) : "memory");
}

__INTRIN_INLINE void __addfsdword(const unsigned long Offset, const unsigned int Data)
{
	if(!__builtin_constant_p(Offset))
		__asm__ __volatile__("addl %k[Offset], %%fs:%a[Offset]" : : [Offset] "r" (Offset) : "memory");
	else
		__asm__ __volatile__("addl %k[Data], %%fs:%a[Offset]" : : [Offset] "ir" (Offset), [Data] "iq" (Data) : "memory");
}

__INTRIN_INLINE unsigned char _BitScanForward(unsigned long *const Index, const unsigned long Mask)
{
	__asm__("bsfl %[Mask], %[Index]" : [Index] "=r" (*Index) : [Mask] "mr" (Mask));
	return Mask ? 1 : 0;
}

__INTRIN_INLINE unsigned char _BitScanReverse(unsigned long *const Index, const unsigned long Mask)
{
	__asm__("bsrl %[Mask], %[Index]" : [Index] "=r" (*Index) : [Mask] "mr" (Mask));
	return Mask ? 1 : 0;
}

__INTRIN_INLINE unsigned char _bittest(const long *const a, const long b)
{
	unsigned char retval;

	if(__builtin_constant_p(b))
		__asm__("bt %[b], %[a]; setb %b[retval]" : [retval] "=q" (retval) : [a] "mr" (*(a + (b / 32))), [b] "Ir" (b % 32));
	else
		__asm__("bt %[b], %[a]; setb %b[retval]" : [retval] "=q" (retval) : [a] "mr" (*a), [b] "r" (b));

	return retval;
}

__INTRIN_INLINE unsigned char _bittestandcomplement(long *const a, const long b)
{
	unsigned char retval;

	if(__builtin_constant_p(b))
		__asm__("btc %[b], %[a]; setb %b[retval]" : [a] "+mr" (*(a + (b / 32))), [retval] "=q" (retval) : [b] "Ir" (b % 32));
	else
		__asm__("btc %[b], %[a]; setb %b[retval]" : [a] "+mr" (*a), [retval] "=q" (retval) : [b] "r" (b));

	return retval;
}

__INTRIN_INLINE unsigned char _bittestandreset(long *const a, const long b)
{
	unsigned char retval;

	if(__builtin_constant_p(b))
		__asm__("btr %[b], %[a]; setb %b[retval]" : [a] "+mr" (*(a + (b / 32))), [retval] "=q" (retval) : [b] "Ir" (b % 32));
	else
		__asm__("btr %[b], %[a]; setb %b[retval]" : [a] "+mr" (*a), [retval] "=q" (retval) : [b] "r" (b));
	
	return retval;
}

__INTRIN_INLINE unsigned char _bittestandset(long *const a, const long b)
{
	unsigned char retval;
	
	if(__builtin_constant_p(b))
		__asm__("bts %[b], %[a]; setb %b[retval]" : [a] "+mr" (*(a + (b / 32))), [retval] "=q" (retval) : [b] "Ir" (b % 32));
	else
		__asm__("bts %[b], %[a]; setb %b[retval]" : [a] "+mr" (*a), [retval] "=q" (retval) : [b] "r" (b));

	return retval;
}

__INTRIN_INLINE unsigned char _rotl8(unsigned char value, unsigned char shift)
{
	unsigned char retval;
	__asm__("rolb %b[shift], %b[retval]" : [retval] "=rm" (retval) : "[retval]" (value), [shift] "Nc" (shift));
	return retval;
}

__INTRIN_INLINE unsigned short _rotl16(unsigned short value, unsigned char shift)
{
	unsigned short retval;
	__asm__("rolw %b[shift], %w[retval]" : [retval] "=rm" (retval) : "[retval]" (value), [shift] "Nc" (shift));
	return retval;
}

__INTRIN_INLINE unsigned int _rotl(unsigned int value, int shift)
{
	unsigned long retval;
	__asm__("roll %b[shift], %k[retval]" : [retval] "=rm" (retval) : "[retval]" (value), [shift] "Nc" (shift));
	return retval;
}

__INTRIN_INLINE unsigned int _rotr(unsigned int value, int shift)
{
	unsigned long retval;
	__asm__("rorl %b[shift], %k[retval]" : [retval] "=rm" (retval) : "[retval]" (value), [shift] "Nc" (shift));
	return retval;
}

__INTRIN_INLINE unsigned char _rotr8(unsigned char value, unsigned char shift)
{
	unsigned char retval;
	__asm__("rorb %b[shift], %b[retval]" : [retval] "=qm" (retval) : "[retval]" (value), [shift] "Nc" (shift));
	return retval;
}

__INTRIN_INLINE unsigned short _rotr16(unsigned short value, unsigned char shift)
{
	unsigned short retval;
	__asm__("rorw %b[shift], %w[retval]" : [retval] "=rm" (retval) : "[retval]" (value), [shift] "Nc" (shift));
	return retval;
}

__INTRIN_INLINE unsigned long long __ll_lshift(const unsigned long long Mask, const int Bit)
{
	unsigned long long retval = Mask;
	
	__asm__
	(
		"shldl %b[Bit], %%eax, %%edx; sall %b[Bit], %%eax" :
		"+A" (retval) :
		[Bit] "Nc" ((unsigned char)((unsigned long)Bit) & 0xFF)
	);

	return retval;
}

__INTRIN_INLINE long long __ll_rshift(const long long Mask, const int Bit)
{
	unsigned long long retval = (unsigned long long)Mask;
	
	__asm__
	(
		"shldl %b[Bit], %%eax, %%edx; sarl %b[Bit], %%eax" :
		"+A" (retval) :
		[Bit] "Nc" ((unsigned char)((unsigned long)Bit) & 0xFF)
	);

	return (long long)retval;
}

__INTRIN_INLINE unsigned long long __ull_rshift(const unsigned long long Mask, int Bit)
{
	unsigned long long retval = Mask;

	__asm__
	(
		"shrdl %b[Bit], %%eax, %%edx; shrl %b[Bit], %%eax" :
		"+A" (retval) :
		[Bit] "Nc" ((unsigned char)((unsigned long)Bit) & 0xFF)
	);

	return retval;
}

__INTRIN_INLINE unsigned short _byteswap_ushort(unsigned short value)
{
	unsigned short retval;
	__asm__("rorw $8, %w[retval]" : [retval] "=rm" (retval) : "[retval]" (value));
	return retval;
}

__INTRIN_INLINE unsigned long _byteswap_ulong(unsigned long value)
{
	unsigned long retval;
	__asm__("bswapl %[retval]" : [retval] "=r" (retval) : "[retval]" (value));
	return retval;
}

__INTRIN_INLINE unsigned long long _byteswap_uint64(unsigned long long value)
{
#if __i386__
	union {
	 unsigned long long int64part;
		struct {
			unsigned long lowpart;
			unsigned long hipart;
		};
	} retval;
	retval.int64part = value;
	__asm__("bswapl %[lowpart]\n"
			"bswapl %[hipart]\n"
			: [lowpart] "=r" (retval.hipart), [hipart] "=r" (retval.lowpart)  : "[lowpart]" (retval.lowpart), "[hipart]" (retval.hipart) );
	return retval.int64part;
#else
	unsigned long long retval;
	__asm__("bswapq %[retval]" : [retval] "=r" (retval) : "[retval]" (value));
	return retval;
#endif
}

__INTRIN_INLINE long long __emul(const int a, const int b)
{
	long long retval;
	__asm__("imull %[b]" : "=A" (retval) : [a] "a" (a), [b] "rm" (b));
	return retval;
}

__INTRIN_INLINE unsigned long long __emulu(const unsigned int a, const unsigned int b)
{
	unsigned long long retval;
	__asm__("mull %[b]" : "=A" (retval) : [a] "a" (a), [b] "rm" (b));
	return retval;
}

__INTRIN_INLINE unsigned char __inbyte(const unsigned short Port)
{
	unsigned char byte;
	__asm__ __volatile__("inb %w[Port], %b[byte]" : [byte] "=a" (byte) : [Port] "Nd" (Port));
	return byte;
}

__INTRIN_INLINE unsigned short __inword(const unsigned short Port)
{
	unsigned short word;
	__asm__ __volatile__("inw %w[Port], %w[word]" : [word] "=a" (word) : [Port] "Nd" (Port));
	return word;
}

__INTRIN_INLINE unsigned long __indword(const unsigned short Port)
{
	unsigned long dword;
	__asm__ __volatile__("inl %w[Port], %k[dword]" : [dword] "=a" (dword) : [Port] "Nd" (Port));
	return dword;
}

__INTRIN_INLINE void __inbytestring(unsigned short Port, unsigned char *Buffer, unsigned long Count)
{
	__asm__ __volatile__
	(
		"rep; insb" :
		[Buffer] "=D" (Buffer), [Count] "=c" (Count) :
		"d" (Port), "[Buffer]" (Buffer), "[Count]" (Count) :
		"memory"
	);
}

__INTRIN_INLINE void __inwordstring(unsigned short Port, unsigned short *Buffer, unsigned long Count)
{
	__asm__ __volatile__
	(
		"rep; insw" :
		[Buffer] "=D" (Buffer), [Count] "=c" (Count) :
		"d" (Port), "[Buffer]" (Buffer), "[Count]" (Count) :
		"memory"
	);
}

__INTRIN_INLINE void __indwordstring(unsigned short Port, unsigned long *Buffer, unsigned long Count)
{
	__asm__ __volatile__
	(
		"rep; insl" :
		[Buffer] "=D" (Buffer), [Count] "=c" (Count) :
		"d" (Port), "[Buffer]" (Buffer), "[Count]" (Count) :
		"memory"
	);
}

__INTRIN_INLINE void __outbyte(unsigned short const Port, const unsigned char Data)
{
	__asm__ __volatile__("outb %b[Data], %w[Port]" : : [Port] "Nd" (Port), [Data] "a" (Data));
}

__INTRIN_INLINE void __outword(unsigned short const Port, const unsigned short Data)
{
	__asm__ __volatile__("outw %w[Data], %w[Port]" : : [Port] "Nd" (Port), [Data] "a" (Data));
}

__INTRIN_INLINE void __outdword(unsigned short const Port, const unsigned long Data)
{
	__asm__ __volatile__("outl %k[Data], %w[Port]" : : [Port] "Nd" (Port), [Data] "a" (Data));
}

__INTRIN_INLINE void __outbytestring(unsigned short const Port, const unsigned char *const Buffer, const unsigned long Count)
{
	__asm__ __volatile__("rep; outsb" : : [Port] "d" (Port), [Buffer] "S" (Buffer), "c" (Count));
}

__INTRIN_INLINE void __outwordstring(unsigned short const Port, const unsigned short *const Buffer, const unsigned long Count)
{
	__asm__ __volatile__("rep; outsw" : : [Port] "d" (Port), [Buffer] "S" (Buffer), "c" (Count));
}

__INTRIN_INLINE void __outdwordstring(unsigned short const Port, const unsigned long *const Buffer, const unsigned long Count)
{
	__asm__ __volatile__("rep; outsl" : : [Port] "d" (Port), [Buffer] "S" (Buffer), "c" (Count));
}

__INTRIN_INLINE int _inp(unsigned short Port)
{
	return __inbyte(Port);
}
__INTRIN_INLINE unsigned short _inpw(unsigned short Port)
{
	return __inword(Port);
}

__INTRIN_INLINE unsigned long _inpd(unsigned short Port)
{
	return __indword(Port);
}

__INTRIN_INLINE int _outp(unsigned short Port, int databyte)
{
	__outbyte(Port, (unsigned char)databyte);
	return databyte;
}

__INTRIN_INLINE unsigned short _outpw(unsigned short Port, unsigned short dataword)
{
	__outword(Port, dataword);
	return dataword;
}

__INTRIN_INLINE unsigned long _outpd(unsigned short Port, unsigned long dataword)
{
	__outdword(Port, dataword);
	return dataword;
}

__INTRIN_INLINE void __cpuid(int CPUInfo[], const int InfoType)
{
	__asm__ __volatile__("cpuid" : "=a" (CPUInfo[0]), "=b" (CPUInfo[1]), "=c" (CPUInfo[2]), "=d" (CPUInfo[3]) : "a" (InfoType));
}

__INTRIN_INLINE unsigned long long __rdtsc(void)
{
#ifdef __x86_64__
	unsigned long long low, high;
	__asm__ __volatile__("rdtsc" : "=a"(low), "=d"(high));
	return low | (high << 32);
#else
	unsigned long long retval;
	__asm__ __volatile__("rdtsc" : "=A"(retval));
	return retval;
#endif
}

__INTRIN_INLINE void __writeeflags(uintptr_t Value)
{
	__asm__ __volatile__("push %0\n popf" : : "rim"(Value));
}

__INTRIN_INLINE uintptr_t __readeflags(void)
{
	uintptr_t retval;
	__asm__ __volatile__("pushf\n pop %0" : "=rm"(retval));
	return retval;
}

__INTRIN_INLINE void __debugbreak(void)
{
	__asm__("int $3");
}

__INTRIN_INLINE void __int2c(void)
{
	__asm__("int $0x2c");
}

__INTRIN_INLINE void _disable(void)
{
	__asm__("cli" : : : "memory");
}

__INTRIN_INLINE void _enable(void)
{
	__asm__("sti" : : : "memory");
}

__INTRIN_INLINE void __halt(void)
{
	__asm__("hlt\n\t" : : : "memory");
}

__INTRIN_INLINE void __writecr0(const unsigned long long Data)
{
	__asm__("mov %[Data], %%cr0" : : [Data] "r" (Data) : "memory");
}

__INTRIN_INLINE void __writecr3(const unsigned long long Data)
{
	__asm__("mov %[Data], %%cr3" : : [Data] "r" (Data) : "memory");
}

__INTRIN_INLINE void __writecr4(const unsigned long long Data)
{
	__asm__("mov %[Data], %%cr4" : : [Data] "r" (Data) : "memory");
}

#if !__x86_64__
__INTRIN_INLINE unsigned long __readcr0(void)
{
	unsigned long value;
	__asm__ __volatile__("mov %%cr0, %[value]" : [value] "=r" (value));
	return value;
}

__INTRIN_INLINE unsigned long __readcr2(void)
{
	unsigned long value;
	__asm__ __volatile__("mov %%cr2, %[value]" : [value] "=r" (value));
	return value;
}

__INTRIN_INLINE unsigned long __readcr3(void)
{
	unsigned long value;
	__asm__ __volatile__("mov %%cr3, %[value]" : [value] "=r" (value));
	return value;
}

__INTRIN_INLINE unsigned long __readcr4(void)
{
	unsigned long value;
	__asm__ __volatile__("mov %%cr4, %[value]" : [value] "=r" (value));
	return value;
}

__INTRIN_INLINE unsigned int __readdr(unsigned int reg)
{
	unsigned int value;
	switch (reg)
	{
	case 0:
		__asm__ __volatile__("mov %%dr0, %[value]" : [value] "=r" (value));
		break;
	case 1:
		__asm__ __volatile__("mov %%dr1, %[value]" : [value] "=r" (value));
		break;
	case 2:
		__asm__ __volatile__("mov %%dr2, %[value]" : [value] "=r" (value));
		break;
	case 3:
		__asm__ __volatile__("mov %%dr3, %[value]" : [value] "=r" (value));
		break;
	case 4:
		__asm__ __volatile__("mov %%dr4, %[value]" : [value] "=r" (value));
		break;
	case 5:
		__asm__ __volatile__("mov %%dr5, %[value]" : [value] "=r" (value));
		break;
	case 6:
		__asm__ __volatile__("mov %%dr6, %[value]" : [value] "=r" (value));
		break;
	case 7:
		__asm__ __volatile__("mov %%dr7, %[value]" : [value] "=r" (value));
		break;
	}
	return value;
}

__INTRIN_INLINE void __writedr(unsigned reg, unsigned int value)
{
	switch (reg)
	{
	case 0:
		__asm__("mov %[value], %%dr0" : : [value] "r" (value) : "memory");
		break;
	case 1:
		__asm__("mov %[value], %%dr1" : : [value] "r" (value) : "memory");
		break;
	case 2:
		__asm__("mov %[value], %%dr2" : : [value] "r" (value) : "memory");
		break;
	case 3:
		__asm__("mov %[value], %%dr3" : : [value] "r" (value) : "memory");
		break;
	case 4:
		__asm__("mov %[value], %%dr4" : : [value] "r" (value) : "memory");
		break;
	case 5:
		__asm__("mov %[value], %%dr5" : : [value] "r" (value) : "memory");
		break;
	case 6:
		__asm__("mov %[value], %%dr6" : : [value] "r" (value) : "memory");
		break;
	case 7:
		__asm__("mov %[value], %%dr7" : : [value] "r" (value) : "memory");
		break;
	}
}
#endif

__INTRIN_INLINE void __invlpg(void *const Address)
{
	__asm__("invlpg %[Address]" : : [Address] "m" (*((unsigned char *)(Address))) : "memory");
}

__INTRIN_INLINE unsigned long long __readmsr(const int reg)
{
#ifdef __x86_64__
	unsigned long low, high;
	__asm__ __volatile__("rdmsr" : "=a" (low), "=d" (high) : "c" (reg));
	return ((unsigned long long)high << 32) | low;
#else
	unsigned long long retval;
	__asm__ __volatile__("rdmsr" : "=A" (retval) : "c" (reg));
	return retval;
#endif
}

__INTRIN_INLINE void __writemsr(const unsigned long Register, const unsigned long long Value)
{
#ifdef __x86_64__
	__asm__ __volatile__("wrmsr" : : "a" (Value), "d" (Value >> 32), "c" (Register));
#else
	__asm__ __volatile__("wrmsr" : : "A" (Value), "c" (Register));
#endif
}

__INTRIN_INLINE unsigned long long __readpmc(const int counter)
{
	unsigned long long retval;
	__asm__ __volatile__("rdpmc" : "=A" (retval) : "c" (counter));
	return retval;
}

__INTRIN_INLINE unsigned long __segmentlimit(const unsigned long a)
{
	unsigned long retval;
	__asm__ __volatile__("lsl %[a], %[retval]" : [retval] "=r" (retval) : [a] "rm" (a));
	return retval;
}

__INTRIN_INLINE void __wbinvd(void)
{
	__asm__ __volatile__("wbinvd" : : : "memory");
}

__INTRIN_INLINE void __lidt(void *Source)
{
	__asm__ __volatile__("lidt %0" : : "m"(*(short*)Source));
}

__INTRIN_INLINE void __sidt(void *Destination)
{
	__asm__ __volatile__("sidt %0" : : "m"(*(short*)Destination) : "memory");
}

__INTRIN_INLINE void _mm_pause(void)
{
	__asm__ __volatile__("pause" : : : "memory");
}
#endif

#endif //_INTRIN_H
