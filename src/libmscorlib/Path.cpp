// Copyright (C) XFX Team
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

#include <System/FrameworkResources.h>
#include <System/IO/Path.h>
#include <System/String.h>

#include <stdlib.h>
#include <string.h>
#include <hal/fileio.h>
#include <xboxkrnl/xboxkrnl.h>

#include <sassert.h>

namespace System
{
	namespace IO
	{
#define NT_STATUS_OBJECT_NAME_NOT_FOUND long(0xC0000000 | 0x0034)
#define NT_STATUS_VOLUME_DISMOUNTED     long(0xC0000000 | 0x026E)

		typedef struct
		{
		  char cDriveLetter;
		  const char* szDevice;
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
		char extendPartitionMapping[] = 
		{ 
			  'F','G','R','S','V','W','A','B'
		};

#define NUM_OF_DRIVES (sizeof(driveMapping) / sizeof(driveMapping[0]))


		const char Path::PathSeparator = '\\';
		const char Path::DirectorySeparatorChar = '\\';

		Path::Path()
		{
			InvalidPathChars = GetInvalidPathChars();

			dirEqualsVolume = (DirectorySeparatorChar == VolumeSeparatorChar);
		}

		String Path::ChangeExtension(const String& path, const String& extension)
		{
			String oldName = GetFileNameWithoutExtension(path);
			String result = String::Empty;

			if (String::IsNullOrEmpty(extension))
				result = oldName;
			else
				result = oldName + extension;

			XRenameFile(
				const_cast<char*>((const char *)path.ToString()),
				const_cast<char*>((const char *)result.ToString())
				);
			return result;
		}

		String Path::Combine(const String& path1, const String& path2)
		{
			if (path1.Length == 0)
				return path2;

			if (path2.Length == 0)
				return path1;

			if (IsPathRooted(path2))
				return path2;

			char p1end = path1[path1.Length - 1];
			if (p1end != DirectorySeparatorChar && p1end != AltDirectorySeparatorChar && p1end != VolumeSeparatorChar)
				return path1 + &DirectorySeparatorChar + path2;

			return (path1 + path2);
		}

		void Path::GetDrive(const char* szPartition, out char* cDriveLetter)
		{
			int part_str_len = strlen(szPartition);
			int part_num;

			if (part_str_len < 19)
			{
				*cDriveLetter = 0;
				return;
			}

			part_num = atoi(szPartition + 19);
			if (part_num >= 6)
			{
				*cDriveLetter = extendPartitionMapping[part_num-6];
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

		String Path::GetFileNameWithoutExtension(const String& path)
		{
			return String(path.SubString(0, path.Length - path.IndexOf('.')));
		}

		char *Path::GetInvalidFileNameChars()
		{
			// return a new array as we do not want anyone to be able to change the values
			static char invChars[41] = { '\x00', '\x01', '\x02', '\x03', '\x04', '\x05', '\x06', '\x07',
				'\x08', '\x09', '\x0A', '\x0B', '\x0C', '\x0D', '\x0E', '\x0F', '\x10', '\x11', '\x12', 
				'\x13', '\x14', '\x15', '\x16', '\x17', '\x18', '\x19', '\x1A', '\x1B', '\x1C', '\x1D', 
				'\x1E', '\x1F', '\x22', '\x3C', '\x3E', '\x7C', ':', '*', '?', '\\', '/' };
			return invChars;
		}

		char *Path::GetInvalidPathChars()
		{
			// return a new array as we do not want anyone to be able to change the values
			static char invChars[36] = { '\x22', '\x3C', '\x3E', '\x7C', '\x00', '\x01', '\x02', '\x03', '\x04', '\x05', '\x06', '\x07',
				'\x08', '\x09', '\x0A', '\x0B', '\x0C', '\x0D', '\x0E', '\x0F', '\x10', '\x11', '\x12', 
				'\x13', '\x14', '\x15', '\x16', '\x17', '\x18', '\x19', '\x1A', '\x1B', '\x1C', '\x1D', 
				'\x1E', '\x1F' };
			return invChars;
		}

		void CheckInvalidPathChars(const String& path)
		{
			for (int i = 0; i < path.Length; i++)
			{
				int num2 = path[i];
				sassert(!(((num2 == 0x22) || (num2 == 60)) || (((num2 == 0x3e) || (num2 == 0x7c)) || (num2 == 0x20))), "Path contains invalid characters.");
			}
		}

		bool Path::IsPathRooted(const String& path)
		{
			CheckInvalidPathChars(path);
			if (((path.Length >= 1) && ((path[0] == DirectorySeparatorChar) || (path[0] == AltDirectorySeparatorChar))) ||
				((path.Length >= 2) && (path[1] == VolumeSeparatorChar)))
			{
				return true;
			}

			return false;
		}
	}
}
