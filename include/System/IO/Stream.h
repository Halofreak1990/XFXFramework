/********************************************************
 *	Stream.h											*
 *														*
 *	XFX Stream definition file							*
 *	Copyright © XFX Team. All Rights Reserved			*
 ********************************************************/
#ifndef _SYSTEM_IO_STREAM_
#define _SYSTEM_IO_STREAM_

#include <System/Types.h>
#include "Enums.h"
#include <System/Delegates.h>
#include <System/Interfaces.h>

namespace System
{
	class WaitHandle;

	namespace IO
	{
		// Provides a generic view of a sequence of bytes.
		class Stream : public IDisposable, virtual Object
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
			virtual Int64 Length();
			Int64 Position;
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
			virtual int Read(byte buffer[], int offset, int count);
			virtual int ReadByte();
			virtual Int64 Seek(Int64 offset, SeekOrigin_t origin);
			virtual void SetLength(Int64 value);
			virtual void Write(byte buffer[], int offset, int count);
			virtual void WriteByte(byte value);
		};
	}
}

#endif //_SYSTEM_IO_STREAM_
