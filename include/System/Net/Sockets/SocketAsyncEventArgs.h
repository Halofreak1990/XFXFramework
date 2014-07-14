/*****************************************************************************
 *	SocketAsyncEventArgs.h  												 *
 *																			 *
 *	System::Net::Sockets::SocketAsyncEventArgs class definition file.		 *
 *	Copyright (c) XFX Team. All rights reserved.							 *
 *****************************************************************************/
#ifndef _SYSTEM_NET_SOCKETS_SOCKETASYNCEVENTARGS_
#define _SYSTEM_NET_SOCKETS_SOCKETASYNCEVENTARGS_

#include <System/Event.h>
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
			class SocketAsyncEventArgs : public EventArgs, public IDisposable
			{
			private:
				friend class Socket;

			protected:
				virtual void Oncompleted(SocketAsyncEventArgs* e);
				virtual ~SocketAsyncEventArgs();

			public:
				byte * getBuffer() const;
				int getBytesTransferred() const;
				//Exception* getConnectByNameError() const;
				Socket * getConnectSocket() const;
				int Count() const;
				SocketAsyncOperation_t getLastOperation() const;
				int getOffset() const;
				EndPoint* RemoteEndPoint;
				SocketError_t SocketError;
				Object* UserToken;

				EventHandler Completed;

				SocketAsyncEventArgs();

				void Dispose();
				static const Type& GetType();
				void SetBuffer(const int offset, const int count);
				void SetBuffer(byte buffer[], const int offset, const int count);
			};
		}
	}
}

#endif //_SYSTEM_NET_SOCKETS_SOCKETASYNCEVENTARGS_
