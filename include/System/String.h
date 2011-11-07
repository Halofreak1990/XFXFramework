/********************************************************
 *	String.h											*
 *														*
 *	XFX String definition file							*
 *	Copyright © XFX Team. All Rights Reserved			*
 ********************************************************/
#ifndef _SYSTEM_STRING_
#define _SYSTEM_STRING_

#include "Enums.h"
#include "Interfaces.h"
#include "Object.h"

namespace System
{
	// Represents text as a series of Unicode characters.
	class String : public IComparable<String>, public IEquatable<String>, virtual Object
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
		const int Length;
		static const String Empty;

		String();
		String(char c, int count);
		String(char value[], int startIndex, int length); //Note: can also be used as String(char *value, int startIndex, int length);
		String(char* value);
		String(const String &obj); // Copy constructor
		String(const char* obj);
		virtual ~String();

		String Clone();
		int CompareTo(String other);
		int Compare(String strA, String strB);
		static String Concat(String values[]);
		static char* Concat(char* values[]);
		static char* Concat(char* str1, char* str2, char* str3, char* str4);
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
		static String Join(String separator, String value[]);
		static String Join(String separator, String value[], int startIndex, int count);
		String PadLeft(int totalWidth);
		String PadLeft(int totalWidth, char paddingChar);
		String PadRight(int totalWidth);
		String PadRight(int totalWidth, char paddingChar);
		String Replace(char oldChar, char newChar);
		String Replace(char* oldValue, char* newValue);
		char** Split(String separator, int count, StringSplitOptions_t options);
		char** Split(String separator, StringSplitOptions_t options);
		char** Split(char separator[], int count, StringSplitOptions_t options);
		char** Split(char separator[], StringSplitOptions_t options);
		char** Split(char separator[], int count);
		char** Split(char separator[]);
		bool StartsWith(char* value);
		char* SubString(int startIndex);
		String SubString(int startIndex, int length);
		char* ToCharArray(int startIndex, int length);
		char* ToCharArray();
		String ToLower();
		static char* ToLower(char* str);
		char* ToString();
		String ToUpper();
		static char* ToUpper(char* str);

		bool operator!=(const String right);
		bool operator!=(char* right);
		bool operator==(const String right);
		bool operator==(char* right);
		String operator=(char* right);
		String operator=(const String right);
		String operator+(char* right);
		String operator+=(String right);
		String operator+=(char* right);
		String operator+(const String right);
		char operator [](int index);
	};

	typedef String string;
}

#endif //_SYSTEM_STRING_
