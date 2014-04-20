// Copyright (C) XFX Team
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

#include <System/FrameworkResources.h>
#include <System/String.h>
#include <System/Type.h>
#include <ctype.h>
#include <stdarg.h>
#undef __STRICT_ANSI__
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#include <sassert.h>

namespace System
{
	const String String::Empty = "";

	const Type StringTypeInfo("String", "System::String", TypeCode::String);

	String::String()
		: Length(0)
	{
		internalString = (char *)malloc(1);

		internalString[0] = '\0';
	}

	String::String(char c, int count)
		: Length(count)
	{
		sassert(count >= 0, String::Format("count; %s", FrameworkResources::ArgumentOutOfRange_NeedNonNegNum));
			
		internalString = (char*)malloc(count + 1);
		memset(internalString, c, count);
		internalString[count] = '\0';
	}

	String::String(char value[], int startIndex, int length)
		: Length(length)
	{
		sassert(value != null, String::Format("value; %s", FrameworkResources::ArgumentNull_Generic));

		internalString = (char*)malloc(length + 1);
		strncpy(internalString, &value[startIndex], length);
		internalString[length] = '\0';
	}

	String::String(const String &obj)
		: Length(obj.Length)
	{
		// allocate storage
		internalString = (char*)malloc(obj.Length + 1);
		// copy the source string
		strncpy(internalString, obj.internalString, obj.Length);

		internalString[Length] = '\0';
	}

	String::String(const char* obj)
		: Length(strlen(obj))
	{
		// allocate storage
		internalString = (char*)malloc(Length + 1);
		// copy the source string
		strncpy(internalString, obj, Length);

		internalString[Length] = '\0';
	}

	String::~String()
	{
		if (internalString)
		{
			free(internalString);
		}
	}

	String String::Clone() const
	{
		return String(*this);
	}

	int String::Compare(const String str1, const String str2)
	{
		return strcmp(str1.internalString, str2.internalString);
	}

	int String::CompareTo(const String other) const
	{
		return strcmp(this->internalString, other.internalString);
	}

	String String::Concat(const String values[], const int stringCount)
	{
		String result(Empty);
		for (int i = 0; i < stringCount; i++)
		{
			result += values[i];
		}
		return result;
	}

	String String::Concat(String str1, String str2, String str3, String str4)
	{
		char* newString = (char*)malloc(str1.Length + str2.Length + str3.Length + str4.Length + 1);

		// Copy all source Strings to the destination buffer
		strncpy(newString, str1.internalString, str1.Length);
		strncpy(newString + str1.Length, str2.internalString, str2.Length);
		strncpy(newString + (str1.Length + str2.Length), str3.internalString, str3.Length);
		strncpy(newString + (str1.Length + str2.Length + str3.Length), str4.internalString, str4.Length);

		newString[str1.Length + str2.Length + str3.Length + str4.Length] = '\0';

		String result = String(newString);
		free(newString);
		return result;
	}

	bool String::Equals(Object const * const obj) const
	{
		return is(obj, this) ? *this == *(String *)obj : false;
	}

	bool String::Equals(const String obj) const
	{
		return *this == obj;
	}

	bool String::Equals(const String& str1, const String& str2)
	{
		return str1 == str2;
	}

	const char* String::Format(const char* format, ...)
	{
		sassert(format != null, "format cannot be null.");

		va_list	args;
		va_start(args, format);

		int count = vsnprintf(NULL, 0, format, args);

		char* res = (char*)malloc(count + 1);

		vsnprintf(res, count + 1, format, args);

		va_end(args);

		return res;
	}

	int String::GetHashCode() const
	{
		int a = 31415, b = 27183;
		const char* v = internalString;
		int h;

		for (h = 0; *v != 0; v++, a = a * b)
			h = (a*h + *v);

		return h;
	}

	const Type& String::GetType()
	{
		return StringTypeInfo;
	}

