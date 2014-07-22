// Copyright (C) XFX Team
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

#include <System/Threading/Interlocked.h>
#include <System/Net/Sockets/SocketAsyncEventArgs.h>
#include <System/Type.h>

#include <sassert.h>

using namespace System::Threading;

namespace System
{
	namespace Net
	{
		namespace Sockets
		{
			const Type SocketAsyncEventArgsTypeInfo("SocketAsyncEventArgs", "System::Net::Sockets::SocketAsyncEventArgs", TypeCode::Object);

			byte * SocketAsyncEventArgs::getBuffer() const
			{
				// TODO: implement
			}

			int SocketAsyncEventArgs::getBytesTransferred() const
			{
				// TODO: implement
			}

			Socket * SocketAsyncEventArgs::getConnectSocket() const
			{
				switch (this->SocketError)
				{
				case SocketError::AccessDenied:
					return null;
				default:
					return curSocket;
				}
			}

			int SocketAsyncEventArgs::Count() const
			{
				return count;
			}

			SocketAsyncOperation_t SocketAsyncEventArgs::getLastOperation() const
			{
				return lastOperation;
			}

			int SocketAsyncEventArgs::getOffset() const
			{
				return offset;
			}

			SocketAsyncEventArgs::SocketAsyncEventArgs()
			{
				lastOperation = SocketAsyncOperation::None;
				this->SocketError = SocketError::Success;

				// TODO: implement
			}

			SocketAsyncEventArgs::~SocketAsyncEventArgs()
			{
				if (!isDisposed)
				{
					// TODO: implement
				}
			}

			void SocketAsyncEventArgs::Dispose()
			{
				isDisposed = true;

				// TODO: implement
			}

			const Type& SocketAsyncEventArgs::GetType()
			{
				return SocketAsyncEventArgsTypeInfo;
			}
			
			void SocketAsyncEventArgs::Oncompleted(SocketAsyncEventArgs * e)
			{
				if (e == null)
				{
					return;
				}

				Completed(this, e);
			}

			void SocketAsyncEventArgs::SetBuffer(const int offset, const int count)
			{
				SetBufferInternal(getBuffer(), offset, count);
			}

			void SocketAsyncEventArgs::SetBuffer(byte buffer[], const int offset, const int count)
			{
				SetBufferInternal(buffer, offset, count);
			}

			void SocketAsyncEventArgs::SetBufferInternal(byte buffer[], int offset, int count)
			{
				if (buffer != null)
				{
					sassert(getBufferList() != null, "Buffer and BufferList properties cannot both be non-null.");

					int buflen = buffer.Length;

					sassert(offset >= 0 && offset < buflen, "");
					//throw new ArgumentOutOfRangeException("offset");

					sassert(count >= 0 && count <= buflen - offset, "");
					//throw new ArgumentOutOfRangeException("count");

					this->count = count;
					this->offset = offset;
				}

				Buffer = buffer;
			}

			void SocketAsyncEventArgs::SetLastOperation(SocketAsyncOperation_t op)
			{
				sassert(!isDisposed, "");

				sassert(Interlocked::Exchange(&inProgress, 1) == 0, "");

				lastOperation = op;
			}
		}
	}
}
