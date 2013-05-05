/********************************************************
 *	OperatingSystem.h									*
 *														*
 *	XFX OperatingSystem definition file					*
 *	Copyright © XFX Team. All Rights Reserved			*
 ********************************************************/
#ifndef _SYSTEM_OPERATINGSYSTEM_
#define _SYSTEM_OPERATINGSYSTEM_

#include "Enums.h"
#include <System/Object.h>
#include <System/Version.h>

namespace System
{
	// Represents information about an operating system, such as the version and platform identifier. This class cannot be inherited.
	class OperatingSystem : public Object
	{
	private:
		OperatingSystem();

	public:
		const PlatformID_t Platform;
		const System::Version Version;

		OperatingSystem(const PlatformID_t platform, const System::Version version);
		OperatingSystem(const OperatingSystem &obj);

		OperatingSystem Clone() const;
		bool Equals(const OperatingSystem other) const;
		int GetHashCode() const;
		int GetType() const;
		const char* ToString() const;

		bool operator !=(const OperatingSystem& right) const;
		bool operator ==(const OperatingSystem& right) const;
	};
}

#endif //_SYSTEM_OPERATINGSYSTEM_
