/*****************************************************************************
 *	Object.h																 *
 *																			 *
 *	XFX Object definition file												 *
 *	Copyright (c) XFX Team. All Rights Reserved 							 *
 *****************************************************************************/
#ifndef _SYSTEM_OBJECT_
#define _SYSTEM_OBJECT_

namespace System
{
	class String;

	// Supports all classes in the .NET Framework class hierarchy and provides low-level services to derived classes.
	// This is the ultimate base class of all classes in the .NET Framework; it is the root of the type hierarchy.
	class Object
	{
	public:
		virtual bool Equals(Object const * const obj) const;
		static bool Equals(Object const * const objA, Object const * const objB);
		virtual int GetHashCode() const;
		virtual int GetType() const =0;
		static bool ReferenceEquals(const Object& objA, const Object& objB);
		virtual const String& ToString() const;

		virtual ~Object() { }
	};

	// returns whether the type of obj1 matches that of obj2
	bool is(Object const * const obj1, Object const * const obj2);

	// syntax: as<[target type]>([source instance])
	template <typename T, typename U>
	U * as(T * const source);

	template<class T, class B> struct Derived_from {
		static void constraints(T* p) { B* pb = p; }
		Derived_from() { void(*p)(T*) = constraints; }
	};
}

#endif //_SYSTEM_OBJECT_
