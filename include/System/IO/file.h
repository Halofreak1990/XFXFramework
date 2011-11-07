/********************************************************
 *	File.h												*
 *														*
 *	XFX File definition file							*
 *	Copyright © XFX Team. All Rights Reserved			*
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
	class DateTime;

	namespace IO
	{
		class FileStream;
		class StreamReader;
		class StreamWriter;

		// Provides static methods for the creation, copying, deletion, moving, and opening of files, and aids in the creation of FileStream objects.
		class File : virtual Object
		{
		private:
#if ENABLE_XBOX
			static int FileAttributeInfo(char* path, PXBOX_FIND_DATA data, bool tryagain, bool returnErrorOnNotFound);
#else
			static int FileAttributeInfo(char* path, data, bool tryagain, bool returnErrorOnNotFound);
#endif

		public:
			static StreamWriter AppendText(char* path) __attribute__((nonnull (1)));
			static void Copy(char* sourceFileName, char* destFileName) __attribute__((nonnull (1, 2)));
			static void Copy(char* sourceFileName, char* destFileName, bool overwrite) __attribute__((nonnull (1, 2)));
			static FileStream Create(char* path);
			static FileStream Create(char* path, int bufferSize);
			static StreamWriter CreateText(char* path) __attribute__((nonnull (1)));
			static void Delete(char* path) __attribute__((nonnull (1)));
			static bool Exists(char* path);
			static DateTime GetCreationTime(char* path);
			static DateTime GetLastAccessTime(char* path);
			static DateTime GetLastWriteTime(char* path);
			static void Move(char* sourceFileName, char* destFileName) __attribute__((nonnull (1, 2)));
			static FileStream Open(char* path, FileMode_t mode);
			static FileStream Open(char* path, FileMode_t mode, FileAccess_t access);
			static FileStream Open(char* path, FileMode_t mode, FileAccess_t access, FileShare_t share);
			static FileStream OpenRead(char* path);
			static StreamReader OpenText(char* path) __attribute__((nonnull (1)));
			static FileStream OpenWrite(char* path);
		};
	}
}

#endif //_SYSTEM_IO_FILE_
