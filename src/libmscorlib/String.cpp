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
#include <System/String.h>
#include <System/Exception.h>
#include <stdlib.h>
#include <string.h>

namespace System
{
	const String String::Empty = String();
	
	int String::Length()
	{
		return Array::Length(internalString);
	}

	String::String()
	{
	}

	String::String(char c, int count)
	{
		if(count < 0)
			throw ArgumentOutOfRangeException("count");
			
		internalString = new char[count];
	}

	String::String(char value[], int startIndex, int length)
	{
		if(value == NULL)
			throw ArgumentNullException("value");

		if((length < 0) || startIndex + length > Array::Length(value))
			throw ArgumentOutOfRangeException("length");

		internalString = new char[length];
		for(int i = 0; i < length; i++)
		{
			internalString[i] = value[startIndex];
			startIndex++;
		}
	}

	String::String(char *value)
	{
		internalString = value;
	}

	String::~String()
	{
		delete internalString;
	}

	String String::Clone()
	{
		return *this;
	}

	int String::Compare(String str1, String str2)
	{
		return strcmp(str1.internalString, str2.internalString);
	}

	String String::Concat(String values[])
	{
		if(values = NULL)
			throw ArgumentNullException("values");

		char *result;
		
		return String(result);
	}

	String String::Concat(String str1, String str2, String str3, String str4)
	{
		str1.internalString + str2.internalString + str3.internalString + str4.internalString
		return String(tmp);
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

	}

	int String::IndexOf(char value)
	{
		for(int i = 0; i < Length(); i++)
		{
			if (internalString[i] == value)
				return i;
		}
	}
	
	int String::IndexOf(char value, int startIndex)
	{
		for(int i=startIndex; i < Length(); i++)
		{
			if(strArray[i] == value)
				return i;
		}
		return -1;
	}

	int String::IndexOf(char value, int startIndex, int count)
	{
		if(startIndex+count > Length())
			return -1;

		for(int i=startIndex; i < startIndex+count; i++)
		{
			if(strArray[i] == value)
				return i;
		}
		return -1;
	}

	bool String::IsNullOrEmpty(String value)
	{
		return ((value.internalSTring == NULL) || value.internalString == "");
	}
	
	String String::Join(char* separator, String value[])
	{
		if (value == NULL)
    		throw ArgumentNullException("value");

    	return Join(separator, value, 0, value.Length());
	}
	
	String String::Join(String separator, String value[], int startIndex, int count)
	{	
    	if (separator == NULL)
    	{
    	    separator = Empty;
    	}
    	if (value == NULL)
    	    throw ArgumentNullException("value");

    	if(startIndex < 0)
    	    throw ArgumentOutOfRangeException("startIndex");

    	if (count < 0)
    	    throw ArgumentOutOfRangeException("count");

    	if (startIndex > (value.Length() - count))
    	    throw ArgumentOutOfRangeException("startIndex");

    	if (count == 0)
    	{
    	    return Empty;
    	}


	}

	String String::PadLeft(int totalWidth)
	{
		return PadLeft(totalWidth, " ");
	}

	String String::PadLeft(int totalWidth, char paddingChar)
	{			
		if(totalWidth < length)
			return *this;

		char *buf;
		
		for(int i=0; i < totalWidth; i++)
		{
			buf[i] = paddingChar;
		}

		strArray = strcat(buf, strArray);
		return *this;
	}

	String String::PadRight(int totalWidth)
	{
		if(totalWidth <= Length())
			return *this;

		int diff = totalWidth - internalString.length();
		internalString.append(diff, " ");
		return *this;
	}

	String String::PadRight(int totalWidth, char paddingChar)
	{
		if(totalWidth <= Length())
			return *this;
	}

	char* *String::Split(String *separator, int count, StringSplitOptions_t options)
	{
		String arr[1] = { String::Empty };
		return arr;
	}

	char* *String::Split(String *separator, StringSplitOptions_t options)
	{
		
	}

	char* *String::Split(char separator[], int count, StringSplitOptions_t options)
	{
		if (count < 0)
    	    throw ArgumentOutOfRangeException("count")

			if ((options < StringSplitOptions::None) || (options > StringSplitOptions::RemoveEmptyEntries))
    	{
    	    throw ArgumentException("options");
    	}
			bool flag = options == StringSplitOptions::RemoveEmptyEntries;
    	if ((count == 0) || (flag && (this.Length == 0)))
    	{
    	    return new string[0];
    	}
    	int[] sepList = new int[this.Length];
    	int numReplaces = MakeSeparatorList(separator, ref sepList);
    	if ((numReplaces == 0) || (count == 1))
    	{
    	    return String[] { this };
    	}
    	if (flag)
    	{
    	    return InternalSplitOmitEmptyEntries(sepList, NULL, numReplaces, count);
    	}
    	return InternalSplitKeepEmptyEntries(sepList, NULL, numReplaces, count);
	}

	char* *String::Split(char separator[], StringSplitOptions_t options)
	{
		return Split(separator, 0x7fffffff, options);
	}

	char* *String::Split(char separator[], int count)
	{
		return Split(separator, count, StringSplitOptions::None);
	}

	char* *String::Split(char separator[])
	{
		return Split(separator, 0x7fffffff, StringSplitOptions::None);
	}
	
	bool String::StartsWith(String value)
	{
		if (value == NULL)
	    	throw ArgumentNullException("value");

		
		return true;
	}

	String String::SubString(int startIndex)
	{
		String result;
		result.internalString = internalString.substr(startIndex);
		return result;
	}
	
	String String::SubString(int startIndex, int length)
	{
		String result;
		result.internalString = internalString.substr(startIndex, length);
		return result;
	}

	char *String::ToCharArray(int startIndex, int length)
	{
		char tmp[length];
		char *buf = internalString.c_str();
		for(int i = startIndex, j = 0; i < startIndex+length; i++, j++)
		{
			tmp[j] = 
		}
	}

	char *String::ToCharArray()
	{
		return internalString.c_str();
	}

	String String::ToLower()
	{
		
	}
	
	String String::ToString()
	{
		return *this;
	}

	String String::ToUpper()
	{
		
	}

	bool String::operator!=(const String right)
	{
		return !Equals(right);
	}

	bool String::operator==(const String right)
	{
		return Equals(right);
	}

	String String::operator=(const char *right)
	{
		internalString = right;
		return *this;
	}

	String String::operator=(const String right)
	{
		internalString = right.internalString;
		return *this;
	}
	
	char String::operator [](int index)
	{
		if (index < 0 || index >= internalString.length())
			throw IndexOutOfRangeException();

		return internalString[index];
	}
}
