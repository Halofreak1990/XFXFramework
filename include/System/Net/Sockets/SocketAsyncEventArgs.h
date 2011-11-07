#ifndef _SYSTEM_NET_SOCKETS_SOCKETASYNCEVENTARGS_
#define _SYSTEM_NET_SOCKETS_SOCKETASYNCEVENTARGS_

#include <System/Delegates.h>
#include <System/Exception.h>
#include "../Endpoint.h"
#include "Socket.h"
#include "Enums.h"
#include <System/Object.h>
#include <System/Types.h>

namespace System
{
	namespace Net
	{
		namespace Sockets
		{
			class SocketAsyncEventArgs : public EventArgs, virtual Object
			{
			protected:
				virtual void Oncompleted(SocketAsyncEventArgs e);
				virtual ~SocketAsyncEventArgs();

			public:
				byte* getBuffer();
				int getBytesTransferred();
				Exception* getConnectByNameError();
				Socket getConnectSocket();
				int Count();
				SocketAsyncOperation_t getLastOperation();
				int getOffset();
				EndPoint* RemoteEndPoint;
				SocketError_t SocketError;
				Object* UserToken;

				EventHandler Completed;

				SocketAsyncEventArgs();

				void Dispose();
				void SetBuffer(int offset, int count);
				void SetBuffer(byte buffer[], int offset, int count);
			};
		}
	}
}

#endif //_SYSTEM_NET_SOCKETS_SOCKETASYNCEVENTARGS_
