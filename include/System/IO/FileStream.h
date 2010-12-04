/********************************************************
 *	FileStream.h										*
 *														*
 *	XFX FileStream definition file						*
 *	Copyright © XFX Team. All Rights Reserved			*
 ********************************************************/
#ifndef _FILESTREAM_
#define _FILESTREAM_

#include "../Types.h"
#include "Enums.h"
#include "Stream.h"

namespace System
{
	namespace IO
	{
		/// <summary>
		/// Exposes a Stream around a file, supporting both synchronous and asynchronous read and write
		/// operations.
		/// </summary>
		class FileStream : public Stream
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
			long long Length();
			char* Name();
			long long Position(); //get
			void Position(long long newPosition); //set

			FileStream();
			FileStream(char* path, FileMode_t mode);
			FileStream(char* path, FileMode_t mode, FileAccess_t access);
			FileStream(char* path, FileMode_t mode, FileAccess_t access, FileShare_t share);
			FileStream(char* path, FileMode_t mode, FileAccess_t access, FileShare_t share, int bufferSize);
			FileStream(char* path, FileMode_t mode, FileAccess_t access, FileShare_t share, int bufferSize, bool useAsync);
			virtual ~FileStream();

			void Flush();
			int Read(byte array[], int offset, int count);
			int ReadByte();
			long long Seek(long long offset, SeekOrigin_t origin);
			void SetLength(long long value);
			void Write(byte array[], int offset, int count);
			void WriteByte(byte value);
		};
	}
}

#endif //_FILESTREAM_
