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

#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <netdb.h>

using namespace System::Threading;

namespace System
{
	namespace Net
	{
		namespace Sockets
		{
			const Type SocketTypeInfo("Socket","System::Net::Sockets", TypeCode::Object);

			AddressFamily_t Socket::getAddressFamily() const
			{
				return addressFamily;
			}

			int Socket::Available() const
			{
				// TODO: implement
			}

			bool Socket::Connected() const
			{
				return isConnected;
			}

			HANDLE Socket::getHandle() const
			{
				return handle;
			}

			ProtocolType_t Socket::getProtocolType() const
			{
				return protocolType;
			}

			EndPoint* Socket::getRemoteEndPoint() const
			{

			}

			Socket::Socket(AddressFamily_t addressFamily, SocketType_t socketType, ProtocolType_t protocolType)
				: addressFamily(addressFamily), protocolType(protocolType)
			{
				// TODO: implement remainder
			}

			void Socket::Close()
			{
				// TODO: implement
			}

			void Socket::Close(int timeOut)
			{
				// TODO: implement
			}

			bool Socket::ConnectAsync(SocketType_t socketType, ProtocolType_t protocolType, SocketAsyncEventArgs e)
			{
				// TODO: implement
			}

			bool Socket::ConnectAsync(SocketAsyncEventArgs * const e)
			{
				// NO check is made whether e != null in MS.NET (NRE is thrown in such case)
				if (disposed && closed)
				{
					throw new ObjectDisposedException(GetType().ToString());
				}

				sassert(e->RemoteEndPoint != null, String::Format("remoteEP: %s", FrameworkResources::ArgumentNull_Generic));

				return ConnectAsyncReal(e);
			}

			void Socket::Dispose()
			{
				// TODO: implement
			}

			void Socket::EndConnect(IAsyncResult* asyncResult)
			{
				sassert(!disposed || !closed, "");

				sassert(asyncResult != null, String::Format("asyncResult: %s", FrameworkResources::ArgumentNull_Generic));

				SocketAsyncResult * req = as<SocketAsyncResult *>(asyncResult);

				sassert(req != null, "Invalid IAsyncResult");

				if (Interlocked::CompareExchange(&req.EndCalled, 1, 0) == 1)
				{
					throw InvalidAsyncOp("EndConnect");
				}

				if (!asyncResult->IsCompleted())
				{
					asyncResult->AsyncWaitHandle.WaitOne();
				}

				req.CheckIfThrowDelayedException();
			}

			void Socket::EndDisconnect(IAsyncResult* asyncResult)
			{
				if (disposed && closed)
				{
				throw new ObjectDisposedException(GetType ().ToString ());
				}

				if (asyncResult == null)
				{
					throw new ArgumentNullException("asyncResult");
				}

				SocketAsyncResult * req = as<SocketAsyncResult *>(asyncResult);

				if (req == null)
					throw new ArgumentException ("Invalid IAsyncResult", "asyncResult");

				if (Interlocked::CompareExchange(&req.EndCalled, 1, 0) == 1)
				{
					throw InvalidAsyncOp("EndDisconnect");
				}

				if (!asyncResult->IsCompleted())
				{
					asyncResult->AsyncWaitHandle.WaitOne();
				}

				req->CheckIfThrowDelayedException();
			}

			const Type& Socket::GetType()
			{
				return SocketTypeInfo;
			}

			bool Socket::ReceiveAsync(SocketAsyncEventArgs * const e)
			{
				// NO check is made whether e != null in MS.NET (NRE is thrown in such case)
				if (disposed && closed)
				{
					throw new ObjectDisposedException(GetType ().ToString ());
				}

				// LAME SPEC: the ArgumentException is never thrown, instead an NRE is
				// thrown when e.Buffer and e.BufferList are null (works fine when one is
				// set to a valid object)
				if (e->getBuffer() == null && e->BufferList == null)
				{
					throw new NullReferenceException ("Either e.Buffer or e.BufferList must be valid buffers.");
				}

				e->curSocket = this;
				SocketOperation op = (e->getBuffer() != null) ? SocketOperation::Receive : SocketOperation::ReceiveGeneric;
				e->Worker.Init (this, e, op);
				SocketAsyncResult res = e->Worker.result;

				if (e->getBuffer() != null)
				{
					res.Buffer = e->getBuffer();
					res.Offset = e->getOffset();
					res.Size = e->Count();
				}
				else
				{
					res.Buffers = e->BufferList;
				}

				res.SockFlags = e->SocketFlags;
				int count;

				lock (readQ)
				{
					readQ.Enqueue(e->Worker);
					count = readQ.Count;
				}

				if (count == 1)
				{
					// Receive takes care of ReceiveGeneric
					socket_pool_queue(Worker.Dispatcher, res);
				}

				return true;
			}

