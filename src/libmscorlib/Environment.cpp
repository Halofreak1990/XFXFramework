// Copyright (C) XFX Team
// All rights reserved.
// 
// Redistribution and use in source and binary forms, with or without 
// modification, are permitted provided that the following conditions are met:
// 
//* Redistributions of source code must retain the above copyright 
//notice, this list of conditions and the following disclaimer.
//* Redistributions in binary form must reproduce the above copyright 
//notice, this list of conditions and the following disclaimer in the 
//documentation and/or other materials provided with the distribution.
//* Neither the name of the copyright holder nor the names of any 
//contributors may be used to endorse or promote products derived from 
//this software without specific prior written permission.
// 
// THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS" 
// AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE 
// IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE 
// ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT OWNER OR CONTRIBUTORS BE 
// LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR 
// CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF 
// SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS 
// INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN 
// CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) 
// ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE 
// POSSIBILITY OF SUCH DAMAGE.

#include <System/Environment.h>
#include <System/OperatingSystem.h>
#include <System/String.h>
#include <System/Version.h>

extern "C" {
#if ENABLE_XBOX
#include <xboxkrnl/xboxkrnl.h>
#else
#endif
}

namespace System
{
	const char* Environment::GetFolderPath(const SpecialFolder_t folder)
	{
#if ENABLE_XBOX
		switch(folder)
		{
		case SpecialFolder::ApplicationData:
			return ""; //! hmmm. What to do here?
		case SpecialFolder::Favorites:
			return ""; //! XBOX doesn't have a Favorites folder.
		case SpecialFolder::Personal:
			return ""; //! XBOX doesn't do personal folders, since it lacks user accounts.
		case SpecialFolder::Programs:
			return "E:\\Apps"; //! Most modded XBOXes have this as their 'programs' directory.
		case SpecialFolder::StartMenu:
			return ""; //! XBOX doesn't have a Start Menu.
		case SpecialFolder::Startup:
			return ""; //! XBOX doesn't have a Startup folder.
		default:
			return "";
		}
#else
		switch (folder)
		{
		case SpecialFolder::Personal:
			return "~";
		}
#endif
	}

#if ENABLE_XBOX
	const char* Environment::NewLine = "\r\n";
#else
	const char* Environment::NewLine = "\n";
#endif

	OperatingSystem Environment::OSVersion()
	{
#if ENABLE_XBOX
		return OperatingSystem(PlatformID::Xbox, Version(XboxKrnlVersion->VersionMajor, XboxKrnlVersion->VersionMinor, XboxKrnlVersion->Build));
#else
		return OperatingSystem(PlatformID::Linux, Version());
#endif
	}

	int Environment::ProcessorCount()
	{
#if ENABLE_XBOX
		return 1;
#else
#endif
	}

	int Environment::TickCount()
	{
#if ENABLE_XBOX
		return KeTickCount;
#else
#endif
	}
}
