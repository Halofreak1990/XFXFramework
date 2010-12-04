#ifndef _IO_DIRECTORYINFO_
#define _IO_DIRECTORYINFO_

#include "../Types.h"
#include "FileSystemInfo.h"

namespace System
{
	namespace IO
	{
		/// <summary>
		/// Exposes instance methods for creating, moving, and enumerating through directories and subdirectories. This
		/// class cannot be inherited.
		/// </summary>
		class DirectoryInfo : public FileSystemInfo
		{
		private:
			char* current;
			char* parent;

			DirectoryInfo();

		public:
			bool Exists();
			char* Name();
			DirectoryInfo Parent();
			DirectoryInfo Root();

			DirectoryInfo(const char* path, bool junk);

			void Create();
			DirectoryInfo CreateSubDirectory(const char* path);
			void Delete();
			void Delete(bool recursive);
			DirectoryInfo *GetDirectories();
			DirectoryInfo *GetDirectories(const char* searchPattern);
			FileSystemInfo *GetFileSystemInfos();
			FileSystemInfo *GetFileSystemInfos(const char* searchPatter);
			void MoveTo(const char* destDirName);
			char* ToString();
		};
	}
}

#endif //_IO_DIRECTORYINFO_
