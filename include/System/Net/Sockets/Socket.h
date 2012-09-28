/********************************************************
 *	Socket.h											*
 *														*
 *	XFX Socket class definition file					*
 *	Based on Windows Phone Socket class.				*
 *	Copyright © XFX Team. All Rights Reserved			*
 ********************************************************/
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

			class Socket : public IDisposable, public virtual Object
			{
			private:
				AddressFamily_t addressFamily;
				bool isConnected;
				HANDLE handle;

			protected:
				virtual ~Socket();

				void Dispose(bool disposing);

			public:
				AddressFamily_t getAddressFamily();
				int Available();
				bool Connected();
				HANDLE getHandle();
				ProtocolType_t getProtocolType();
				int ReceiveBufferSize;
				EndPoint* getRemoteEndPoint();
				int SendBufferSize;
				short Ttl;

				Socket(AddressFamily_t addressFamily, SocketType_t socketType, ProtocolType_t protocolType);

				static void CancelConnectAsync(SocketAsyncEventArgs e);
				void Close();
				void Close(int timeOut);
				static bool ConnectAsync(SocketType_t socketType, ProtocolType_t protocolType, SocketAsyncEventArgs e);
				bool ConnectAsync(SocketAsyncEventArgs e);
				void Dispose();
				void EndConnect(IAsyncResult* asyncResult);
				void EndDisconnect(IAsyncResult* asyncResult);
				int GetType() const;
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
