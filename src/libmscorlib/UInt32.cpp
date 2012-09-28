#include <System/UInt32.h>
#include <System/String.h>

#include <stdlib.h>

namespace System
{
	const uint UInt32::MaxValue = 0xFFFFFFFF;
	const uint UInt32::MinValue = 0;

	UInt32::UInt32(const UInt32 &obj)
		: value(obj.value)
	{
	}

	UInt32::UInt32(const uint &obj)
		: value(obj)
	{
	}

	int UInt32::CompareTo(const UInt32 other) const
	{
		if (value > other.value)
			return 1;
		if (value < other.value)
			return -1;
		return 0;
	}

	bool UInt32::Equals(const Object* obj) const
	{
		return is(this, obj) ? (*this == *(UInt32*)obj) : false;
	}

	bool UInt32::Equals(const UInt32 other) const
	{
		return (*this == other);
	}

	int UInt32::GetHashCode() const
	{
		return (int)value;
	}

	int UInt32::GetType() const
	{
		return 10;
	}

	const char* UInt32::ToString() const
	{
		return String::Format("%i", value);
	}

	const char* UInt32::ToString(const uint value)
	{
		return String::Format("%i", value);
	}

	bool UInt32::TryParse(const String& str, out uint result)
	{
		char* end = NULL;
		result = 0;

		if (String::IsNullOrEmpty(str))
			return false;

		uint retval = strtoul(str.ToString(), &end, 10);

		if (*end)
			return false;

		result = retval;
		return true;
	}

	bool UInt32::operator==(const UInt32& right) const
	{
		return (value == right.value);
	}

	bool UInt32::operator!=(const UInt32& right) const
	{
		return (value != right.value);
	}
}
