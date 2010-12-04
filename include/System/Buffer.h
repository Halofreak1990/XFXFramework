/********************************************************
 *	Buffer.h											*
 *														*
 *	XFX Buffer class definition file					*
 *	Copyright © XFX Team. All Rights Reserved			*
 ********************************************************/
#ifndef _SYSTEM_BUFFER_
#define _SYSTEM_BUFFER_

#include "Types.h"

namespace System
{
	/// <summary>
	/// Manipulates arrays of primitive types.
	/// </summary>
	class Buffer
	{
	public:
		template <class T>
		static void BlockCopy(T src[], int srcOffset, T dst[], int dstOffset, int count);
		template <class T>
		static int ByteLength(T array[]);
		template <class T>
		static byte GetByte(T array[], int index);
		template <class T>
		static void SetByte(T array[], int index, byte value);
	};
}

#endif //_SYSTEM_BUFFER_
