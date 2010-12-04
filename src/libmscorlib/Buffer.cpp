// Copyright (C) 2010-2012, XFX Team
// All rights reserved.
// 
// Redistribution and use in source and binary forms, with or without 
// modification, are permitted provided that the following conditions are met:
// 
//     * Redistributions of source code must retain the above copyright 
//       notice, this list of conditions and the following disclaimer.
//     * Redistributions in binary form must reproduce the above copyright 
//       notice, this list of conditions and the following disclaimer in the 
//       documentation and/or other materials provided with the distribution.
//     * Neither the name of the copyright holder nor the names of any 
//       contributors may be used to endorse or promote products derived from 
//       this software without specific prior written permission.
// 
// THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS" 
// AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE 
// IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE 
// ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT OWNER OR CONTRIBUTORS BE 
// LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR 
// CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF 
// SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS 
// INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN 
// CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) 
// ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE 
// POSSIBILITY OF SUCH DAMAGE.

#include <System/Buffer.h>
#include <System/Exception.h>

namespace System
{
	template <class T>
	void Buffer::BlockCopy(T src[], int srcOffset, T dst[], int dstOffset, int count)
	{
		if (src == null)
			throw ArgumentNullException("src");

		if (dst == null)
			throw ArgumentNullException("dst");

		if (srcOffset < 0)
			throw ArgumentOutOfRangeException("srcOffset", "Non-negative number required.");

		if (dstOffset < 0)
			throw ArgumentOutOfRangeException("dstOffset", "Non-negative number required.");

		if (count < 0)
			throw ArgumentOutOfRangeException("count", "Non-negative number required.");
		
		if ((srcOffset > ByteLength(src) - count) || (dstOffset > ByteLength(dst) - count))
				throw ArgumentException("Offset and length were out of bounds for the array or count is greater than the number of elements from index to the end of the source collection.");

		for(int i = srcOffset, j = dstOffset; i < (srcOffset + count); i++, j++)
		{
			dst[j] = src[i];
		}
	}

	template <class T>
	int Buffer::ByteLength(T array[])
	{
		return sizeof(array);
	}

	template <class T>
	byte Buffer::GetByte(T array[], int index)
	{
		if (index < 0 || index >= ByteLength(array))
			throw ArgumentOutOfRangeException("index", "Value must be non-negative and less than the size of the collection.");

		return ((byte *) &array[index]);
	}

	template <class T>
	void Buffer::SetByte(T array[], int index, byte value)
	{
		if (index < 0 || index >= ByteLength(array))
			throw ArgumentOutOfRangeException ("index", "Value must be non-negative and less than the size of the collection.");

		SetByteInternal(array, index, value);
	}
}
