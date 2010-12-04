/********************************************************
 *	OperatingSystem.h									*
 *														*
 *	XFX OperatingSystem definition file					*
 *	Copyright © XFX Team. All Rights Reserved			*
 ********************************************************/
#ifndef _OPERATINGSYSTEM_
#define _OPERATINGSYSTEM_

#include "Enums.h"

namespace System
{
	class Version;

	/// <summary>
	/// Represents information about an operating system, such as the version and platform identifier. This class
	/// cannot be inherited.
	/// </summary>
	class OperatingSystem
	{
	private:
		OperatingSystem();

	public:
		PlatformID Platform();
		Version Version_();

		OperatingSystem(PlatformID platform, Version version);

		OperatingSystem Clone();
		String ToString();
	};
}

#endif //_OPERATINGSYSTEM_
