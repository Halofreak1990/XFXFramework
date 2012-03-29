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
	class OperatingSystem : virtual Object
	{
	private:
		OperatingSystem();

	public:
		const PlatformID_t Platform;
		const System::Version Version;

		OperatingSystem(PlatformID_t platform, System::Version version);
		OperatingSystem(const OperatingSystem &obj);

		OperatingSystem Clone();
		bool Equals(const OperatingSystem other) const;
		int GetHashCode();
		char* ToString();

		bool operator !=(const OperatingSystem right) const;
		bool operator ==(const OperatingSystem right) const;
	};
}

#endif //_SYSTEM_OPERATINGSYSTEM_
