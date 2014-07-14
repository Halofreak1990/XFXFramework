/*****************************************************************************
 *	Socket.h																 *
 *																			 *
 *	System::Net::Socket class definition file								 *
 *	Based on Windows Phone Socket class.									 *
 *	Copyright (c) XFX Team. All Rights Reserved 							 *
 *****************************************************************************/
#ifndef _SYSTEM_NET_SOCKET_
#define _SYSTEM_NET_SOCKET_

#include "Enums.h"
#include "../EndPoint.h"
#include <System/Interfaces.h>
#include <System/Object.h>

#include <xboxkrnl/xboxkrnl.h>

using namespace System;

namespace System
{
	namespace Net
	{
		namespace Sockets
		{
			class SocketAsyncEventArgs;

			class Socket : public IDisposable, public Object
			{
			private:
				AddressFamily_t addressFamily;
				HANDLE handle;
				bool isConnected;
				ProtocolType_t protocolType;

			protected:
				virtual ~Socket();

				void Dispose(bool disposing);

			public:
				AddressFamily_t getAddressFamily() const;
				int Available() const;
				bool Connected() const;
				HANDLE getHandle() const;
				ProtocolType_t getProtocolType() const;
				int ReceiveBufferSize;
				EndPoint* getRemoteEndPoint() const;
				int SendBufferSize;
				short Ttl;

				Socket(AddressFamily_t addressFamily, SocketType_t socketType, ProtocolType_t protocolType);

				static void CancelConnectAsync(SocketAsyncEventArgs e);
				void Close();
				void Close(int timeOut);
				static bool ConnectAsync(SocketType_t socketType, ProtocolType_t protocolType, SocketAsyncEventArgs e);
				bool ConnectAsync(SocketAsyncEventArgs e);
				void Dispose();
				void EndConnect(IAsyncResult * asyncResult);
				void EndDisconnect(IAsyncResult * asyncResult);
				static const Type& GetType();
				bool ReceiveAsync(SocketAsyncEventArgs e);
				bool ReceiveFromAsync(SocketAsyncEventArgs e);
				bool SendAsync(SocketAsyncEventArgs e);
				bool SendToAsync(SocketAsyncEventArgs e);
				void Shutdown(SocketShutdown_t how);
			};
		}
	}
}

#endif //_SYSTEM_NET_SOCKET_
