#include <System/Boolean.h>

namespace System
{
	const char* Boolean::True = "True";
	const char* Boolean::False = "False";

	Boolean::Boolean(const bool &obj)
	{
		value = obj;
	}

	bool Boolean::operator !=(bool right)
	{
		return (value != right);
	}

	bool Boolean::operator !=(Boolean right)
	{
		return (value != right.value);
	}

	bool Boolean::operator ==(bool right)
	{
		return (value == right);
	}

	bool Boolean::operator ==(Boolean right)
	{
		return (value == right.value);
	}

	Boolean Boolean::operator =(bool right)
	{
		value = right;
		return *this;
	}

	Boolean Boolean::operator =(Boolean right)
	{
		value = right.value;
		return *this;
	}
}
