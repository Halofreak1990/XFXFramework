/********************************************************
 *	Directory.h											*
 *														*
 *	XFX Directory class definition file					*
 *	Copyright © XFX Team. All Rights Reserved			*
 ********************************************************/
#ifndef _SYSTEM_IO_DIRECTORY_
#define _SYSTEM_IO_DIRECTORY_

#include "../Types.h"
//#include "../Object.h"
#include "../String.h"

namespace System
{
	class DateTime;

	namespace IO
	{
		class DirectoryInfo;

		// Exposes static methods for creating, moving, and enumerating through directories and subdirectories. This class cannot be inherited.
		class Directory : public virtual Object
		{
		private:
			Directory();

		public:
			static DirectoryInfo CreateDirectory(const String& path);
			static void Delete(const String& path);
			static void Delete(const String& path, const bool recursive);
			static bool Exists(const String& path);
			static DateTime GetCreationTime(const String& path);
			static String GetCurrentDirectory();
			static char** GetDirectories(const String& path);
			static char** GetDirectories(const String& path, const String& searchPattern);
			static char* GetDirectoryRoot(String& path);
			static char** GetFiles(const String& path);
			static char** GetFiles(const String& path, const String& searchPattern);
			static char** GetFileSystemEntries(const String& path);
			static char** GetFileSystemEntries(const String& path, const String& searchPattern);
			static DateTime GetLastAccessTime(const String& path);
			static DateTime GetLastWriteTime(const String& path);
			static void Move(const String& sourceDirName, const String& destDirName);
			static void SetCurrentDirectory(const String& path);
		};
	}
}

#endif //_SYSTEM_IO_DIRECTORY_
