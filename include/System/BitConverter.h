/*****************************************************************************
 *	BitConverter.h															 *
 *																			 *
 *	XFX BitConverter definition file										 *
 *	Copyright (c) XFX Team. All Rights Reserved 							 *
 *****************************************************************************/
#ifndef _SYSTEM_BITCONVERTER_
#define _SYSTEM_BITCONVERTER_

#include "Types.h"

namespace System
{
	// Converts base data types to an array of bytes, and an array of bytes to base data types.
	class BitConverter
	{
	private:
		static byte* GetBytes(byte *ptr, int count) NONNULL(1);
		static bool AmIBigOrLittleEndian();
		static bool SwappedWordsInDouble();

		BitConverter(); //! private constructor to prevent instantiation

	public:
		static const bool IsLittleEndian;

		static byte* GetBytes(bool value);
		static byte* GetBytes(char value);
		static byte* GetBytes(double value);
		static byte* GetBytes(short value);
		static byte* GetBytes(int value);
		static byte* GetBytes(long long value);
		static byte* GetBytes(float value);
		static byte* GetBytes(ushort value);
		static byte* GetBytes(uint value);
		static byte* GetBytes(ulong value);
		static bool ToBoolean(byte value[], int startIndex) NONNULL(1);
		static char ToChar(byte value[], int startIndex) NONNULL(1);
		static double ToDouble(byte value[], int startIndex) NONNULL(1);
		static short ToInt16(byte value[], int startIndex) NONNULL(1);
		static int ToInt32(byte value[], int startIndex) NONNULL(1);
		static long long ToInt64(byte value[], int startIndex) NONNULL(1);
		static float ToSingle(byte value[], int startIndex) NONNULL(1);
		static ushort ToUInt16(byte value[], int startIndex) NONNULL(1);
		static uint ToUInt32(byte value[], int startIndex) NONNULL(1);
		static ulong ToUInt64(byte value[], int startIndex) NONNULL(1);
	};
}

#endif //_SYSTEM_BITCONVERTER_
