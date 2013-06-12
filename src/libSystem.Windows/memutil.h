#ifndef _MEMUTIL_H
#define _MEMUTIL_H

// sets count dwords of dest to value
inline void* memsetd(void* dest, const unsigned int value, const int count)
{
	__asm__ __volatile__("rep stosl"::"c" (count),"a" (value),"D" (dest): "memory");
	return dest;
}

// sets count words of dest to value
inline void* memsetw(void* dest, const unsigned short value, const int count)
{
	__asm__ __volatile__("rep stosw"::"c" (count),"a" (value),"D" (dest): "memory");
	return dest;
}

#endif //_MEMUTIL_H
