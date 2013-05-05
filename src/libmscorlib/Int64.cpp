#include <System/Int64.h>
#include <System/String.h>

#include <stdlib.h>

namespace System
{
	const long long Int64::MaxValue = 0x7FFFFFFFFFFFFFFFLL;
	const long long Int64::MinValue = 0x8FFFFFFFFFFFFFFFLL;

	Int64::Int64()
		: value(0)
	{
	}

	Int64::Int64(const Int64 &obj)
		: value(obj.value)
	{
	}

	Int64::Int64(const long long &obj)
		: value(obj)
	{
	}

	int Int64::CompareTo(const Int64 other) const
	{
		if (value > other.value)
			return 1;
		if (value < other.value)
			return -1;
		return 0;
	}

	bool Int64::Equals(Object const * const obj) const
	{
		if (!obj)
			return false;

		return is(obj, this) ? *this == *(Int64 *)obj : false;
	}

	bool Int64::Equals(const Int64 other) const
	{
		return (*this == other);
	}

	int Int64::GetHashCode() const
	{
		return (int)value;
	}

	int Int64::GetType() const
	{
		return 11;
	}

	const char* Int64::ToString() const
	{
		return String::Format("%i", value);
	}

	const char* Int64::ToString(const long long value)
	{
		return String::Format("%i", value);
	}

	bool Int64::TryParse(const String& str, out long long* result)
	{
		*result = 0;
		char* end = NULL;

		if (String::IsNullOrEmpty(str))
			return false;

		long long retval = strtoll(str, &end, 10);

		if (end)
			return false;

		*result = retval;
		return true;
	}

	Int64::operator long long() const
	{
		return value;
	}

	bool Int64::operator==(const Int64& right) const
	{
		return (value == right.value);
	}

	bool Int64::operator!=(const Int64& right) const
	{
		return (value != right.value);
	}
}
