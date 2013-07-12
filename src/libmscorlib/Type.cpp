#include <System/Type.h>

namespace System
{
	Type::Type(const String& name, const String& fullName, const TypeCode_t typeCode, const bool hasGenericParameters)
		: FullName(fullName), HasGenericParameters(hasGenericParameters), Name(name), TypeCode(typeCode)
	{
	}

	bool Type::Equals(Object const * const obj) const
	{
		return is(obj, this) ? *this == *(Type *)obj : false;
	}

	int Type::GetHashCode() const
	{
		return FullName.GetHashCode() + (int)HasGenericParameters + Name.GetHashCode() + (int)this->TypeCode;
	}

	TypeCode_t Type::GetTypeCode(const Type& type)
	{
		return type.TypeCode;
	}

	const String Type::ToString() const
	{
	}

	bool Type::operator ==(const Type& right) const
	{
		return (FullName == right.FullName) && (HasGenericParameters == right.HasGenericParameters) && 
			   (Name == right.Name) && (this->TypeCode == right.TypeCode);
	}

	bool Type::operator !=(const Type& right) const
	{
		return (FullName != right.FullName) || (HasGenericParameters == right.HasGenericParameters) ||
			   (Name != right.Name) || (this->TypeCode != right.TypeCode);
	}
}
