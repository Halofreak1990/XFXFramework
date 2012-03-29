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
		virtual bool Equals(const Object* obj) const;
		static bool Equals(const Object* objA, const Object* objB);
		virtual int GetHashCode() const;
		virtual const char* ToString() const;
	};
}

#endif //_SYSTEM_OBJECT_
