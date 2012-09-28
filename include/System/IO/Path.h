/********************************************************
 *	Path.h												*
 *														*
 *	XFX Path definition file							*
 *	Copyright © XFX Team. All Rights Reserved			*
 ********************************************************/
#ifndef _SYSTEM_IO_PATH_
#define _SYSTEM_IO_PATH_

#include <System/String.h>
#include <System/Types.h>

namespace System
{
	namespace IO
	{
		// Performs operations on String instances that contain file or directory path information.
		// These operations are performed in a cross-platform manner.
		class Path
		{
		private:
			static bool dirEqualsVolume;
			static const char* InvalidPathChars;

			Path();

			static void GetDrive(const char* szPartition, out char* cDriveLetter);
			static char *Path::GetInvalidFileNameChars();

		public:
			static const char AltDirectorySeparatorChar;
			static const char DirectorySeparatorChar;
			static const char PathSeparator;
			static const char VolumeSeparatorChar;

			static String ChangeExtension(const String& path, const String& extension);
			static String Combine(const String& path1, const String& path2);
			static String GetDirectoryName(char* path);
			static String GetExtension(const String& path);
			static char* GetFileName(char* path);
			static String GetFileNameWithoutExtension(const String& path);
			static char* GetFullPath(const String& path);
			static char *GetInvalidPathChars();
			static char* GetPathRoot(char* path);
			static char* GetTempFileName();
			static char* GetTempPath();
			static bool HasExtension(const String& path);
			static bool IsPathRooted(const String& path);
		};
	}
}

#endif //_SYSTEM_IO_PATH_
