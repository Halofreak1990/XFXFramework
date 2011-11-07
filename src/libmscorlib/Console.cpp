#include <System/Console.h>
#include <System/Environment.h>

extern "C" 
{
#include <openxdk/debug.h>
}

namespace System
{
	void Console::Clear()
	{
		debugClearScreen();
	}

	void Console::Write(bool value)
	{
		if (value)
			debugPrint("true");
		else
			debugPrint("false");
	}

	void Console::Write(Object* value)
	{
		debugPrint(value->ToString());
	}

	void Console::Write(String value)
	{
		debugPrint(value.ToString());
	}

	void Console::WriteLine()
	{
		debugPrint(Environment::NewLine());
	}

	void Console::WriteLine(bool value)
	{
		Console::Write(value);
		Console::WriteLine();
	}

	void Console::WriteLine(Object* value)
	{
		Console::Write(value);
		Console::WriteLine();
	}

	void Console::WriteLine(String value)
	{
		Console::Write(value);
		Console::WriteLine();
	}
}
