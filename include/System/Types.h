/*****************************************************************************
 *	Types.h																	 *
 *																			 *
 *	Defines types for the entire XFX Framework								 *
 *	Copyright (c) XFX Team. All Rights Reserved 							 *
 *****************************************************************************/
#ifndef _SYSTEM_TYPES_
#define _SYSTEM_TYPES_

#ifndef NULL
#define NULL 0
#endif

namespace System
{
	// Type definitions
	//
	/* SIGNED */
	typedef signed char			sbyte;
	typedef signed int			IntPtr;
	/* UNSIGNED */
	typedef unsigned char 		byte;
	typedef unsigned short		ushort;
	typedef unsigned int 		uint;
	typedef unsigned long long	ulong;
	typedef unsigned int		UIntPtr;

	/* OTHER */
#define null NULL
}

// Other typedefs
//
#define interface class

// Hints that the following parameter is an output
#define out

#if _MSC_VER
#define __attribute__(x)
#endif

// Structure packing
#define PACKED __attribute__((packed))

// Aligning Data types
//
#define ALIGNED4 __attribute__((aligned (4)))
#define ALIGNED8 __attribute__((aligned (8)))
#define ALIGNED16 __attribute__((aligned (16)))

#if _MSC_VER
#define FORMAT(...) __attribute__((format(__VA_ARGS__)))
#define NONNULL(...) __attribute__((nonnull(__VA_ARGS__)))
#else
#define FORMAT(x...) __attribute__((format(x)))
#define NONNULL(x...) __attribute__((nonnull(x)))
#endif

#define DEPRECATED __attribute__((deprecated))

#endif //_SYSTEM_TYPES_
