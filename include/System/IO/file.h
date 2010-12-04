/********************************************************
 *	File.h												*
 *														*
 *	XFX File definition file							*
 *	Copyright © XFX Team. All Rights Reserved			*
 ********************************************************/
#ifndef _FILE_
#define _FILE_

#include "Enums.h"

#if ENABLE_XBOX
#include <hal/fileio.h>
#else
#endif

namespace System
{
	class DateTime;

	namespace IO
	{
		class FileStream;
		class StreamReader;
		class StreamWriter;

		/// <summary>
		/// Provides static methods for the creation, copying, deletion, moving, and opening of files, and aids in the
		/// creation of FileStream objects.
		/// </summary>
		class File
		{
		private:
#if ENABLE_XBOX
			static int FileAttributeInfo(char* path, PXBOX_FIND_DATA data, bool tryagain, bool returnErrorOnNotFound);
#else
			static int FileAttributeInfo(char* path, data, bool tryagain, bool returnErrorOnNotFound);
#endif

		public:
			static StreamWriter AppendText(char* path);
			static void Copy(char* sourceFileName, char* destFileName);
			static void Copy(char* sourceFileName, char* destFileName, bool overwrite);
			static FileStream Create(char* path);
			static FileStream Create(char* path, int bufferSize);
			static StreamWriter CreateText(char* path);
			static void Delete(char* path);
			static bool Exists(char* path);
			static DateTime GetCreationTime(char* path);
			static DateTime GetLastAccessTime(char* path);
			static DateTime GetLastWriteTime(char* path);
			static void Move(char* sourceFileName, char* destFileName);
			static FileStream Open(char* path, FileMode_t mode);
			static FileStream Open(char* path, FileMode_t mode, FileAccess_t access);
			static FileStream Open(char* path, FileMode_t mode, FileAccess_t access, FileShare_t share);
			static FileStream OpenRead(char* path);
			static StreamReader OpenText(char* path);
			static FileStream OpenWrite(char* path);
		};
	}
}

#endif //_FILE_
