#ifndef _SYSTEM_NET_SOCKETS_ENUMS_
#define _SYSTEM_NET_SOCKETS_ENUMS_

namespace System
{
	namespace Net
	{
		namespace Sockets
		{
			struct AddressFamily
			{
				enum type
				{
					InterNetwork,
					InterNetworkV6,
					Unknown,
					Unspecified
				};
			};

			struct ProtocolType
			{
				enum type
				{
					Tcp = 6,
					Udp = 17,
					Unknown = -1,
					Unspecified = 0
				};
			};

			struct SocketAsyncOperation
			{
				enum type
				{
					Connect = 2,
					None = 0,
					Receive = 4,
					RecieveFrom = 5,
					Send = 7,
					SendTo = 9
				};
			};

			struct SocketError
			{
				enum type
				{
					AccessDenied = 10013,
					AddressAlreadyInUse = 10048,
					AddressFamilyNotSupported = 10047,
					AddressNotAvailable = 10049,

				};
			};

			struct SocketShutdown
			{
				enum type
				{
					Both,
					Recieve,
					Send
				};
			};

			struct SocketType
			{
				enum type
				{
					Unknown = -1,
					Stream = 1,
					Dgram = 2,
				};
			};

			typedef AddressFamily::type			AddressFamily_t;		// Specifies the addressing scheme that an instance of the System::Net::Sockets::Socket class can use.
			typedef ProtocolType::type			ProtocolType_t;			// Specifies the protocols that the System::Net::Sockets::Socket class supports.
			typedef SocketAsyncOperation::type	SocketAsyncOperation_t;	// The type of asynchronous socket operation most recently performed with this object.
			typedef SocketError::type			SocketError_t;			// Defines error codes for the System::Net::Sockets::Socket class.
			typedef SocketShutdown::type		SocketShutdown_t;		// Defines constants that are used by the System::Net::Sockets::Socket::Shutdown(System::Net::Sockets::SocketShutdown) method.
			typedef SocketType::type			SocketType_t;			// Specifies the type of socket that an instance of the System::Net::Sockets::Socket class represents.
		}
	}
}

#endif //_SYSTEM_NET_ENUMS_