	int String::IndexOf(char value) const
	{
		for(int i = 0; i <= Length; i++)
		{
			if (internalString[i] == value)
			{
				return i;
			}
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
		for(int i = startIndex; i < startIndex + count; i++)
		{
			if(internalString[i] == value)
			{
				return i;
			}
		}

		return -1;
	}

	int String::IndexOfAny(char anyOf[], int charCount) const
	{
		return IndexOfAny(anyOf, charCount, 0, Length);
	}

	int String::IndexOfAny(char anyOf[], int charCount, int startIndex) const
	{
		return IndexOfAny(anyOf, charCount, startIndex, Length - startIndex);
	}

	int String::IndexOfAny(char anyOf[], int charCount, int startIndex, int count) const
	{
		int indexOf = -1;

		for (int i = 0; i < charCount; i++)
		{
			indexOf = IndexOf(anyOf[i], startIndex, count);
			if (indexOf != -1)
			{
				return indexOf;
			}
		}

		return indexOf;
	}

	bool String::IsNullOrEmpty(const char* value)
	{
		return (value == NULL || strlen(value) == 0);
	}

	bool String::IsNullOrEmpty(const String& value)
	{
		return (value == NULL || value.Length == 0);
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
		return PadRight(totalWidth, ' ');
	}

	String String::PadRight(int totalWidth, char paddingChar)
	{
		if(totalWidth <= Length)
		{
			return *this;
		}

		char* newString = (char*)malloc(totalWidth + 1);
		
		strncpy(newString, internalString, Length);
		memset(&internalString[Length], paddingChar, totalWidth - Length);
		newString[totalWidth] = '\0';

		String result = String(newString);
		free(newString);
		return result;
	}

	char** String::Split(const String& separator, int count, StringSplitOptions_t options) const
	{
		// TODO: implement
		return null;
	}

	char** String::Split(const String& separator, StringSplitOptions_t options) const
	{
		return Split(separator, 0x7fffffff, options);
	}

	char** String::Split(char separator[], int count, StringSplitOptions_t options) const
	{
		// TODO: implement
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
	
	bool String::StartsWith(const String value) const
	{
		return (strncmp(internalString, value.internalString, value.Length) == 0);
	}

	char* String::SubString(const int startIndex) const
	{
		int newstrLen = (Length + 1) - startIndex;
		char* newString = (char*)malloc(newstrLen); // allocate space for the SubString and accompanying null-terminator.

		strncpy(newString, internalString + startIndex, newstrLen); // copy  the string, starting at startIndex to destination
		
		newString[newstrLen] = '\0'; // null-terminate the resulting string

		return newString; // return the result
	}
	
	String String::SubString(int startIndex, int length) const
	{
		return String(internalString, startIndex, length);
	}

	char* String::ToCharArray(const int startIndex, const int length) const
	{
		sassert((startIndex + length) < Length, "startIndex + length exceeds the length of this String instance.");

		char* tmp = (char*)malloc(length);
		
		strncpy(tmp, internalString + startIndex, length);

		return tmp;
	}

	char *String::ToCharArray() const
	{
		char* result = (char*)malloc(Length);
		strncpy(result, internalString, Length);
		return result;
	}

	String String::ToLower() const
	{
		String newString = String(*this);

		for (int i = 0; i < Length; i++)
		{
			newString.internalString[i] = tolower(internalString[i]);
		}

		return newString;
	}

	const char* String::ToLower(const char* str)
	{
		size_t strLen = strlen(str);
		char* tmp = (char*)malloc(strLen + 1);
		for (size_t i = 0; i < strLen; i++)
		{
			tmp[i] = tolower(str[i]);
		}

		tmp[strLen] = '\0';
		return tmp;
	}
	
	const String String::ToString() const
	{
		return *this;
	}

	String String::ToUpper() const
	{
		String newString = String(*this);

		for (int i = 0; i < Length; i++)
		{
			newString.internalString[i] = toupper(internalString[i]);
		}

		return newString;
	}

	const char* String::ToUpper(const char* str)
	{
		size_t strLen = strlen(str);
		char* tmp = (char*)malloc(strLen + 1);

		for (size_t i = 0; i < strLen; i++)
		{
			tmp[i] = toupper(str[i]);
		}

		tmp[strLen] = '\0';
		return tmp;
	}

	String::operator const char *() const
	{
		return internalString;
	}

	bool String::operator!=(const String& right) const
	{
		if (Length == right.Length)
		{
			return !Equals(right);
		}

		return true;
	}

	bool String::operator!=(const char* right) const
	{
		if (Length == (int)strlen(right))
		{
			return (strncmp(internalString, right, Length) != 0);
		}

		return false;
	}

	bool String::operator==(const String& right) const
	{
		if (Length == right.Length)
		{
			return Equals(right);
		}
		return false;
	}

	bool String::operator==(const char* right) const
	{
		if (Length == (int)strlen(right))
		{
			return (strncmp(internalString, right, Length) == 0);
		}

		return false;
	}

	String& String::operator=(const String& right)
	{
		// check for self-assignment
		if (*this == right)
		{
			return *this;
		}

		String result(right.internalString);

		return result;
	}

	String String::operator +(const char *right) const
	{
		// Allocate a temporary buffer
		char* newString = (char*)malloc(Length + strlen(right) + 1);

		strncpy(newString, internalString, Length);
		strncpy(newString + Length, right, strlen(right));
		newString[Length + strlen(right)] = '\0';

		String result(newString);
		free(newString);
		return result;
	}

	String String::operator +=(const String& right)
	{
		return *this + right;
	}

	String String::operator +=(const char* right)
	{
		return *this + right;
	}

	String String::operator +(const String& right) const
	{
		char* newString = (char*)malloc(Length + right.Length + 1);

		strncpy(newString, internalString, Length);
		strncpy(newString + Length, right.internalString, right.Length);
		newString[Length + right.Length] = '\0';

		String result = String(newString);
		free(newString);
		return result;
	}
	
	const char String::operator [](const int index) const
	{
		sassert(index > 0 && index < Length, "index out of range.");

		return internalString[index];
	}
}
