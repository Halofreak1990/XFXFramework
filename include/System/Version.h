/********************************************************
 *	Version.h											*
 *														*
 *	XFX Version definition file							*
 *	Copyright © XFX Team. All Rights Reserved			*
 ********************************************************/
#ifndef _SYSTEM_VERSION_
#define _SYSTEM_VERSION_

namespace System
{
	/// <summary>
	/// Represents the version number for a common language runtime assembly.
	/// </summary>
	class Version
	{
	private:
		int _build;
		int _major;
		int _minor;
		int _revision;

	public:
		int Build();
		int Major();
		int Minor();
		int Revision();

		Version(int major, int minor);
		Version(int major, int minor, int build);
		Version(int major, int minor, int build, int revision);
		Version(char* version);
		Version(const Version &obj);

		Version Clone();
		int CompareTo(Version value);
		bool Equals(Version obj);
		int GetHashCode();
		char* ToString();
		char* ToString(int fieldCount);

		bool operator !=(const Version other);
		bool operator <(const Version other);
		bool operator <=(const Version other);
		bool operator ==(const Version other);
		bool operator >(const Version other);
		bool operator >=(const Version other);
	};
}

#endif //_SYSTEM_VERSION_