			bool Socket::ReceiveFromAsync(SocketAsyncEventArgs * const e)
			{
				if (disposed && closed)
				{
					throw new ObjectDisposedException(GetType ().ToString ());
				}
				
				// We do not support recv into multiple buffers yet
				if (e->getBufferList() != null)
				{
					throw new NotSupportedException("Mono doesn't support using BufferList at this point.");
				}

				if (e->RemoteEndPoint == null)
				{
					throw new ArgumentNullException("remoteEP", "Value cannot be null.");
				}
				
				e->curSocket = this;
				e->Worker.Init(this, e, SocketOperation::ReceiveFrom);
				SocketAsyncResult res = e->Worker.result;
				res.Buffer = e->getBuffer();
				res.Offset = e->getOffset();
				res.Size = e->Count();
				res.EndPoint = e->RemoteEndPoint;
				res.SockFlags = e->SocketFlags;
				int count;

				lock (readQ)
				{
					readQ.Enqueue(e.Worker);
					count = readQ.Count;
				}

				if (count == 1)
				{
					socket_pool_queue (Worker.Dispatcher, res);
				}

				return true;
			}

			bool Socket::SendAsync(SocketAsyncEventArgs * const e)
			{
				// NO check is made whether e != null in MS.NET (NRE is thrown in such case)
				if (disposed && closed)
				{
					throw new ObjectDisposedException (GetType ().ToString ());
				}

				if (e->getBuffer() == null && e->BufferList == null)
				{
					throw new NullReferenceException("Either e.Buffer or e.BufferList must be valid buffers.");
				}

				e->curSocket = this;
				SocketOperation op = (e->getBuffer() != null) ? SocketOperation::Send : SocketOperation::SendGeneric;
				e->Worker.Init(this, e, op);
				SocketAsyncResult res = e->Worker.result;

				if (e->getBuffer() != null)
				{
					res.Buffer = e->getBuffer();
					res.Offset = e->getOffset();
					res.Size = e->Count();
				}
				else
				{
					res.Buffers = e->BufferList;
				}

				res.SockFlags = e->SocketFlags;
				int count;

				lock (writeQ)
				{
					writeQ.Enqueue(e.Worker);
					count = writeQ.Count;
				}

				if (count == 1)
				{
					// Send takes care of SendGeneric
					socket_pool_queue(Worker.Dispatcher, res);
				}

				return true;
			}

			bool Socket::SendToAsync(SocketAsyncEventArgs * const e)
			{
				// NO check is made whether e != null in MS.NET (NRE is thrown in such case)
				if (disposed && closed)
				{
					throw new ObjectDisposedException (GetType().ToString());
				}

				if (e->BufferList != null)
				{
					throw new NotSupportedException ("Mono doesn't support using BufferList at this point.");
				}

				if (e->RemoteEndPoint == null)
				{
					throw new ArgumentNullException("remoteEP", "Value cannot be null.");
				}

				e->curSocket = this;
				e->Worker.Init(this, e, SocketOperation::SendTo);
				SocketAsyncResult res = e->Worker.result;
				res.Buffer = e->getBuffer();
				res.Offset = e->getOffset();
				res.Size = e->Count;
				res.SockFlags = e->SocketFlags;
				res.EndPoint = e->RemoteEndPoint;
				int count;

				lock (writeQ)
				{
					writeQ.Enqueue(e->Worker);
					count = writeQ.Count;
				}

				if (count == 1)
				{
					socket_pool_queue(Worker.Dispatcher, res);
				}

				return true;
			}

			void Socket::Shutdown(SocketShutdown_t how)
			{
				if (disposed && closed)
				{
					throw new ObjectDisposedException(GetType ().ToString ());
				}

				if (!isConnected)
				{
					throw new SocketException(10057); // Not connected
				}

				int error;

				// TODO: implement
				Shutdown_internal(socket, how, out error);

				if (error != 0)
				{
					throw new SocketException(error);
				}
			}
		}
	}
}
