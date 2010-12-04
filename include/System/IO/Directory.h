/********************************************************
 *	Directory.h											*
 *														*
 *	XFX Directory class definition file					*
 *	Copyright © XFX Team. All Rights Reserved			*
 ********************************************************/
#ifndef _IO_DIRECTORY_
#define _IO_DIRECTORY_

#include "../Types.h"

namespace System
{
	class DateTime;

	namespace IO
	{
		class DirectoryInfo;

		/// <summary>
		/// Exposes static methods for creating, moving, and enumerating through directories and subdirectories. This
		/// class cannot be inherited.
		/// </summary>
		class Directory
		{
		private:
			Directory();

		public:
			static DirectoryInfo CreateDirectory(char* path);
			static void Delete(char* path);
			static void Delete(char* path, bool recursive);
			static bool Exists(char* path);
			static DateTime GetCreationTime(const char* path);
			static char* GetCurrentDirectory();
			static char** GetDirectories(char* path);
			static char** GetDirectories(char* path, char* searchPattern);
			static char* GetDirectoryRoot(char* path);
			static char** GetFiles(char* path);
			static char** GetFiles(char* path, char* searchPattern);
			static char** GetFileSystemEntries(char* path);
			static char** GetFileSystemEntries(char* path, char* searchPattern);
			static DateTime GetLastAccessTime(char* path);
			static DateTime GetLastWriteTime(char* path);
			static void Move(char* sourceDirName, char* destDirName);
			static void SetCurrentDirectory(char* path);
		};
	}
}

#endif //_IO_DIRECTORY_
