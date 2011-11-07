#ifndef _SYSTEM_CONSOLE_
#define _SYSTEM_CONSOLE_

#include <System/Object.h>
#include <System/String.h>
#include <System/Types.h>

namespace System
{
	class Console
	{
	public:
		static void Clear();
		static void Write(bool value);
		static void Write(char value);
		static void Write(char value[]);
		static void Write(char value[], int index, int count);
		static void Write(double value);
		static void Write(int value);
		static void Write(long long value);
		static void Write(Object* value);
		static void Write(float value);
		static void Write(String value);
		static void WriteLine();
		static void WriteLine(bool value);
		static void WriteLine(char value);
		static void WriteLine(char value[]);
		static void WriteLine(char value[], int index, int count);
		static void WriteLine(double value);
		static void WriteLine(int value);
		static void WriteLine(long long value);
		static void WriteLine(Object* value);
		static void WriteLine(float value);
		static void WriteLine(String value);
	};
}

#endif //_SYSTEM_CONSOLE_
