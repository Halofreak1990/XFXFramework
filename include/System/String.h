/*****************************************************************************
 *	String.h																 *
 *																			 *
 *	XFX String definition file												 *
 *	Copyright (c) XFX Team. All Rights Reserved 							 *
 *****************************************************************************/
#ifndef _SYSTEM_STRING_
#define _SYSTEM_STRING_

#include "Enums.h"
#include "Interfaces.h"
#include "Object.h"
#include "Types.h"

namespace System
{
	/**
	 * Represents text as a series of ASCII characters.
	 */
	class String : public IComparable<String>, public IEquatable<String>, public Object
	{
	private:
		char* internalString;

	public:
		const int Length;
		static const String Empty;

		String();
		String(char c, int count);
		String(char value[], int startIndex, int length); //Note: can also be used as String(char *value, int startIndex, int length);
		String(const String &obj); // Copy constructor
		String(const char* obj);
		virtual ~String();

		String Clone() const;
		static int Compare(const String strA, const String strB);
		int CompareTo(const String other) const;
		static String Concat(const String values[], const int stringCount);
		static char* Concat(char* values[]);
		static char* Concat(char* str1, char* str2, char* str3, char* str4);
		static String Concat(String str1, String str2, String str3, String str4);
		bool Contains(char* value) const;
		bool EndsWith(const String value) const;
		bool Equals(Object const * const obj) const;
		bool Equals(const String obj) const;
		bool Equals(const String& str1, const String& str2);
		static const char* Format(const char* format, ...) FORMAT(printf, 1, 2);
		int GetHashCode() const;
		static const Type& GetType();
		int IndexOf(char value) const;
		int IndexOf(char value, int startIndex) const;
		int IndexOf(char value, int startIndex, int count) const;
		int IndexOfAny(char anyOf[], int charCount) const;
		int IndexOfAny(char anyOf[], int charCount, int startIndex) const;
		int IndexOfAny(char anyOf[], int charCount, int startIndex, int count) const;
		static bool IsNullOrEmpty(const String& value);
		static bool IsNullOrEmpty(const char* value);
		static String Join(String separator, String value[]);
		static String Join(String separator, String value[], int startIndex, int count);
		String PadLeft(int totalWidth);
		String PadLeft(int totalWidth, char paddingChar);
		String PadRight(int totalWidth);
		String PadRight(int totalWidth, char paddingChar);
		String Replace(char oldChar, char newChar);
		String Replace(char* oldValue, char* newValue);
		char** Split(const String& separator, int count, StringSplitOptions_t options) const;
		char** Split(const String& separator, StringSplitOptions_t options) const;
		char** Split(char separator[], int count, StringSplitOptions_t options) const;
		char** Split(char separator[], StringSplitOptions_t options) const;
		char** Split(char separator[], int count) const;
		char** Split(char separator[]) const;
		bool StartsWith(const String value) const;
		char* SubString(int startIndex) const;
		String SubString(int startIndex, int length) const;
		char* ToCharArray(int startIndex, int length) const;
		char* ToCharArray() const;
		String ToLower() const;
		static const char* ToLower(const char* str);
		const String ToString() const;
		String ToUpper() const;
		static const char* ToUpper(const char* str);

		operator const char*() const;
		bool operator!=(const String& right) const;
		bool operator!=(const char* right) const;
		bool operator==(const String& right) const;
		bool operator==(const char* right) const;
		String& operator=(const String& right);
		String operator+(const char* right) const;
		String operator+=(const String& right);
		String operator+=(const char* right);
		String operator+(const String& right) const;
		const char& operator[](const int index) const;
	};

	inline const String operator +(const char * left, const String& right)
	{
		return String(left) + right;
	}

	typedef String string;
}

#endif //_SYSTEM_STRING_
