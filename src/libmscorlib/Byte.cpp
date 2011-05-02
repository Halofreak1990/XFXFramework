#include <System/Byte.h>
#include <System/String.h>

namespace System
{
	const byte Byte::MaxValue = 255;
	const byte Byte::MinValue = 0;

	Byte::Byte(const byte &obj)
	{
		value = obj;
	}

	int Byte::CompareTo(byte other)
	{
		if (value > other)
			return 1;
		else if (value == other)
			return 0;
		else
			return -1;
	}

	int Byte::CompareTo(Byte other)
	{
		if (value > other.value)
			return 1;
		else if (value == other.value)
			return 0;
		else
			return -1;
	}

	char* Byte::ToString()
	{
		return String::Format("%i", value);
	}

	char* Byte::ToString(byte value)
	{
		return String::Format("%i", value);
	}

	bool Byte::operator !=(byte right)
	{
		return (value != right);
	}

	bool Byte::operator !=(Byte right)
	{
		return (value != right.value);
	}

	bool Byte::operator ==(byte right)
	{
		return (value == right);
	}

	bool Byte::operator ==(Byte right)
	{
		return (value == right.value);
	}

	Byte Byte::operator =(System::byte right)
	{
		value = right;
		return *this;
	}

	Byte Byte::operator =(System::Byte right)
	{
		value = right.value;
		return *this;
	}
}
