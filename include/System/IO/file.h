/********************************************************
 *	File.h												*
 *														*
 *	XFX File definition file							*
 *	Copyright (c) XFX Team. All Rights Reserved			*
 ********************************************************/
#ifndef _SYSTEM_IO_FILE_
#define _SYSTEM_IO_FILE_

#include "Enums.h"
#include "../Object.h"

#if ENABLE_XBOX
#include <hal/fileio.h>
#endif

namespace System
{
	struct DateTime;

	namespace IO
	{
		class FileStream;
		class StreamReader;
		class StreamWriter;

		// Provides static methods for the creation, copying, deletion, moving, and opening of files, and aids in the creation of FileStream objects.
		class File : public virtual Object
		{
		private:
#if ENABLE_XBOX
			static int FileAttributeInfo(const String& path, PXBOX_FIND_DATA data, bool tryagain, bool returnErrorOnNotFound);
#else
			static int FileAttributeInfo(char* path, <unknown> data, bool tryagain, bool returnErrorOnNotFound);
#endif

		public:
			static StreamWriter* AppendText(const String& path);
			static void Copy(const String& sourceFileName, const String& destFileName);
			static void Copy(const String& sourceFileName, const String& destFileName, const bool overwrite);
			static FileStream* Create(const String& path);
			static FileStream* Create(const String& path, const int bufferSize);
			static StreamWriter* CreateText(const String& path);
			static void Delete(const String& path);
			static bool Exists(const String& path);
			static DateTime GetCreationTime(const String& path);
			static DateTime GetLastAccessTime(const String& path);
			static DateTime GetLastWriteTime(const String& path);
			static void Move(const String& sourceFileName, const String& destFileName);
			static FileStream* Open(const String& path, const FileMode_t mode);
			static FileStream* Open(const String& path, const FileMode_t mode, const FileAccess_t access);
			static FileStream* Open(const String& path, const FileMode_t mode, const FileAccess_t access, const FileShare_t share);
			static FileStream* OpenRead(const String& path);
			static StreamReader* OpenText(const String& path);
			static FileStream* OpenWrite(const String& path);
		};
	}
}

#endif //_SYSTEM_IO_FILE_
