/********************************************************
 *	DirectoryInfo.h										*
 *														*
 *	XFX DirectoryInfo definition file					*
 *	Copyright © XFX Team. All Rights Reserved			*
 ********************************************************/
#ifndef _SYSTEM_IO_DIRECTORYINFO_
#define _SYSTEM_IO_DIRECTORYINFO_

#include "../Types.h"
#include "FileSystemInfo.h"

namespace System
{
	namespace IO
	{
		class Directory;

		// Exposes instance methods for creating, moving, and enumerating through directories and subdirectories. This class cannot be inherited.
		class DirectoryInfo : public FileSystemInfo, virtual Object
		{
		private:
			friend class Directory;

			char* current;
			char* parent;

			DirectoryInfo();

		public:
			bool Exists();
			char* Name();
			DirectoryInfo Parent();
			DirectoryInfo Root();

			DirectoryInfo(char* path); // Initializes a new instance of the System::IO::DirectoryInfo class on the specified path.

			void Create(); // Creates a directory.
			DirectoryInfo CreateSubDirectory(const char* path); // Creates a subdirectory or subdirectories on the specified path. The specified path can be relative to this instance of the System::IO::DirectoryInfo class.
			void Delete(); // Deletes this System::IO::DirectoryInfo if it is empty.
			void Delete(bool recursive); // Deletes this instance of a System::IO::DirectoryInfo, specifying whether to delete subdirectories and files.
			DirectoryInfo* GetDirectories(); // 
			DirectoryInfo* GetDirectories(const char* searchPattern);
			FileSystemInfo* GetFileSystemInfos();
			FileSystemInfo* GetFileSystemInfos(const char* searchPattern);
			void MoveTo(const char* destDirName);
			char* ToString();
		};
	}
}

#endif //_SYSTEM_IO_DIRECTORYINFO_
