#ifndef _TEXT_ENCODER_
#define _TEXT_ENCODER_

#include <System/Types.h>

namespace System
{
	namespace Text
	{
		/// <summary>
		/// Converts a set of characters into a sequence of bytes.
		/// </summary>
		class Encoder
		{
		public:
			Encoder();

			virtual void Convert(char* chars, int charCount, byte* bytes, int byteCount, bool flush, int charsUsed, int bytesUsed, bool completed);
			virtual void Convert(char chars[], int charIndex, int charCount, byte bytes[], int byteIndex, int byteCount, bool flush, int charsUsed, int bytesUsed, bool completed);
			virtual int GetByteCount(char* chars, int count, bool flush);
			virtual int GetByteCount(char chars[], int index, int count, bool flush);
			virtual int GetBytes(char* chars, int charCount, byte* bytes, int byteCount, bool flush);
			virtual int GetBytes(char chars[], int charIndex, int charCount, byte bytes[], int byteIndex, bool flush);
		};
	}
}

#endif //_TEXT_ENCODER_
