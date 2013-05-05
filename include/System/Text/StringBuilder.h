#ifndef _SYSTEM_TEXT_STRINGBUILDER_
#define _SYSTEM_TEXT_STRINGBUILDER_

#include <System/Object.h>
#include <System/Types.h>

namespace System
{
	class String;

	namespace Text
	{
		// Represents a mutable string of characters. This class cannot be inherited.
		class StringBuilder : public Object
		{
		private:
			char* stringBuffer;
			int strEnd;
			int bufferLength;
			int maxCapacity;

		public:
			StringBuilder();
			StringBuilder(const int capacity);
			StringBuilder(const int capacity, const int maxCapacity);
			StringBuilder(const String& value);
			StringBuilder(const String& value, const int capacity);
			StringBuilder(const String& value, const int startIndex, const int length, const int capacity);
			~StringBuilder();

			StringBuilder& Append(const bool value);
			StringBuilder& Append(const byte value);
			StringBuilder& Append(const char value);
			StringBuilder& Append(const char value[]);
			StringBuilder& Append(const char value[], const int startIndex, const int charCount);
			StringBuilder& Append(const double value);
			StringBuilder& Append(const short value);
			StringBuilder& Append(const int value);
			StringBuilder& Append(const long long value);
			StringBuilder& Append(const Object* value);
			StringBuilder& Append(const sbyte value);
			StringBuilder& Append(const float value);
			StringBuilder& Append(const String& value);
			StringBuilder& Append(const String& value, const int startIndex, const int count);
			StringBuilder& Append(const ushort value);
			StringBuilder& Append(const uint value);
			StringBuilder& Append(const ulong value);
			StringBuilder& AppendFormat(const char* format, ...);
			StringBuilder& AppendLine();
			StringBuilder& AppendLine(const String& value);
			void CopyTo(const int sourceIndex, char destination[], const int destinationIndex, const int count);
			int EnsureCapacity(const int capacity);
			bool Equals(Object const * const obj) const;
			bool Equals(const StringBuilder& other) const;
			int GetType() const;
			StringBuilder& Insert(const int index, const bool value);
			StringBuilder& Insert(const int index, const byte value);
			StringBuilder& Insert(const int index, const char value);
			StringBuilder& Insert(const int index, const char value[]);
			StringBuilder& Insert(const int index, const char value[], const int startIndex, const int charCount);
			StringBuilder& Insert(const int index, const double value);
			StringBuilder& Insert(const int index, const short value);
			StringBuilder& Insert(const int index, const int value);
			StringBuilder& Insert(const int index, const long long value);
			StringBuilder& Insert(const int index, const Object* value);
			StringBuilder& Insert(const int index, const sbyte value);
			StringBuilder& Insert(const int index, const float value);
			StringBuilder& Insert(const int index, const String& value);
			StringBuilder& Insert(const int index, const String& value, const int count);
			StringBuilder& Insert(const int index, const ushort value);
			StringBuilder& Insert(const int index, const uint value);
			StringBuilder& Insert(const int index, const ulong value);
			StringBuilder& Remove(const int startIndex, const int length);
			StringBuilder& Replace(const char oldChar, const char newChar);
			StringBuilder& Replace(const char oldChar, const char newChar, const int startIndex, const int count);
			StringBuilder& Replace(const String& oldValue, const String& newValue);
			StringBuilder& Replace(const String& oldValue, const String& newValue, const int startIndex, const int count);
			const char* ToString() const;
			const char* ToString(const int startIndex, const int length);

			bool operator==(const StringBuilder& right) const;
			bool operator!=(const StringBuilder& right) const;
		};
	}
}

#endif //_SYSTEM_TEXT_STRINGBUILDER_
