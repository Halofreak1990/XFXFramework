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

#include <System/Environment.h>
#include <System/FrameworkResources.h>
#include <System/Text/StringBuilder.h>
#include <System/String.h>
#include <sassert.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include <sassert.h>

namespace System
{
	namespace Text
	{
		StringBuilder::StringBuilder()
		{
		}

		StringBuilder::StringBuilder(const int capacity)
			: stringBuffer((char*)malloc(capacity)), strEnd(0), bufferLength(capacity)
		{
		}

		StringBuilder::StringBuilder(const int capacity, const int maxCapacity)
			: stringBuffer((char*)malloc(capacity)), strEnd(0), bufferLength(capacity), maxCapacity(maxCapacity)
		{
		}

		StringBuilder::StringBuilder(const String& value)
			: stringBuffer((char*)malloc(value.Length)), strEnd(value.Length), bufferLength(value.Length)
		{
			strncpy(stringBuffer, value.ToString(), value.Length);
		}

		StringBuilder::StringBuilder(const String& value, const int capacity)
		{
		}

		StringBuilder::StringBuilder(const String& value, const int startIndex, const int length, const int capacity)
		{
		}

		StringBuilder::~StringBuilder()
		{
			free(stringBuffer);
		}

		StringBuilder& StringBuilder::Append(const bool value)
		{
			return Append((value ? "true" : "false"));
		}

		StringBuilder& StringBuilder::Append(const byte value)
		{
			return AppendFormat("%i", value);
		}

		StringBuilder& StringBuilder::Append(const char value)
		{
			stringBuffer[strEnd++] = value;
			return *this;
		}

		StringBuilder& StringBuilder::Append(const char value[])
		{

			return *this;
		}

		StringBuilder& StringBuilder::Append(const char value[], const int startIndex, const int charCount)
		{
			//int requiredLength = length + charCount;

			for (int i = strEnd, j = startIndex; i < strEnd + charCount; i++, j++)
			{
				stringBuffer[i] = value[j];
			}

			return *this;
		}

		StringBuilder& StringBuilder::Append(const double value)
		{
			return AppendFormat("%f", value);
		}

		StringBuilder& StringBuilder::Append(const short value)
		{
			return AppendFormat("%i", value);
		}

		StringBuilder& StringBuilder::Append(const int value)
		{
			return AppendFormat("%i", value);
		}

		StringBuilder& StringBuilder::Append(const long long value)
		{
			return AppendFormat("%i", value);
		}

		StringBuilder& StringBuilder::Append(const Object* value)
		{
			return Append(value->ToString());
		}

		StringBuilder& StringBuilder::Append(const sbyte value)
		{
			return AppendFormat("%i", value);
		}

		StringBuilder& StringBuilder::Append(const float value)
		{
			return AppendFormat("%f", value);
		}

		StringBuilder& StringBuilder::Append(const String& value)
		{
			//int requiredLength = length + value.Length;
		}

		StringBuilder& StringBuilder::Append(const String& value, const int startIndex, const int count)
		{
			//int requiredLength = length + count;
		}

		StringBuilder& StringBuilder::Append(const ushort value)
		{
			return AppendFormat("%i", value);
		}

		StringBuilder& StringBuilder::Append(const uint value)
		{
			return AppendFormat("%i", value);
		}

		StringBuilder& StringBuilder::Append(const ulong value)
		{
			return AppendFormat("%i", value);
		}

		StringBuilder& StringBuilder::AppendFormat(const char* format, ...)
		{
			
		}

		StringBuilder& StringBuilder::AppendLine()
		{
			return Append(Environment::NewLine);
		}

		StringBuilder& StringBuilder::AppendLine(const String& value)
		{
			Append(value);
			return AppendLine();
		}

		void StringBuilder::CopyTo(const int sourceIndex, char destination[], const int destinationIndex, const int count)
		{
			sassert(destination != NULL, String::Format("destination; %s", FrameworkResources::ArgumentNull_Generic));

			sassert((sourceIndex + count) < bufferLength, "");

			for (int i = sourceIndex, j = destinationIndex; i < sourceIndex + count; i++, j++)
			{
				destination[j] = stringBuffer[i];
			}
		}

		int StringBuilder::EnsureCapacity(const int capacity)
		{
		}

		bool StringBuilder::Equals(const Object* obj) const
		{
			return is(obj, this) ? this->Equals((*(StringBuilder*)obj)) : false;
		}

		bool StringBuilder::Equals(const StringBuilder& other) const
		{
			return (*this == other);
		}

		int StringBuilder::GetType() const
		{
		}

		StringBuilder& StringBuilder::Remove(const int startIndex, const int length)
		{
			sassert(((startIndex + length) < bufferLength), "");

			for (int i = startIndex, j = startIndex + length; i < startIndex + length; i++, j++)
			{
				stringBuffer[i] = stringBuffer[j];
			}

			strEnd -= length;

			return *this;
		}

		StringBuilder& StringBuilder::Replace(const char oldChar, const char newChar)
		{
			for(int i = 0; i < strEnd; i++)
			{
				if (stringBuffer[i] == oldChar)
					stringBuffer[i] = newChar;
			}

			return *this;
		}

		StringBuilder& StringBuilder::Replace(const char oldChar, const char newChar, const int startIndex, const int count)
		{
			sassert((startIndex + count) < strEnd, "");

			for(int i = startIndex; i < startIndex + count; i++)
			{
				if (stringBuffer[i] == oldChar)
					stringBuffer[i] = newChar;
			}

			return *this;
		}

		const char* StringBuilder::ToString() const
		{
			char* result = (char*)malloc(strEnd + 1);
			strncpy(result, stringBuffer, strEnd);
			result[strEnd] = '\0';
			return result;
		}

		const char* StringBuilder::ToString(const int startIndex, const int length)
		{
			char* result = (char*)malloc(length + 1);
			strncpy(result, &stringBuffer[startIndex], length);
			result[length] = '\0';
			return result;
		}

		bool StringBuilder::operator ==(const StringBuilder& right) const
		{
			if (bufferLength == right.bufferLength)
			{
				return (strncmp(stringBuffer, right.stringBuffer, bufferLength) == 0);
			}
			return false;
		}

		bool StringBuilder::operator !=(const StringBuilder& right) const
		{
			if (bufferLength == right.bufferLength)
			{
				return (strncmp(stringBuffer, right.stringBuffer, bufferLength) != 0);
			}
			return true;
		}
	}
}
