#include <System/UInt64.h>
#include <System/String.h>

#include <stdlib.h>

namespace System
{
	const ulong UInt64::MaxValue = 0xFFFFFFFFFFFFFFFFULL;
	const ulong UInt64::MinValue = 0;

	UInt64::UInt64(const UInt64 &obj)
		: value(obj.value)
	{
	}

	UInt64::UInt64(const ulong &obj)
		: value(obj)
	{
	}

	int UInt64::CompareTo(const UInt64 other) const
	{
		if (value > other.value)
			return 1;
		if (value < other.value)
			return -1;
		return 0;
	}

	bool UInt64::Equals(const Object* obj) const
	{
		return is(obj, this) ? (*this == *(UInt64*)obj) : false;
	}

	bool UInt64::Equals(const UInt64 other) const
	{
		return (*this == other);
	}

	int UInt64::GetHashCode() const
	{
		return (int)value;
	}

	int UInt64::GetType() const
	{
		return 12;
	}

	const char* UInt64::ToString() const
	{
		return String::Format("%i", value);
	}

	const char* UInt64::ToString(const ulong value)
	{
		return String::Format("%i", value);
	}

	bool UInt64::TryParse(const String& str, out ulong result)
	{
		result = 0;
		char* end = NULL;

		if (String::IsNullOrEmpty(str))
			return false;

		ulong retval = strtoull(str.ToString(), &end, 10);

		if (end)
			return false;

		result = retval;
		return true;
	}

	bool UInt64::operator==(const UInt64& right) const
	{
		return (value == right.value);
	}

	bool UInt64::operator!=(const UInt64& right) const
	{
		return (value != right.value);
	}
}
