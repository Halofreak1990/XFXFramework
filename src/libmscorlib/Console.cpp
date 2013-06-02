#include <System/Console.h>
#include <System/Environment.h>
#include <System/FrameworkResources.h>

extern "C" 
{
#include <openxdk/debug.h>
}

#include <sassert.h>

namespace System
{
	void Console::Clear()
	{
		debugClearScreen();
	}

	void Console::Write(const bool value)
	{
		if (value)
			debugPrint("true");
		else
			debugPrint("false");
	}

	void Console::Write(const char value)
	{
		debugPrint("%c", value);
	}

	void Console::Write(const char value[])
	{
		debugPrint(const_cast<char *>(value));
	}

	void Console::Write(const char value[], const int index, const int count)
	{
		sassert(value != null, FrameworkResources::ArgumentNull_Generic);

		//sassert(index + count < Array::Length(value), "index + count are out of range of the array.");

		for (int i = index; i < (index + count); i++)
			debugPrint("%c", value[i]);
	}

	void Console::Write(const double value)
	{
		debugPrint("%f", value);
	}

	void Console::Write(const int value)
	{
		debugPrint("%i", value);
	}

	void Console::Write(const Object* value)
	{
		Write(value->ToString());
	}

	void Console::Write(const String& value)
	{
		debugPrint((char *)((const char *)value.ToString()));
	}

	void Console::WriteLine()
	{
		debugPrint(const_cast<char*>(Environment::NewLine));
	}

	void Console::WriteLine(const bool value)
	{
		Console::Write(value);
		Console::WriteLine();
	}

	void Console::WriteLine(const char value)
	{
		Console::Write(value);
		Console::WriteLine();
	}

	void Console::WriteLine(const char value[])
	{
		Console::Write(value);
		Console::WriteLine();
	}

	void Console::WriteLine(const char value[], const int index, const int count)
	{
		Console::Write(value);
		Console::WriteLine();
	}

	void Console::WriteLine(const double value)
	{
		Console::Write(value);
		Console::WriteLine();
	}

	void Console::WriteLine(const int value)
	{
		Console::Write(value);
		Console::WriteLine();
	}

	void Console::WriteLine(const Object* value)
	{
		Console::Write(value);
		Console::WriteLine();
	}

	void Console::WriteLine(const String& value)
	{
		Console::Write(value);
		Console::WriteLine();
	}
}
