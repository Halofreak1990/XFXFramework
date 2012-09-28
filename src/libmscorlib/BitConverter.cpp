// Copyright (C) 2010-2012, XFX Team
// All rights reserved.
// 
// Redistribution and use in source and binary forms, with or without 
// modification, are permitted provided that the following conditions are met:
// 
//* Redistributions of source code must retain the above copyright 
//notice, this list of conditions and the following disclaimer.
//* Redistributions in binary form must reproduce the above copyright 
//notice, this list of conditions and the following disclaimer in the 
//documentation and/or other materials provided with the distribution.
//* Neither the name of the copyright holder nor the names of any 
//contributors may be used to endorse or promote products derived from 
//this software without specific prior written permission.
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

#include <System/BitConverter.h>
#include <System/FrameworkResources.h>
#include <System/String.h>

#include <sassert.h>

namespace System
{
	bool BitConverter::AmIBigOrLittleEndian()
	{
		// binary representations of 1.0:
		// big endian: 3f f0 00 00 00 00 00 00
		// little endian: 00 00 00 00 00 00 f0 3f
		// arm fpa little endian: 00 00 f0 3f 00 00 00 00
		double d = 1.0;
		byte *b = (byte*)&d;
		return (b[0] == 0);
	}

	bool BitConverter::SwappedWordsInDouble()
	{
		// binary representations of 1.0:
		// big endian: 3f f0 00 00 00 00 00 00
		// little endian: 00 00 00 00 00 00 f0 3f
		// arm fpa little endian: 00 00 f0 3f 00 00 00 00
		double d = 1.0;
		byte *b = (byte*)&d;
		return b[2] == 0xf0;
	}

	void PutBytes(byte *dst, byte src[], int start_index, int count)
	{
		sassert(src != null, String::Format("src; %s", FrameworkResources::ArgumentNull_Generic));

		/*if (start_index < 0 || (start_index > Array::Length(src) - 1))
		{
#if DEBUG
			printf("ARGUMENT_OUT_OF_RANGE in function %s, at line %i in file %s, argument \"%s\": %s\n", __FUNCTION__, __LINE__, __FILE__, "startIndex", "Index was out of range. Must be non-negative and less than the size of the collection.");
#endif
			return;
		}*/

		for (int i = 0; i < count; i++)
			dst[i] = src[i + start_index];
	}

	const bool BitConverter::IsLittleEndian = BitConverter::AmIBigOrLittleEndian();

	byte *BitConverter::GetBytes(byte *ptr, int count)
	{
		byte *ret = new byte[count];

		for (int i = 0; i < count; i++)
		{
			ret[i] = ptr[i];
		}

		return ret;
	}

	byte *BitConverter::GetBytes(bool value)
	{
		return GetBytes((byte *) &value, 1);
	}

	byte *BitConverter::GetBytes(char value)
	{
		return GetBytes((byte *) &value, 1);
	}

	byte *BitConverter::GetBytes(double value)
	{
		if (SwappedWordsInDouble())
		{
			byte *data = new byte[8];
			byte *p = (byte*)&value;
			data [0] = p [4];
			data [1] = p [5];
			data [2] = p [6];
			data [3] = p [7];
			data [4] = p [0];
			data [5] = p [1];
			data [6] = p [2];
			data [7] = p [3];
			return data;
		}
		else
		{
			return GetBytes((byte *) &value, 8);
		}
	}

	byte *BitConverter::GetBytes(short value)
	{
		return GetBytes((byte *) &value, 2);
	}

	byte *BitConverter::GetBytes(int value)
	{
		return GetBytes((byte *) &value, 4);
	}

	byte *BitConverter::GetBytes(long long value)
	{
		return GetBytes((byte *) &value, 8);
	}

	byte *BitConverter::GetBytes(ushort value)
	{
		return GetBytes((byte *) &value, 2);
	}

	byte *BitConverter::GetBytes(uint value)
	{
		return GetBytes((byte *) &value, 4);
	}

	byte *BitConverter::GetBytes(ulong value)
	{
		return GetBytes((byte *) &value, 8);
	}

	bool BitConverter::ToBoolean(byte value[], int startIndex)
	{
		sassert(value != null, String::Format("value; %s", FrameworkResources::ArgumentNull_Generic));

		/*if (startIndex < 0 || (startIndex > Array::Length(value) - 1))
		{
#if DEBUG
			printf("ARGUMENT_OUT_OF_RANGE in function %s, at line %i in file %s, argument \"%s\": %s\n", __FUNCTION__, __LINE__, __FILE__, "startIndex", "Index was out of range. Must be non-negative and less than the size of the collection.");
#endif
			return false;
		}*/

		if (value[startIndex] != 0)
			return true;
			
		return false;
	}

	char BitConverter::ToChar(byte value[], int startIndex)
	{
		sassert(value != null, String::Format("value; %s", FrameworkResources::ArgumentNull_Generic));

		char ret;
		PutBytes((byte *) &ret, value, startIndex, 1);
		return ret;
	}

	double BitConverter::ToDouble(byte value[], int startIndex)
	{
		sassert(value != null, String::Format("value; %s", FrameworkResources::ArgumentNull_Generic));

		double ret;
		PutBytes((byte*)&ret, value, startIndex, 8);
		return ret;
	}

	short BitConverter::ToInt16(byte value[], int startIndex)
	{
		sassert(value != null, String::Format("value; %s", FrameworkResources::ArgumentNull_Generic));

		short ret;
		PutBytes((byte*)&ret, value, startIndex, 2);
		return ret;
	}

	int BitConverter::ToInt32(byte value[], int startIndex)
	{
		sassert(value != null, String::Format("value; %s", FrameworkResources::ArgumentNull_Generic));

		int ret;
		PutBytes((byte*)&ret, value, startIndex, 4);
		return ret;
	}

	float BitConverter::ToSingle(byte value[], int startIndex)
	{
		sassert(value != null, String::Format("value; %s", FrameworkResources::ArgumentNull_Generic));

		float ret;
		PutBytes((byte*)&ret, value, startIndex, 4);
		return ret;
	}

	ushort BitConverter::ToUInt16(byte value[], int startIndex)
	{
		sassert(value != null, String::Format("value; %s", FrameworkResources::ArgumentNull_Generic));

		ushort ret;
		PutBytes((byte*)&ret, value, startIndex, 2);
		return ret;
	}

	uint BitConverter::ToUInt32(byte value[], int startIndex)
	{
		sassert(value != null, String::Format("value; %s", FrameworkResources::ArgumentNull_Generic));

		uint ret;
		PutBytes((byte*)&ret, value, startIndex, 4);
		return ret;
	}

	ulong BitConverter::ToUInt64(byte value[], int startIndex)
	{
		sassert(value != null, String::Format("value; %s", FrameworkResources::ArgumentNull_Generic));

		ulong ret;
		PutBytes((byte*)&ret, value, startIndex, 8);
		return ret;
	}
}
