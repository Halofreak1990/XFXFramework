#include <System/Net/Sockets/Socket.h>
#include <System/Net/Sockets/SocketAsyncEventArgs.h>
#include <System/Threading.h>

using namespace System::Threading;

namespace System
{
	namespace Net
	{
		namespace Sockets
		{
			AddressFamily_t Socket::getAddressFamily()
			{
				return addressFamily;
			}

			HANDLE Socket::getHandle()
			{
				return handle;
			}

			Socket::Socket(AddressFamily_t addressFamily, SocketType_t socketType, ProtocolType_t protocolType)
			{
				this->addressFamily = addressFamily;

			}

			bool Socket::ConnectAsync(SocketType_t socketType, ProtocolType_t protocolType, SocketAsyncEventArgs e)
			{
			}

			bool Socket::ConnectAsync(SocketAsyncEventArgs e)
			{
			}

			void Socket::Close()
			{
			}

			void Socket::Close(int timeOut)
			{
			}

			void Socket::Dispose()
			{
			}

			void Socket::EndConnect(IAsyncResult* asyncResult)
			{
			}

			void Socket::EndDisconnect(IAsyncResult* asyncResult)
			{
			}
		}
	}
}
