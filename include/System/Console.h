#ifndef _SYSTEM_CONSOLE_
#define _SYSTEM_CONSOLE_

#include <System/Object.h>
#include <System/String.h>
#include <System/Types.h>

namespace System
{
	class Console
	{
	private:
		Console();

	public:
		static void Clear();
		static void Write(const bool value);
		static void Write(const byte value);
		static void Write(const char value);
		static void Write(const char value[]);
		static void Write(const char value[], const int index, const int count);
		static void Write(const double value);
		static void Write(const int value);
		static void Write(const long long value);
		static void Write(const Object* value);
		static void Write(const float value);
		static void Write(const short value);
		static void Write(const String value);
		static void WriteLine();
		static void WriteLine(const bool value);
		static void WriteLine(const byte value);
		static void WriteLine(const char value);
		static void WriteLine(const char value[]);
		static void WriteLine(const char value[], const int index, const int count);
		static void WriteLine(const double value);
		static void WriteLine(const int value);
		static void WriteLine(const long long value);
		static void WriteLine(const Object* value);
		static void WriteLine(const float value);
		static void WriteLine(const short value);
		static void WriteLine(const String value);
	};
}

#endif //_SYSTEM_CONSOLE_
