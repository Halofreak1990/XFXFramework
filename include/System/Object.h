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
	/// <summary>
	/// Supports all classes in the .NET Framework class hierarchy and provides low-level services to derived classes.
	/// This is the ultimate base class of all classes in the .NET Framework; it is the root of the type hierarchy.
	/// </summary>
	class Object
	{
	public:
		virtual bool Equals(Object* obj);
		static bool Equals(Object* objA, Object* objB);
		virtual int GetHashCode();
		virtual char* ToString();
	};

	typedef Object object;
}

#endif //_SYSTEM_OBJECT_
