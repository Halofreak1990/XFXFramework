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
#include <stdarg.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

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
		if(count < 0)
		{
#if DEBUG
			printf("ARGUMENT_OUT_OF_RANGE in function %s, at line %i in file %s, argument \"%s\"\n", __FUNCTION__, __LINE__, __FILE__, "count");
#endif
			return;
		}
			
		internalString = (char*)malloc(count + 1);
		memset(internalString, c, count);
		internalString[count] = '\0';
	}

	String::String(char value[], int startIndex, int length)
		: Length(length)
	{
		if(value == NULL)
		{
#if DEBUG
			printf("ARGUMENT_NULL in function %s, at line %i in file %s, argument \"%s\"\n", __FUNCTION__, __LINE__, __FILE__, "value");
#endif
			return;
		}

		if((length < 0) || startIndex + length > Array::Length(value))
		{
#if DEBUG
			printf("ARGUMENT_OUT_OF_RANGE in function %s, at line %i in file %s, argument \"%s\"\n", __FUNCTION__, __LINE__, __FILE__, "length");
#endif
			return;
		}

		internalString = (char*)malloc(length + 1);
		Array::Copy(value, startIndex, internalString, 0, length);
		internalString[length] = '\0';
	}

	String::String(char *value)
		: Length(Array::Length(value))
	{
		internalString = (char*)malloc(Length+1);
		Buffer::BlockCopy(value, 0, internalString, 0, Length);
		internalString[Length] = '\0';
	}

	String::String(const String &obj)
		: Length(obj.Length)
	{
		// allocate storage
		internalString = (char*)malloc(obj.Length + 1);
		// copy the source string including null-terminator
		strncpy(obj.internalString, internalString, obj.Length + 1);
	}

	String::String(const char* obj)
		: Length(Array::Length(obj) - 1)
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

	String String::Clone()
	{
		return String(*this);
	}

	int String::CompareTo(String other)
	{
		return (Compare(*this, other));
	}

	int String::Compare(String str1, String str2)
	{
		return strncmp(str1.internalString, str2.internalString, str1.Length);
	}

	String String::Concat(String values[])
	{
		if(!values)
		{
#if DEBUG
			printf("ARGUMENT_NULL in function %s, at line %i in file %s, argument \"%s\"\n", __FUNCTION__, __LINE__, __FILE__, "values");
#endif
			return String();
		}

		String buf = values[0];

		for (int i = 1; i < Array::Length(values); i++)
		{
			buf += values[i];
		}
		
		return buf;
	}

	char* String::Concat(char* values[])
	{
		if (!values)
		{
#if DEBUG
			printf("ARGUMENT_NULL in function %s, at line %i in file %s, argument \"%s\"\n", __FUNCTION__, __LINE__, __FILE__, "values");
#endif
			return "";
		}

		String buf = String(values[0]);

		for (int i = 1; i < Array::Length(values); i++)
		{
			buf += String(values[i]);
		}
		
		return buf.ToCharArray();
	}

	String String::Concat(String str1, String str2, String str3, String str4)
	{
		char* newString = (char*)malloc(str1.Length + str2.Length + str3.Length + str4.Length + 1);

		// Copy all source Strings to the destination buffer
		Buffer::BlockCopy(str1.internalString, 0, newString, 0, str1.Length);
		Buffer::BlockCopy(str2.internalString, 0, newString, str1.Length, str2.Length);
		Buffer::BlockCopy(str3.internalString, 0, newString, str1.Length + str2.Length, str3.Length);
		Buffer::BlockCopy(str4.internalString, 0, newString, str1.Length + str2.Length + str3.Length, str4.Length);

		newString[str1.Length + str2.Length + str3.Length + str4.Length] = '\0';

		String result = String(newString);
		free(newString);
		return result;
	}

	bool String::Equals(const String obj)
	{
		return (Compare(internalString, obj.internalString) == 0);
	}

	bool String::Equals(const String str1, const String str2)
	{
		return (Compare(str1.internalString, str2.internalString) == 0);
	}

	char* String::Format(char* format, ...)
	{
		if (!format)
		{
#if DEBUG
			printf("ARGUMENT_NULL in function %s, at line %i in file %s, argument \"%s\"\n", __FUNCTION__, __LINE__, __FILE__, "format");
#endif
			return "";
		}

		char* res = (char*)malloc(128);

		va_list	args;
		va_start(args, format);

		vsprintf(res, format, args);

		return res;
	}

	int String::IndexOf(char value)
	{
		for(int i = 0; i <= Length; i++)
		{
			if (internalString[i] == value)
				return i;
		}
		return -1;
	}
	
	int String::IndexOf(char value, int startIndex)
	{
		for(int i = startIndex; i <= Length; i++)
		{
			if(internalString[i] == value)
				return i;
		}
		return -1;
	}

	int String::IndexOf(char value, int startIndex, int count)
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
		return ((!value.internalString) || value.internalString == "");
	}
	
	String String::Join(String separator, String value[])
	{
		if (!value)
    		return "";

		return Join(separator, value, 0, Array::Length(value));
	}
	
	String String::Join(String separator, String value[], int startIndex, int count)
	{	
    	if (separator == NULL)
    	{
    	    separator = Empty;
    	}
    	if (!value)
		{
#if DEBUG
			printf("ARGUMENT_NULL in function %s, at line %i in file %s, argument \"%s\"\n", __FUNCTION__, __LINE__, __FILE__, "value");
#endif
    	    return "";
		}

    	if(startIndex < 0)
		{
#if DEBUG
    	    printf("ARGUMENT_OUT_OF_RANGE in function %s, at line %i in file %s, argument \"%s\"\n", __FUNCTION__, __LINE__, __FILE__, "startIndex");
#endif
			return "";
		}

    	if (count < 0)
		{
#if DEBUG
    	    printf("ARGUMENT_OUT_OF_RANGE in function %s, at line %i in file %s, argument \"%s\"\n", __FUNCTION__, __LINE__, __FILE__, "count");
#endif
			return "";
		}

		if (startIndex > (Array::Length(value) - count))
		{
#if DEBUG
    	    printf("ARGUMENT_OUT_OF_RANGE in function %s, at line %i in file %s, argument \"%s\"\n", __FUNCTION__, __LINE__, __FILE__, "startIndex");
#endif
			return "";
		}

    	if (count == 0)
    	{
    	    return Empty;
    	}


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

	char** String::Split(String separator, int count, StringSplitOptions_t options)
	{
		return null;
	}

	char** String::Split(String separator, StringSplitOptions_t options)
	{
		return null;
	}

	char** String::Split(char separator[], int count, StringSplitOptions_t options)
	{
		return null;
	}

	char** String::Split(char separator[], StringSplitOptions_t options)
	{
		return Split(separator, 0x7fffffff, options);
	}

	char** String::Split(char separator[], int count)
	{
		return Split(separator, count, StringSplitOptions::None);
	}

	char** String::Split(char separator[])
	{
		return Split(separator, 0x7fffffff, StringSplitOptions::None);
	}
	
	bool String::StartsWith(char* value)
	{
		if (!value)
	    	return false;

		return (strncmp(internalString, value, strlen(value)));
	}

	char* String::SubString(int startIndex)
	{
		char* newString = (char*)malloc(Length - startIndex); // allocate space for the SubString and accompanying null-terminator.

		Buffer::BlockCopy(internalString, startIndex, newString, 0, Length - startIndex); // copy  the string, starting at startIndex to destination
		
		newString[Array::Length(newString)] = '\0'; // null-terminate the resulting string

		return newString; // return the result
	}
	
	String String::SubString(int startIndex, int length)
	{
		char* newString = (char*)malloc(length + 1); // allocate space for the SubString and accompanying null-terminator.
		
		Buffer::BlockCopy(internalString, startIndex, newString, 0, length); // copy length chars, starting at startIndex, to newString

		newString[length] = '\0'; // null-terminate the resulting string
		
		String result = String(newString); // copy the newly created substring to a new String instance
		free(newString); // free the temporary buffer
		return result; // return the result
	}

	char *String::ToCharArray(int startIndex, int length)
	{
		/*if (startIndex + length > Length)
			throw ArgumentOutOfRangeException("startIndex + length exceeds the length of this String");*/

		char* tmp = (char*)malloc(length);
		
		Buffer::BlockCopy(internalString, startIndex, tmp, 0, length);

		return tmp;
	}

	char *String::ToCharArray()
	{
		char* result = (char*)malloc(Length + 1);
		strncpy(result, internalString, Length + 1);
		return result;
	}

	String String::ToLower()
	{
		
	}

	char* String::ToLower(char* str)
	{

	}
	
	char* String::ToString()
	{
		char* result = (char*)malloc(Length + 1);
		Buffer::BlockCopy(internalString, 0, result, 0, Length + 1);
		return result;
	}

	String String::ToUpper()
	{
		
	}

	char* String::ToUpper(char* str)
	{

	}

	bool String::operator!=(const String right)
	{
		return !Equals(right);
	}

	bool String::operator !=(char* right)
	{
		return (strncmp(internalString, right, Length) != 0);
	}

	bool String::operator==(const String right)
	{
		return Equals(right);
	}

	bool String::operator ==(char* right)
	{
		return (strncmp(internalString, right, Length) == 0);
	}

	String String::operator=(char* right)
	{
		return String(right);
	}

	String String::operator=(const String right)
	{
		return String(right);
	}

	String String::operator +(char *right)
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

	String String::operator +=(char* right)
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
		/*if (index < 0 || index >= strlen(internalString))
			throw IndexOutOfRangeException();*/

		return internalString[index];
	}
}
