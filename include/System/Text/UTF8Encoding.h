#ifndef _SYSTEM_TEXT_UTF8ENCODING_
#define _SYSTEM_TEXT_UTF8ENCODING_

#include "Encoding.h"

namespace System
{
	namespace Text
	{
		/// <summary>
		/// Represents a UTF-8 encoding of Unicode characters.
		/// </summary>
		class UTF8Encoding : public Encoding
		{
		private:
			bool emitUTF8Identifier;
			static const int FinalByte = 0x20000000;
			bool isThrowException;
			static const int SupplimentarySeq = 0x10000000;
			static const int ThreeByteSeq = 0x8000000;
			static const int UTF8_CODEPAGE = 0xfde9;

			byte* GetBytesUnknown(byte* pSrc, int ch);

		public:
			UTF8Encoding();
			UTF8Encoding(bool encoderShouldEmitUTF8Identifier);
			UTF8Encoding(bool encoderShouldEmitUTF8Identifier, bool throwOnInvalidBytes);
			bool Equals(Object* value);
			int GetByteCount(char* chars);
			int GetByteCount(char* chars, int count);
			int GetByteCount(char chars[], int index, int count);
			int GetBytes(char* chars, int charCount, byte* bytes, int byteCount);
			int GetBytes(char chars[], int charIndex, int charCount, byte bytes[], int byteIndex);
			int GetCharCount(byte* bytes, int count);
			int GetCharCount(byte bytes[], int index, int count);
			int GetChars(byte* bytes, int byteCount, char* chars, int charCount);
			int GetChars(byte bytes[], int byteIndex, int byteCount, char chars[], int charIndex);
			Decoder GetDecoder();
			Encoder GetEncoder();
			int GetHashCode();
			int GetMaxByteCount(int charCount);
			int GetMaxCharCount(int byteCount);
			byte* GetPreamble();
			char* GetString(byte bytes[], int index, int count);
		};
	}
}

#endif //_SYSTEM_TEXT_UTF8ENCODING_
