/********************************************************
 *	FileStream.h										*
 *														*
 *	XFX FileStream definition file						*
 *	Copyright © XFX Team. All Rights Reserved			*
 ********************************************************/
#ifndef _SYSTEM_IO_FILESTREAM_
#define _SYSTEM_IO_FILESTREAM_

#include "../String.h"
#include "../Types.h"
#include "Enums.h"
#include "Stream.h"

namespace System
{
	namespace IO
	{
		// Exposes a Stream around a file, supporting both synchronous and asynchronous read and write operations.
		class FileStream : public Stream
		{
		private:
			void* handle;
			//int handle;
			byte* _buffer;
			FileAccess_t _access;
			bool canSeek;
			bool isAsync;
			long long _pos;
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
			long long getPosition();
			void setPosition(long long newPosition);

			FileStream();
			FileStream(const String& path, const FileMode_t mode);
			FileStream(const String& path, const FileMode_t mode, const FileAccess_t access);
			FileStream(const String& path, const FileMode_t mode, const FileAccess_t access, const FileShare_t share);
			FileStream(const String& path, const FileMode_t mode, const FileAccess_t access, const FileShare_t share, const int bufferSize);
			FileStream(const String& path, const FileMode_t mode, const FileAccess_t access, const FileShare_t share, const int bufferSize, const bool useAsync);
			virtual ~FileStream();

			virtual IAsyncResult* BeginRead(byte buffer[], int offset, int count, AsyncCallback callback, Object* state);
			virtual IAsyncResult* BeginWrite(byte buffer[], int offset, int count, AsyncCallback callback, Object* state);
			virtual int EndRead(IAsyncResult* asyncResult);
			virtual void EndWrite(IAsyncResult* asyncResult);
			void Flush();
			int GetType() const;
			int Read(byte array[], const int offset, const int count);
			int ReadByte();
			long long Seek(const long long offset, const SeekOrigin_t origin);
			void SetLength(const long long value);
			void Write(byte array[], const int offset, const int count);
			void WriteByte(const byte value);
		};
	}
}

#endif //_SYSTEM_IO_FILESTREAM_
