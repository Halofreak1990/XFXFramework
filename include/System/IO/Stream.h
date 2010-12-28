/********************************************************
 *	Stream.h											*
 *														*
 *	XFX Stream definition file							*
 *	Copyright © XFX Team. All Rights Reserved			*
 ********************************************************/
#ifndef _SYSTEM_IO_STREAM_
#define _SYSTEM_IO_STREAM_

#include "../Types.h"
#include "Enums.h"
#include "../Delegates.h"
#include "../Interfaces.h"

namespace System
{
	class WaitHandle;

	namespace IO
	{
		/// <summary>
		/// Provides a generic view of a sequence of bytes.
		/// </summary>
		class Stream : public IDisposable
		{
		private:
			int _asyncActiveCount;

		protected:
			virtual WaitHandle CreateWaitHandle();
			virtual void Dispose(bool disposing);

		public:
			Stream();

			virtual bool CanRead();
			virtual bool CanSeek();
			virtual bool CanTimeOut();
			virtual bool CanWrite();
			virtual Int64 Length();
			Int64 Position;
			int ReadTimeOut;
			int WriteTimeOut;
			static const Stream Null;

			virtual void Close();
			void Dispose();
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
