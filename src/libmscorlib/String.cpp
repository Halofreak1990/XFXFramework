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

#include <System/Array.h>
#include <System/Buffer.h>
#include <System/String.h>
#include <ctype.h>
#include <stdarg.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#include <sassert.h>

namespace System
{
	const String String::Empty = "";

	String::String()
		: Length(0)
	{
		internalString = null;
	}

	String::String(char c, int count)
		: Length(count)
	{
		sassert(count >= 0, String::Format("count; %s", FrameworkResources::ArgumentOutOfRange_NeedNonNegNum));
			
		internalString = new char[count + 1];
		memset(internalString, c, count);
		internalString[count] = '\0';
	}

	String::String(char value[], int startIndex, int length)
		: Length(length)
	{
		sassert(value != null, "value cannot be null.");

		//sassert(!((length < 0) || startIndex + length > Array::Length(value)), "length is out of range.");

		internalString = new char[length + 1];
		Array::Copy(value, startIndex, internalString, 0, length);
		internalString[length] = '\0';
	}

	String::String(char *value)
		: Length(strlen(value))
	{
		internalString = new char[Length+1];
		Buffer::BlockCopy(value, 0, internalString, 0, Length);
		internalString[Length] = '\0';
	}

	String::String(const String &obj)
		: Length(obj.Length)
	{
		// allocate storage
		internalString = (char*)malloc(obj.Length + 1);
		// copy the source string
		strncpy(obj.internalString, internalString, obj.Length);
	}

	String::String(const char* obj)
		: Length(strlen(obj))
	{
		internalString = (char*)malloc(Length + 1);
		strncpy(internalString, obj, Length);
		internalString[Length] = '\n';
	}

	String::~String()
	{
		if (internalString)
			free(internalString);
	}

	String String::Clone() const
	{
		return String(*this);
	}

	int String::CompareTo(const String other) const
	{
		return (Compare(*this, other));
	}

	int String::Compare(const String str1, const String str2)
	{
		return strncmp(str1.internalString, str2.internalString, str1.Length);
	}

	String String::Concat(String str1, String str2, String str3, String str4)
	{
		char* newString = new char[str1.Length + str2.Length + str3.Length + str4.Length + 1];

		// Copy all source Strings to the destination buffer
		Buffer::BlockCopy(str1.internalString, 0, newString, 0, str1.Length);
		Buffer::BlockCopy(str2.internalString, 0, newString, str1.Length, str2.Length);
		Buffer::BlockCopy(str3.internalString, 0, newString, str1.Length + str2.Length, str3.Length);
		Buffer::BlockCopy(str4.internalString, 0, newString, str1.Length + str2.Length + str3.Length, str4.Length);

		newString[str1.Length + str2.Length + str3.Length + str4.Length] = '\0';

		String result = String(newString);
		delete[] newString;
		return result;
	}

	bool String::Equals(const String obj) const
	{
		return (Compare(internalString, obj.internalString) == 0);
	}

	bool String::Equals(const String str1, const String str2)
	{
		return (Compare(str1.internalString, str2.internalString) == 0);
	}

	const char* String::Format(const char* format, ...)
	{
		sassert(format != null, "format cannot be null.");

		va_list	args;
		va_start(args, format);

		int count = vsnprintf(NULL, 0, format, args);

		char* res = (char*)malloc(count + 1);

		vsnprintf(res, count + 1, format, args);

		return res;
	}

	int String::IndexOf(char value) const
	{
		for(int i = 0; i <= Length; i++)
		{
			if (internalString[i] == value)
				return i;
		}
		return -1;
	}
	
	int String::IndexOf(char value, int startIndex) const
	{
		for(int i = startIndex; i <= Length; i++)
		{
			if(internalString[i] == value)
				return i;
		}
		return -1;
	}

	int String::IndexOf(char value, int startIndex, int count) const
	{
		if((startIndex + count) > Length)
			return -1;

		for(int i = startIndex; i < startIndex+count; i++)
		{
			if(internalString[i] == value)
				return i;
		}
		return -1;
	}

	bool String::IsNullOrEmpty(String value)
	{
		return ((!value.internalString) || (value.internalString == ""));
	}

	String String::PadLeft(int totalWidth)
	{
		return PadLeft(totalWidth, ' ');
	}

	String String::PadLeft(int totalWidth, char paddingChar)
	{			
		if(totalWidth <= Length)
			return *this;

		char *buf = (char*)malloc(totalWidth);
		
		for(int i=0; i < (totalWidth - Length); i++)
		{
			buf[i] = paddingChar;
		}

		String result = String(strcat(buf, internalString));
		free(buf);
		return result;
	}

	String String::PadRight(int totalWidth)
	{
		int diff = totalWidth - Length;
		return PadRight(diff, ' ');
	}

