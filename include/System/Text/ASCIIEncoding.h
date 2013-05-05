/********************************************************
 *	ASCIIEncoding.h										*
 *														*
 *	XFX ASCIIEncoding class definition file				*
 *	Copyright © XFX Team. All Rights Reserved			*
 ********************************************************/
#ifndef _ASCIIENCODING_
#define _ASCIIENCODING_

#include "Encoding.h"

namespace System
{
	namespace Text
	{
		/// <summary>
		/// Represents an ASCII character encoding of Unicode characters.
		/// </summary>
		class ASCIIEncoding : public Encoding
		{
		public:
			ASCIIEncoding();
			int GetByteCount(char chars[], int index, int count);
			int GetByteCount(String &chars);
			int GetBytes(char chars[], int charIndex, int charCount, byte bytes[], int byteIndex);
			int GetBytes(String &chars, int charIndex, int charCount, byte bytes[], int byteIndex);
			int GetCharCount(byte bytes[], int index, int count);
			int GetChars(byte bytes[], int byteIndex, int byteCount, char chars[], int charIndex);
			int GetMaxByteCount(int charCount);
			int GetMaxCharCount(int byteCount);
		};
	}
}

#endif //_ASCIIENCODING_
