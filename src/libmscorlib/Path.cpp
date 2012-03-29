#include <System/IO/Path.h>
#include <System/String.h>
#include <stdlib.h>
#include <string.h>
#include <hal/fileio.h>
#include <xboxkrnl/xboxkrnl.h>

#include <sassert.h>

#if DEBUG
#include <stdio.h>
#endif

#define NT_STATUS_OBJECT_NAME_NOT_FOUND long(0xC0000000 | 0x0034)
#define NT_STATUS_VOLUME_DISMOUNTED     long(0xC0000000 | 0x026E)

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
char extendPartitionMapping[] = 
{ 
      'F','G','R','S','V','W','A','B'
};

#define NUM_OF_DRIVES (sizeof(driveMapping) / sizeof(driveMapping[0]))

namespace System
{
	namespace IO
	{
		const char Path::PathSeparator = '\\';
		const char Path::DirectorySeparatorChar = '\\';

		Path::Path()
		{
			InvalidPathChars = GetInvalidPathChars();

			dirEqualsVolume = (DirectorySeparatorChar == VolumeSeparatorChar);
		}

		char* Path::ChangeExtension(char* path, char* extension)
		{
			char* oldname = GetFileNameWithoutExtension(path);
			char* tmp[] = { oldname, extension};
			XRenameFile(path, String::Concat(tmp));
			return String::Concat(tmp);
		}

		char* Path::Combine(char* path1, char* path2)
		{
			//sassert(path1 != null, "path1 cannot be null.");

			if (path1 == null)
			{
#if DEBUG
				printf("ARGUMENT_NULL in function %s, at line %i in file %s, argument \"%s\"\n", __FUNCTION__, __LINE__, __FILE__, "path1");
#endif
				return path2;
			}

			if (path2 == null)
			{
#if DEBUG
				printf("ARGUMENT_NULL in function %s, at line %i in file %s, argument \"%s\"\n", __FUNCTION__, __LINE__, __FILE__, "path2");
#endif
				return path1;
			}

			if ((sizeof(path1)/sizeof(char)) == 0)
				return path2;

			if ((sizeof(path2)/sizeof(char)) == 0)
				return path1;

			if (IsPathRooted(path2))
				return path2;

			char p1end = path1[(sizeof(path2)/sizeof(char)) - 1];
			if (p1end != DirectorySeparatorChar && p1end != AltDirectorySeparatorChar && p1end != VolumeSeparatorChar)
				return strcat(strcat(path1, (const char*)DirectorySeparatorChar), path2);

			return strcat(path1, path2);
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

		bool Path::IsPathRooted(char* path)
		{
			if (path == null || (sizeof(path)/sizeof(char)) == 0)
				return false;

			/* FIXME: check for InvalidPathChars in path
			if (path.IndexOfAny (InvalidPathChars) != -1)
			{
#if DEBUG
				throw new ArgumentException ("Illegal characters in path.");
#endif
			}*/

			char c = path [0];
			return (c == DirectorySeparatorChar || c == AltDirectorySeparatorChar ||
				(!dirEqualsVolume && (sizeof(path)/sizeof(char)) > 1 && path[1] == VolumeSeparatorChar));
		}
	}
}
