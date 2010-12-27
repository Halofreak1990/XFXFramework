#include <System/DateTime.h>
#include <System/IO/Directory.h>
#include <System/IO/DirectoryInfo.h>
#include <System/IO/IOException.h>
#include <System/IO/File.h>

#include <string.h>

#if ENABLE_XBOX
#include <hal/fileio.h>
#else
#endif

namespace System
{
	namespace IO
	{
		DirectoryInfo Directory::CreateDirectory(char* path)
		{
			if (path == null)
				throw ArgumentNullException("path");

			if (File::Exists(path))
				throw IOException(strcat((char*)"Cannot create ", strcat(path,(char*)" because a file with the same name already exists.")));

#if ENABLE_XBOX
			XCreateDirectory(path);
#else
#endif
		}

		void Directory::Delete(char* path)
		{
			Delete(path, false);
		}

		void Directory::Delete(char* path, bool recursive)
		{
#if ENABLE_XBOX
#else
#endif
		}

		bool Directory::Exists(char* path)
		{
			return File::Exists(path);
		}

		DateTime Directory::GetLastAccessTime(char* path)
		{
			return File::GetLastAccessTime(path);
		}

		DateTime Directory::GetLastWriteTime(char* path)
		{
			return File::GetLastWriteTime(path);
		}

		void Directory::Move(char* sourceDirName, char* destDirName)
		{
			File::Move(sourceDirName, destDirName);
		}
	}
}
