/********************************************************
 *	Object.h											*
 *														*
 *	XFX Object definition file							*
 *	Copyright © XFX Team. All Rights Reserved			*
 ********************************************************/
#ifndef _SYSTEM_OBJECT_
#define _SYSTEM_OBJECT_

namespace System
{
	// Supports all classes in the .NET Framework class hierarchy and provides low-level services to derived classes.
	// This is the ultimate base class of all classes in the .NET Framework; it is the root of the type hierarchy.
	class Object
	{
	public:
		virtual bool Equals(Object const * const obj) const;
		static bool Equals(const Object* objA, const Object* objB);
		virtual int GetHashCode() const;
		virtual int GetType() const =0;
		static bool ReferenceEquals(const Object& objA, const Object& objB);
		virtual const char* ToString() const;

		virtual ~Object() { }
	};

	bool is(Object const * const obj1, Object const * const obj2);
}

#endif //_SYSTEM_OBJECT_
