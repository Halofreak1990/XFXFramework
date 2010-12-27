// Copyright (C) 2010-2012, XFX Team
// All rights reserved.
// 
// Redistribution and use in source and binary forms, with or without 
// modification, are permitted provided that the following conditions are met:
// 
//* Redistributions of source code must retain the above copyright 
//notice, this list of conditions and the following disclaimer.
//* Redistributions in binary form must reproduce the above copyright 
//notice, this list of conditions and the following disclaimer in the 
//documentation and/or other materials provided with the distribution.
//* Neither the name of the copyright holder nor the names of any 
//contributors may be used to endorse or promote products derived from 
//this software without specific prior written permission.
// 
// THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS" 
// AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE 
// IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE 
// ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT OWNER OR CONTRIBUTORS BE 
// LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR 
// CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF 
// SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS 
// INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN 
// CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) 
// ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE 
// POSSIBILITY OF SUCH DAMAGE.

#include <System/IO/Stream.h>
#include <System/IO/StreamAsyncResult.h>
#include <system/Exception.h>

namespace System
{
	namespace IO
	{
		Stream::Stream()
		{
			_asyncActiveCount = 1;
		}

		bool Stream::CanTimeOut()
		{
			return false;
		}

		IAsyncResult* Stream::BeginRead(byte buffer[], int offset, int count, ASyncCallback callback, Object* state)
		{
			if(!CanRead())
				throw NotSupportedException("This stream does not support reading");

			StreamAsyncResult result = StreamAsyncResult(state);
			try
			{
				int nbytes = Read(buffer, offset, count);
				result.SetComplete(null, nbytes);
			}
			catch (Exception e)
			{
				result.SetComplete(&e, 0);
			}

			return result;
		}

		IAsyncResult* Stream::BeginWrite(byte buffer[], int offset, int count, ASyncCallback callback, Object* state)
		{
			if(!CanWrite())
				throw NotSupportedException("This stream does not support writing");

			StreamAsyncResult result = StreamAsyncResult(state);
			try
			{
				Write (buffer, offset, count);
				result.SetComplete(null);
			}
			catch (Exception e)
			{
				result.SetComplete(&e);
			}

			callback(result);

			return result;
		}

		void Stream::Close()
		{
			Dispose(true);
		}

		void Stream::Dispose()
		{
			Close();
		}

		int Stream::EndRead(IAsyncResult* asyncResult)
		{
			StreamAsyncResult result = (StreamAsyncResult)asyncResult;
			if (result.NBytes() == -1)
				throw ArgumentException("Invalid IAsyncResult", "asyncResult");

			if (result.Done)
				throw InvalidOperationException("EndRead already called.");

			result.Done = true;
			if (result.Exception_() != null)
				throw result.Exception_();

			return result.NBytes();
		}

		void Stream::EndWrite(IAsyncResult* asyncResult)
		{
			StreamAsyncResult result = (StreamAsyncResult)asyncResult;
			if (result.NBytes() != -1)
				throw ArgumentException("Invalid IAsyncResult", "asyncResult");

			if (result.Done)
				throw InvalidOperationException("EndWrite already called.");

			result.Done = true;
			if (result.Exception_() != null)
				throw result.Exception_();
		}

		int Stream::ReadByte()
		{
			byte* buffer = new byte[1];
			if (Read(buffer, 0, 1) == 0)
			{
				return -1;
			}
			return buffer[0];
		}

		void Stream::WriteByte(byte value)
		{
			byte buffer[] = { value };
			Write(buffer, 0, 1);
		}
	}
}
