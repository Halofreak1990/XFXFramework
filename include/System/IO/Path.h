/********************************************************
 *	Path.h												*
 *														*
 *	XFX Path definition file							*
 *	Copyright © XFX Team. All Rights Reserved			*
 ********************************************************/
#ifndef _SYSTEM_IO_PATH_
#define _SYSTEM_IO_PATH_

#include <System/Types.h>

namespace System
{
	namespace IO
	{
		/// <summary>
		/// Performs operations on char* instances that contain file or directory path information. These
		/// operations are performed in a cross-platform manner.
		/// </summary>
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

			static char* ChangeExtension(char* path, char* extension);
			static char* Combine(char* path1, char* path2) __attribute__((nonnull (1, 2)));;
			static char* GetDirectoryName(char* path);
			static char* GetExtension(char* path);
			static char* GetFileName(char* path);
			static char* GetFileNameWithoutExtension(char* path);
			static char* GetFullPath(char* path);
			static char *GetInvalidPathChars();
			static char* GetPathRoot(char* path);
			static char* GetTempFileName();
			static char* GetTempPath();
			static bool HasExtension(char* path);
			static bool IsPathRooted(char* path);
		};
	}
}

#endif //_SYSTEM_IO_PATH_
