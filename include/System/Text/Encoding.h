/********************************************************
 *	Encoding.h											*
 *														*
 *	XFX Encoding class definition file					*
 *	Copyright © XFX Team. All Rights Reserved			*
 ********************************************************/
#ifndef _ENCODING_
#define _ENCODING_

#include "../Types.h"
#include "Decoder.h"
#include "Encoder.h"

namespace System
{
	class String;

	namespace Text
	{
		// Represents a character encoding.
		class Encoding
		{
		public:
			Encoding();
			Encoding(int codePage);

			static Encoding ASCII();
			static Encoding BigEndianUnicode();
			virtual int CodePage();
			static Encoding Default();
			static Encoding Unicode();
			static Encoding UTF7();
			static Encoding UTF8();
			virtual String WebName();

			virtual Encoding Clone();
			static byte *Convert(Encoding &srcEncoding, Encoding &dstEncoding, byte bytes[]);
			static byte *Convert(Encoding &srcEncoding, Encoding &dstEncoding, byte bytes[], int index, int count);
			bool Equals(Encoding &obj);
			virtual int GetByteCount(char chars[]);
			virtual int GetByteCount(char chars[], int index, int count);
			virtual int GetByteCount(String &s);
			virtual byte *GetBytes(char chars[]);
			virtual byte *GetBytes(char chars[], int index, int count);
			virtual int GetBytes(char chars[], int charIndex, int charCount, byte bytes[], int byteIndex);
			virtual byte *GetBytes(String &s);
			virtual int GetBytes(String &s, int charIndex, int charCount, byte bytes[], int byteIndex);
			virtual int GetCharCount(byte bytes[]);
			virtual int GetCharCount(byte bytes[], int index, int count);
			virtual char *GetChars(byte bytes[]);
			virtual char *GetChars(byte bytes[], int index, int count);
			virtual int GetChars(byte bytes[], int byteIndex, int byteCount, char chars[], int charIndex);
			virtual Decoder GetDecoder();
			virtual Encoder GetEncoder();
			static Encoding GetEncoding(int codePage);
			static Encoding GetEncoding(String &name);
			int GetHashCode();
			virtual int GetMaxByteCount(int charCount);
			virtual int GetMaxCharCount(int byteCount);
			virtual byte* GetPreamble();
			virtual char* GetString(byte bytes[], int index, int count);
		};
	}
}

#endif //_ENCODING_
