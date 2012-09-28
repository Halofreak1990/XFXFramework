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

extern "C"
{
#include <xboxkrnl/xboxkrnl.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
}

#include <Storage/StorageContainer.h>
#include <Storage/StorageDevice.h>

namespace XFX
{
	namespace Storage
	{
		typedef struct
		{
		  char cDriveLetter;
		  char* szDevice;
		  int iPartition;
		}
		stDriveMapping;

		stDriveMapping driveMapping[] =
		{
			{ 'C', "Harddisk0\\Partition2", 2},
			{ 'D', "Cdrom0", -1},
			{ 'E', "Harddisk0\\Partition1", 1},
			{ 'X', "Harddisk0\\Partition3", 3},
			{ 'Y', "Harddisk0\\Partition4", 4},
			{ 'Z', "Harddisk0\\Partition5", 5},
		};
		char extendPartitionMapping[] = { 'F','G','R','S','V','W','A','B' };

#define NUM_OF_DRIVES (sizeof(driveMapping) / sizeof(driveMapping[0]))
#define EXTEND_PARTITION_BEGIN  6

		void GetDrive(const char* szPartition, char* cDriveLetter)
		{
		  int part_str_len = strlen(szPartition);
		  int part_num;

		  if (part_str_len < 19)
		  {
			*cDriveLetter = 0;
			return;
		  }

		  part_num = atoi(szPartition + 19);
		  if (part_num >= EXTEND_PARTITION_BEGIN)
		  {
			*cDriveLetter = extendPartitionMapping[part_num-EXTEND_PARTITION_BEGIN];
			return;
		  }
		  for (unsigned int i=0; i < NUM_OF_DRIVES; i++)
			if (strnicmp(driveMapping[i].szDevice, szPartition, strlen(driveMapping[i].szDevice)) == 0)
			{
			  *cDriveLetter = driveMapping[i].cDriveLetter;
			  return;
			}
		  *cDriveLetter = 0;
		}

		StorageDevice* StorageContainer::getStorageDevice() const
		{
			return device;
		}

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
			if (!isDisposed)
			{
				isDisposed = true;

				if (disposing)
					Disposing(this, const_cast<EventArgs*>(EventArgs::Empty));
			}
		}

		const char* StorageContainer::Path() const
		{
			// Calculate the path to this storage location
		}

		const char* StorageContainer::TitleLocation()
		{
			// XBOX returns the XeImageFileName like \device\harddisk0\partition2\apps\default.xbe
			// we need to map the partitions, and strip the \default.xbe from this string

			// copy the XeImageFileName to tmp, and strip the \default.xbe
			//char *tmp = strncpy(tmp, XeImageFileName->Buffer, XeImageFileName->Length - 12);
	
			char* szTemp = (char*)malloc(256);
			char cDriveLetter = 0;
			char* szDest;

			strncpy(szTemp, XeImageFileName->Buffer + 12, XeImageFileName->Length - 12);
			szTemp[20] = 0;
			GetDrive(szTemp, &cDriveLetter);
	
			strncpy(szTemp, XeImageFileName->Buffer + 29, XeImageFileName->Length - 29);
			szTemp[XeImageFileName->Length - 29] = 0;

			sprintf(szDest, "%c:\\%s", cDriveLetter, szTemp);
			return szDest;
		}

		const char* StorageContainer::TitleName() const
		{
			//! TODO: Read the Title field from the XBE header
		}
	}
}
