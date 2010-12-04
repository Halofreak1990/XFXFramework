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
	typedef signed char			sbyte, SByte;
	typedef signed short		Int16;
	typedef signed int			Int32;
	typedef signed long long	Int64;
	typedef signed int			*IntPtr;
	/* UNSIGNED */
	typedef unsigned char 		byte, Byte;
	typedef unsigned short		ushort, UInt16;
	typedef unsigned int 		uint, UInt32;
	typedef unsigned long long	ulong, UInt64;
	/* FLOATING-POINT */
	typedef float				Single;
	typedef double				Double;
	/* OTHER */
	typedef bool				Boolean;

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
#define ALIGNED __attribute__ ((aligned (16)))

#endif //_SYSTEM_TYPES_
