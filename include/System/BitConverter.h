/********************************************************
 *	BitConverter.h										*
 *														*
 *	XFX BitConverter definition file					*
 *	Copyright © XFX Team. All Rights Reserved			*
 ********************************************************/
#ifndef _SYSTEM_BITCONVERTER_
#define _SYSTEM_BITCONVERTER_

#include "Types.h"

namespace System
{
	/// <summary>
	/// Converts base data types to an array of bytes, and an array of bytes to base data types.
	/// </summary>
	class BitConverter
	{
	private:
		static byte *GetBytes(byte *ptr, int count);
		static bool AmIBigOrLittleEndian();
		static bool SwappedWordsInDouble();

		BitConverter(); //! private constructor to prevent instantiation

	public:
		static const bool IsLittleEndian;

		static byte *GetBytes(bool value);
		static byte *GetBytes(char value);
		static byte *GetBytes(double value);
		static byte *GetBytes(short value);
		static byte *GetBytes(int value);
		static byte *GetBytes(Int64 value);
		static byte *GetBytes(float value);
		static byte *GetBytes(UInt16 value);
		static byte *GetBytes(UInt32 value);
		static byte *GetBytes(UInt64 value);
		static bool ToBoolean(byte value[], int startIndex);
		static char ToChar(byte value[], int startIndex);
		static double ToDouble(byte value[], int startIndex);
		static Int16 ToInt16(byte value[], int startIndex);
		static Int32 ToInt32(byte value[], int startIndex);
	};
}

#endif //_SYSTEM_BITCONVERTER_
