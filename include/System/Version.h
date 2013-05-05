/********************************************************
 *	Version.h											*
 *														*
 *	XFX Version definition file							*
 *	Copyright © XFX Team. All Rights Reserved			*
 ********************************************************/
#ifndef _SYSTEM_VERSION_
#define _SYSTEM_VERSION_

#include "Interfaces.h"

namespace System
{
	// Represents the version number for a common language runtime assembly.
	class Version : public IComparable<Version>, public IEquatable<Version>, public Object
	{
	public:
		const int Build;
		const int Major;
		const int Minor;
		const int Revision;

		Version(const int major, const int minor);
		Version(const int major, const int minor, const int build);
		Version(const int major, const int minor, const int build, const int revision);
		Version(const Version &obj);

		Version Clone() const;
		int CompareTo(const Version value) const;
		bool Equals(Object const * const obj) const;
		bool Equals(const Version obj) const;
		int GetHashCode() const;
		int GetType() const;
		const char* ToString() const;
		const char* ToString(const int fieldCount) const;

		bool operator !=(const Version& other) const;
		bool operator  <(const Version& other) const;
		bool operator <=(const Version& other) const;
		bool operator ==(const Version& other) const;
		bool operator  >(const Version& other) const;
		bool operator >=(const Version& other) const;
	};
}

#endif //_SYSTEM_VERSION_
