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

#include <System/Net/Sockets/Socket.h>
#include <System/Net/Sockets/SocketAsyncEventArgs.h>
#include <System/Threading.h>
#include <System/Type.h>

using namespace System::Threading;

namespace System
{
	namespace Net
	{
		namespace Sockets
		{
			const Type SocketTypeInfo("Socket","System::Net::Sockets", TypeCode::Object);

			AddressFamily_t Socket::getAddressFamily()
			{
				return addressFamily;
			}

			HANDLE Socket::getHandle()
			{
				return handle;
			}

			Socket::Socket(AddressFamily_t addressFamily, SocketType_t socketType, ProtocolType_t protocolType)
				: addressFamily(addressFamily)
			{
				// TODO: implement remainder
			}

			bool Socket::ConnectAsync(SocketType_t socketType, ProtocolType_t protocolType, SocketAsyncEventArgs e)
			{
				// TODO: implement
			}

			bool Socket::ConnectAsync(SocketAsyncEventArgs e)
			{
				// TODO: implement
			}

			void Socket::Close()
			{
				// TODO: implement
			}

			void Socket::Close(int timeOut)
			{
				// TODO: implement
			}

			void Socket::Dispose()
			{
				// TODO: implement
			}

			void Socket::EndConnect(IAsyncResult* asyncResult)
			{
				// TODO: implement
			}

			void Socket::EndDisconnect(IAsyncResult* asyncResult)
			{
				// TODO: implement
			}

			const Type& Socket::GetType()
			{
				return SocketTypeInfo;
			}
		}
	}
}
