// Copyright (C) 2010-2012, XFX Team
// All rights reserved.
// 
// Redistribution and use in source and binary forms, with or without 
// modification, are permitted provided that the following conditions are met:
// 
//     * Redistributions of source code must retain the above copyright 
//       notice, this list of conditions and the following disclaimer.
//     * Redistributions in binary form must reproduce the above copyright 
//       notice, this list of conditions and the following disclaimer in the 
//       documentation and/or other materials provided with the distribution.
//     * Neither the name of the copyright holder nor the names of any 
//       contributors may be used to endorse or promote products derived from 
//       this software without specific prior written permission.
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

extern "C" {
#if ENABLE_XBOX
#include <xboxkrnl/xboxkrnl.h>
#else
#endif
}

#include <Storage/StorageContainer.h>
#include <Storage/StorageDevice.h>

namespace XFX
{
	namespace Storage
	{
		bool StorageContainer::IsDisposed()
		{
			return isDisposed;
		}

		StorageContainer::~StorageContainer()
		{
			Dispose(false);
		}

		void StorageContainer::Delete()
		{
			containerFolder.Delete(true);
		}

		void StorageContainer::Dispose()
		{
			Dispose(true);
		}

		void StorageContainer::Dispose(bool disposing)
		{
			if (!this._isDisposed)
			{
				isDisposed = true;
				if (disposing && (Disposing != null))
				{
					Disposing(this, EventArgs::Empty);
				}
			}
		}

		char* StorageContainer::TitleLocation()
		{
#if ENABLE_XBOX
			//XBOX returns the XeImageFileName like \device\harddisk0\partition2\apps\default.xbe
			// we need to map the partitions, and strip the \default.xbe from this string

			// copy the XeImageFileName to tmp, and strip the \default.xbe
			//char *tmp = strncpy(tmp, XeImageFileName->Buffer, XeImageFileName->Length - 12);
	
			char szTemp[MAX_PATH];
			char cDriveLetter = 0;

			strncpy(szTemp, XeImageFileName->Buffer + 12, XeImageFileName->Length - 12);
			szTemp[20] = 0;
			GetDrive(szTemp, &cDriveLetter);
	
			strncpy(szTemp, XeImageFileName->Buffer + 29, XeImageFileName->Length - 29);
			szTemp[XeImageFileName->Length - 29] = 0;

			sprintf(szDest, "%c:\\%s", cDriveLetter, szTemp);
			return szDest;
#else
			GetCurrentDirectory(XBMC_MAX_PATH, szDest);
			strcat(szDest, "\\XBMC_PC.exe");
			return szDest;
#endif
		}

		char* StorageContainer::TitleName()
		{
#if ENABLE_XBOX
			//! TODO: Read the Title field from the XBE header
#else
#endif
		}
	}
}
