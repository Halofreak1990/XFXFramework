/*****************************************************************************
 *	DependencyProperty.h													 *
 *																			 *
 *	System::Windows::DependencyProperty definition file						 *
 *	Copyright (c) XFX Team. All rights reserved								 *
 *****************************************************************************/
#ifndef _SYSTEM_TYPE_
#define _SYSTEM_TYPE_

#include <System/String.h>
#include <System/Enums.h>

namespace System
{
	/**
	 * Represents type declarations: class types, interface types, array types, value types, enumeration types, type parameters, generic type definitions, and open or closed constructed generic types.
	 */
	class Type : public Object
	{
	public:
		const String FullName;
		const bool HasGenericParameters;
		const String Name;
		const TypeCode_t TypeCode;

		/**
		 * Initializes a new instance of the System::Type class.
		 *
		 * @param name
		 * The name of the System::Type. E.g. Object
		 *
		 * @param fullName
		 * The fully qualified name of the System::Type. E.g. System::Object
		 *
		 * @param hasGenericParameters
		 * Whether the System::Type has generic parameters. For template classes, this should be true.
		 */
		Type(const String& name, const String& fullName, const TypeCode_t typeCode, const bool hasGenericParameters = false);

		/**
		 *	Determines if the underlying system type of the current System::Type is the same as the underlying system type of the specified System::Object.
		 *
		 * @param obj
		 * The System::Object whose underlying system type is to be compared with the underlying system type of the current System::Type.
		 *
		 * @return
		 * true if the underlying system type of obj is the same as the underlying system type of the current System::Type; otherwise, false. This method also returns false if the object specified by the obj parameter is not a Type.
		 */
		bool Equals(Object const * const obj) const;
		/**
		 * Returns the hash code for this instance.
		 *
		 * @return
		 * An System::Int32 containing the hash code for this instance.
		 */
		int GetHashCode() const;
		/**
		 * Gets the underlying type code of the specified System::Type.
		 *
		 * @param type
		 * The System::Type whose underlying type code to get.
		 *
		 * @return
		 * The System::TypeCode value of the underlying type.
		 */
		static TypeCode_t GetTypeCode(const Type& type);
		/**
		 * Returns a System::String representation of this object.
		 *
		 * @return
		 * A System::String that represents this object.
		 */
		const String ToString() const;

		/**
		 * Determines whether two System::Type instances are equal.
		 *
		 * @param right
		 * The System::Type on the right side of the equality operator.
		 *
		 * @return
		 * true if the System::Type instances are equal; otherwise, false.
		 */
		bool operator ==(const Type& right) const;
		/**
		 * Determines whether two System::Type instances are not equal.
		 *
		 * @param right
		 * The System::Type on the right side of the inequality operator.
		 *
		 * @return
		 * true if the System::Type instances are not equal; otherwise, false.
		 */
		bool operator !=(const Type& right) const;
	};
}

#endif //_SYSTEM_TYPE_
