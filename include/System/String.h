/********************************************************
 *	String.h											*
 *														*
 *	XFX String definition file							*
 *	Copyright © XFX Team. All Rights Reserved			*
 ********************************************************/
#ifndef _SYSTEM_STRING_
#define _SYSTEM_STRING_

#include "Enums.h"
#include "Types.h"

namespace System
{
	/// <summary>
	/// Represents text as a series of Unicode characters.
	/// </summary>
	class String
	{
	private:
		int m_arrayLength;
		char m_firstChar;
		int m_stringLength;
		static const int TrimBoth = 2;
		static const int TrimHead = 0;
		static const int TrimTail = 1;
		char* internalString;

	public:
		int Length();
		static const String Empty;

		String();
		String(char c, int count);
		String(char value[], int startIndex, int length); //Note: can also be used as String(char *value, int startIndex, int length);
		String(char* value);
		String(const String &obj); // Copy constructor
		~String();

		String Clone();
		int Compare(String strA, String strB);
		static String Concat(String values[]);
		static String Concat(String str1, String str2, String str3, String str4);
		bool Contains(char* value);
		bool EndsWith(char* value);
		bool Equals(const String obj);
		bool Equals(const String str1, const String str2);
		static char* Format(char* format, ...);
		int IndexOf(char value);
		int IndexOf(char value, int startIndex);
		int IndexOf(char value, int startIndex, int count);
		static bool IsNullOrEmpty(String value);
		static bool IsNullOrEmpty(char* value);
		static String Join(String &separator, String value[]);
		static String Join(String &separator, String value[], int startIndex, int count);
		String PadLeft(int totalWidth);
		String PadLeft(int totalWidth, char paddingChar);
		String PadRight(int totalWidth);
		String PadRight(int totalWidth, char paddingChar);
		String Replace(char oldChar, char newChar);
		String Replace(char* oldValue, char* newValue);
		char** Split(String *separator, int count, StringSplitOptions_t options);
		char** Split(String *separator, StringSplitOptions_t options);
		char** Split(char separator[], int count, StringSplitOptions_t options);
		char** Split(char separator[], StringSplitOptions_t options);
		char** Split(char separator[], int count);
		char** Split(char separator[]);
		bool StartsWith(char* value);
		static char* SubString(int startIndex);
		String SubString(int startIndex, int length);
		char *ToCharArray(int startIndex, int length);
		char *ToCharArray();
		String ToLower();
		char* ToString();
		String ToUpper();

		bool operator!=(const String right);
		bool operator!=(const char* right);
		bool operator==(const String right);
		bool operator==(const char* right);
		String operator=(const char* right);
		String operator=(const String right);
		char operator [](int index);
	};

	typedef String string;
}

#endif //_SYSTEM_STRING_
