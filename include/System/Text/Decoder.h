/********************************************************
 *	Decoder.h											*
 *														*
 *	XFX Decoder class definition file					*
 *	Copyright © XFX Team. All Rights Reserved			*
 ********************************************************/
#ifndef _TEXT_DECODER_
#define _TEXT_DECODER_

#include "../Types.h"

namespace System
{
	namespace Text
	{
		/// <summary>
		/// Converts a sequence of encoded bytes into a set of characters.
		/// </summary>
		class Decoder
		{
		private:
			void CheckArguments(char chars[], int charIndex);
			void CheckArguments(byte bytes[], int byteIndex, int byteCount);
			void CheckArguments(char* chars, int charCount, byte* bytes, int byteCount);

		public:
			Decoder();

			virtual void Convert(byte* bytes, int byteCount, char* chars, int charCount, bool flush, out int bytesUsed, out int charsUsed, out bool completed);
			virtual void Convert(byte bytes[], int byteIndex, int byteCount, char chars[], int charIndex, int charCount, bool flush, out int bytesUsed, out int charsUsed, out bool completed);
			virtual int GetCharCount(byte* bytes, int count, bool flush);
			virtual int GetCharCount(byte bytes[], int index, int count);
			virtual int GetCharCount(byte bytes[], int index, int count, bool flush);
			virtual int GetChars(byte* bytes, int byteCount, char* chars, int charCount, bool flush);
			virtual int GetChars(byte bytes[], int byteIndex, int byteCount, char chars[], int charIndex);
			virtual int GetChars(byte bytes[], int byteIndex, int byteCount, char chars[], int charIndex, bool flush);
			virtual void Reset();
		};
	}
}

#endif //_TEXT_DECODER_
