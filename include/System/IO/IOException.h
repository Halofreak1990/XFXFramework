/********************************************************
 *	IOException.h										*
 *														*
 *	XFX IOException definition file						*
 *	Copyright © XFX Team. All Rights Reserved			*
 ********************************************************/
#ifndef _SYSTEM_IO_IOEXCEPTION_
#define _SYSTEM_IO_IOEXCEPTION_

#include "../Exception.h"

namespace System
{
	namespace IO
	{
		/// <summary>
		/// The exception that is thrown when an I/O error occurs.
		/// <summary>
		class IOException : public SystemException
		{
		public:
			IOException();
			IOException(char* message);
		};

		/// <summary>
		/// The exception that is thrown when part of a file or directory cannot be found.
		/// </summary>
		class DirectoryNotFoundException : public IOException
		{
		public:
			DirectoryNotFoundException();
			DirectoryNotFoundException(char* message);
		};

		/// <summary>
		/// The exception that is thrown when reading is attempted past the end of a stream.
		/// </summary>
		class EndOfStreamException : public IOException
		{
		public:
			EndOfStreamException();
			EndOfStreamException(char* message);
		};

		/// <summary>
		/// The exception that is thrown when an attempt to access a file that does not exist on disk fails.
		/// </summary>
		class FileNotFoundException : public IOException
		{
		public:
			FileNotFoundException();
			FileNotFoundException(char* message);
		};

		/// <summary>
		/// The exception that is thrown when a pathname or filename is longer than the system-defined maximum length.
		/// </summary>
		class PathTooLongException : public IOException
		{
		public:
			PathTooLongException();
			PathTooLongException(char* message);
		};
	}
}

#endif //_SYSTEM_IO_IOEXCEPTION_
