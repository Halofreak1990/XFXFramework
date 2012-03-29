/********************************************************
 *	FileStream.h										*
 *														*
 *	XFX FileStream definition file						*
 *	Copyright © XFX Team. All Rights Reserved			*
 ********************************************************/
#ifndef _SYSTEM_IO_FILESTREAM_
#define _SYSTEM_IO_FILESTREAM_

#include "../Types.h"
#include "Enums.h"
#include "Stream.h"

namespace System
{
	namespace IO
	{
		// Exposes a Stream around a file, supporting both synchronous and asynchronous read and write operations.
		class FileStream : public Stream, virtual Object
		{
		private:
			int handle;
			byte* _buffer;
			FileAccess_t _access;
			bool canSeek;
			bool isAsync;
			Int64 _pos;
			int _readLen;
			int _readPos;
			int _writePos;
			static const int DefaultBufferSize = 8192;

			void FlushRead();
			void FlushWrite(bool calledFromFinalizer);

		protected:
			void Dispose(bool disposing);

		public:
			bool CanRead();
			bool CanSeek();
			bool CanWrite();
			virtual bool IsAsync();
			Int64 Length();
			char* Name();
			Int64 getPosition();
			void setPosition(Int64 newPosition);

			FileStream();
			FileStream(const char* path, const FileMode_t mode);
			FileStream(const char* path, const FileMode_t mode, const FileAccess_t access);
			FileStream(const char* path, const FileMode_t mode, const FileAccess_t access, const FileShare_t share);
			FileStream(const char* path, const FileMode_t mode, const FileAccess_t access, const FileShare_t share, const int bufferSize);
			FileStream(const char* path, const FileMode_t mode, const FileAccess_t access, const FileShare_t share, const int bufferSize, const bool useAsync);
			virtual ~FileStream();

			void Flush();
			int Read(byte array[], const int offset, const int count) __attribute__((nonnull (1)));
			int ReadByte();
			Int64 Seek(const Int64 offset, const SeekOrigin_t origin);
			void SetLength(const Int64 value);
			void Write(byte array[], const int offset, const int count) __attribute__((nonnull (1)));
			void WriteByte(const byte value);
		};
	}
}

#endif //_SYSTEM_IO_FILESTREAM_
