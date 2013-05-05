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
		class DirectoryInfo : public FileSystemInfo, public virtual Object
		{
		private:
			friend class Directory;

			char* current;
			char* parent;

		public:
			bool Exists() const;
			const char* Name() const;
			DirectoryInfo Parent();
			DirectoryInfo Root();

			DirectoryInfo();
			DirectoryInfo(const String& path); // Initializes a new instance of the System::IO::DirectoryInfo class on the specified path.

			// Creates a directory.
			void Create();
			// Creates a subdirectory or subdirectories on the specified path.
			// The specified path can be relative to this instance of the System::IO::DirectoryInfo class.
			DirectoryInfo CreateSubDirectory(const String& path);
			// Deletes this System::IO::DirectoryInfo if it is empty.
			void Delete();
			// Deletes this instance of a System::IO::DirectoryInfo, specifying whether to delete subdirectories and files.
			void Delete(const bool recursive);
			DirectoryInfo* GetDirectories(); // 
			DirectoryInfo* GetDirectories(const String& searchPattern);
			FileSystemInfo* GetFileSystemInfos();
			FileSystemInfo* GetFileSystemInfos(const String& searchPattern);
			int GetType() const;
			void MoveTo(const String& destDirName);
			const char* ToString() const;

			bool operator !=(const DirectoryInfo& right) const;
			bool operator ==(const DirectoryInfo& right) const;
		};
	}
}

#endif //_SYSTEM_IO_DIRECTORYINFO_