	String String::PadRight(int totalWidth, char paddingChar)
	{
		if(totalWidth <= Length)
			return String(*this);

		char* newString = (char*)malloc(totalWidth + 1);
		
		Buffer::BlockCopy(internalString, 0, newString, 0, Length);
		memset(&internalString[Length], paddingChar, totalWidth - Length);
		newString[totalWidth] = '\0';

		String result = String(newString);
		free(newString);
		return result;
	}

	char** String::Split(String separator, int count, StringSplitOptions_t options) const
	{
		return null;
	}

	char** String::Split(String separator, StringSplitOptions_t options) const
	{
		return null;
	}

	char** String::Split(char separator[], int count, StringSplitOptions_t options) const
	{
		return null;
	}

	char** String::Split(char separator[], StringSplitOptions_t options) const
	{
		return Split(separator, 0x7fffffff, options);
	}

	char** String::Split(char separator[], int count) const
	{
		return Split(separator, count, StringSplitOptions::None);
	}

	char** String::Split(char separator[]) const
	{
		return Split(separator, 0x7fffffff, StringSplitOptions::None);
	}
	
	bool String::StartsWith(char* value) const
	{
		if (!value)
	    	return false;

		return (strncmp(internalString, value, strlen(value)));
	}

	char* String::SubString(const int startIndex) const
	{
		int newstrLen = (Length + 1) - startIndex;
		char* newString = new char[newstrLen]; // allocate space for the SubString and accompanying null-terminator.

		Buffer::BlockCopy(internalString, startIndex, newString, 0, Length - startIndex); // copy  the string, starting at startIndex to destination
		
		newString[newstrLen] = '\0'; // null-terminate the resulting string

		return newString; // return the result
	}
	
	String String::SubString(int startIndex, int length) const
	{
		char* newString = new char[length + 1]; // allocate space for the SubString and accompanying null-terminator.
		
		Buffer::BlockCopy(internalString, startIndex, newString, 0, length); // copy length chars, starting at startIndex, to newString

		newString[length] = '\0'; // null-terminate the resulting string
		
		String result = String(newString); // copy the newly created substring to a new String instance
		delete[] newString; // free the temporary buffer
		return result; // return the result
	}

	char* String::ToCharArray(const int startIndex, const int length) const
	{
		sassert((startIndex + length) < Length, "startIndex + length exceeds the length of this String");

		char* tmp = new char[length];
		
		Buffer::BlockCopy(internalString, startIndex, tmp, 0, length);

		return tmp;
	}

	char *String::ToCharArray() const
	{
		char* result = new char[Length];
		Buffer::BlockCopy(internalString, 0, result, 0, Length);
		return result;
	}

	String String::ToLower()
	{
		char* tmp = new char[Length+1];
		for (int i = 0; i < Length; i++)
			tmp[i] = tolower(internalString[i]);

		tmp[Length] = '\0';
		String result = tmp;
		delete tmp;
		return result;
	}

	const char* String::ToLower(char* str)
	{
		
	}
	
	const char* String::ToString() const
	{
		char* result = new char[Length + 1];
		Buffer::BlockCopy(internalString, 0, result, 0, Length);
		result[Length] = '\0';
		return result;
	}

	String String::ToUpper()
	{
		char* tmp = new char[Length+1];
		for (int i = 0; i < Length; i++)
			tmp[i] = toupper(internalString[i]);

		tmp[Length] = '\0';
		String result = tmp;
		delete tmp;
		return result;
	}

	const char* String::ToUpper(char* str)
	{
		
	}

	bool String::operator!=(const String right) const
	{
		return !Equals(right);
	}

	bool String::operator !=(const char* right) const
	{
		return (strncmp(internalString, right, Length) != 0);
	}

	bool String::operator==(const String right) const
	{
		return Equals(right);
	}

	bool String::operator ==(const char* right) const
	{
		return (strncmp(internalString, right, Length) == 0);
	}

	/*String String::operator=(const char* right)
	{
		return String(right);
	}*/

	String String::operator=(const String right)
	{
		return String(right);
	}

	String String::operator +(const char *right)
	{
		// Allocate a temporary buffer
		char* newString = (char*)malloc(Length + strlen(right) + 1);

		Buffer::BlockCopy(internalString, 0, newString, 0, Length);
		Buffer::BlockCopy(right, 0, newString, Length, strlen(right));
		newString[Length + strlen(right)] = '\0';

		String result = String(newString);
		free(newString);
		return result;
	}

	String String::operator +=(const String right)
	{
		return *this + right;
	}

	String String::operator +=(const char* right)
	{
		return *this + right;
	}

	String String::operator +(const String right)
	{
		char* newString = (char*)malloc(Length + right.Length + 1);

		Buffer::BlockCopy(internalString, 0, newString, 0, Length);
		Buffer::BlockCopy(right.internalString, 0, newString, Length, right.Length);
		newString[Length + right.Length] = '\0';

		String result = String(newString);
		free(newString);
		return result;
	}
	
	char String::operator [](int index)
	{
		sassert(index > 0 && index < Length, "index out of range.");

		return internalString[index];
	}
}
