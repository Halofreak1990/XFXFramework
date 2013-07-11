/********************************************************
 *	Stream.h											*
 *														*
 *	XFX Stream definition file							*
 *	Copyright (c) XFX Team. All Rights Reserved			*
 ********************************************************/
#ifndef _SYSTEM_IO_STREAM_
#define _SYSTEM_IO_STREAM_

#include <System/Types.h>
#include "Enums.h"
#include <System/Delegates.h>
#include <System/Interfaces.h>

namespace System
{
	namespace Threading
	{
		class WaitHandle;
	}

	namespace IO
	{
		// Provides a generic view of a sequence of bytes.
		class Stream : public IDisposable, public Object
		{
		private:
			int _asyncActiveCount;

		protected:
			virtual void Dispose(bool disposing);

		public:
			virtual bool CanRead();
			virtual bool CanSeek();
			virtual bool CanTimeOut();
			virtual bool CanWrite();
			virtual long long Length();
			long long Position;
			int ReadTimeOut;
			int WriteTimeOut;
			static const Stream* Null;
			
			Stream();
			virtual ~Stream();

			virtual IAsyncResult* BeginRead(byte buffer[], int offset, int count, AsyncCallback callback, Object* state);
			virtual IAsyncResult* BeginWrite(byte buffer[], int offset, int count, AsyncCallback callback, Object* state);
			virtual void Close();
			void Dispose();
			virtual int EndRead(IAsyncResult* asyncResult);
			virtual void EndWrite(IAsyncResult* asyncResult);
			virtual void Flush();
			static int GetType();
			virtual int Read(byte buffer[], int offset, int count);
			virtual int ReadByte();
			virtual long long Seek(long long offset, SeekOrigin_t origin);
			virtual void SetLength(long long value);
			virtual void Write(byte buffer[], int offset, int count);
			virtual void WriteByte(byte value);
		};
	}
}

#endif //_SYSTEM_IO_STREAM_
