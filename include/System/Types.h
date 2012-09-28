/********************************************************
 *	Types.h												*
 *														*
 *	Defines types for the entire XFX Framework			*
 *	Copyright © XFX Team. All Rights Reserved			*
 ********************************************************/
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

// Documentation
//
#define out

// Aligning Data types
//
#define ALIGNED4 __attribute__((aligned (4)))
#define ALIGNED8 __attribute__((aligned (8)))
#define ALIGNED16 __attribute__((aligned (16)))

#endif //_SYSTEM_TYPES_
