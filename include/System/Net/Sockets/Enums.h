/*****************************************************************************
 *	Enums.h 																 *
 *																			 *
 *	System::Net::Sockets enumerations definition file.  					 *
 *	Copyright (c) XFX Team. All rights reserved.							 *
 *****************************************************************************/
#ifndef _SYSTEM_NET_SOCKETS_ENUMS_
#define _SYSTEM_NET_SOCKETS_ENUMS_

namespace System
{
	namespace Net
	{
		namespace Sockets
		{
			/**
			 * Specifies the addressing scheme that an instance of the System::Net::Sockets::Socket class can use.
			 */
			struct AddressFamily
			{
				enum type
				{
					/**
					 * An address for IP version 4.
					 */
					InterNetwork = 2,
					/**
					 * An address for IP version 6.
					 */
					InterNetworkV6 = 23,
					/**
					 * An unknown address family.
					 */
					Unknown = -1,
					/**
					 * An address family has not been specified.
					 */
					Unspecified = 0
				};
			};

			/**
			 * Specifies the protocol that the System::Net::Sockets::Socket class supports.
			 */
			struct ProtocolType
			{
				enum type
				{
					/**
					 * The Transmission Control Protocol (TCP).
					 */
					Tcp = 6,
					/**
					 * The User Datagram Protocol (UDP).
					 */
					Udp = 17,
					/**
					 * An unknown protocol type.
					 */
					Unknown = -1,
					/**
					 * The protocol type is unspecified.
					 */
					Unspecified = 0
				};
			};

			/**
			 * The type of asynchronous socket operation most recently performed with this object.
			 */
			struct SocketAsyncOperation
			{
				enum type
				{
					/**
					 * A socket Connect operation.
					 */
					Connect = 2,
					/**
					 * None of the socket operations.
					 */
					None = 0,
					/**
					 * A socket Receive operation.
					 */
					Receive = 4,
					/**
					 * A socket ReceiveFrom operation.
					 */
					RecieveFrom = 5,
					/**
					 * A socket Send operation.
					 */
					Send = 7,
					/**
					 * A socket SendTo operation.
					 */
					SendTo = 9
				};
			};

			/**
			 * Defines error codes for the System::Net::Sockets::Socket class.
			 */
			struct SocketError
			{
				enum type
				{
					/**
					 * An attempt was made to access a System::Net::Sockets::Socket in a way that is forbidden by its access permissions.
					 */
					AccessDenied = 10013,
					/**
					 * Only one use of an address is normally permitted.
					 */
					AddressAlreadyInUse = 10048,
					/**
					 * The address family specified is not supported. This error is returned if the IPv6 address family was specified and the IPv6 stack is not installed on the local machine. This error is returned if the IPv4 address family was specified and the IPv4 stack is not installed on the local machine.
					 */
					AddressFamilyNotSupported = 10047,
					/**
					 * The selected IP address is not valid in this context.
					 */
					AddressNotAvailable = 10049,
					/**
					 * The nonblocking System::Net::Sockets::Socket already has an operation in progress.
					 */
					AlreadyInProgress = 10037,
					/**
					 * The connection was aborted by the .NET Framework or the underlying socket provider.
					 */
					ConnectionAborted = 10053,
					/**
					 * The remote host is actively refusing a connection.
					 */
					ConnectionRefused = 10061,
					/**
					 * The connection was reset by the remote peer.
					 */
					ConnectionReset = 10054,
					/**
					 * A required address was omitted from an operation on a System::Net::Sockets::Socket.
					 */
					DestinationAddressRequired = 10039,
					/**
					 * A graceful shutdown is in progress.
					 */
					Disconnecting = 10101,
					/**
					 * An invalid pointer address was detected by the underlying socket provider.
					 */
					Fault = 10014,
					/**
					 * The operation failed because the remote host is down.
					 */
					HostDown = 10064,
					/**
					 * No such host is known. The name is not an official host name or alias.
					 */
					HostNotFound = 11001,
					/**
					 * There is no network route to the specified host.
					 */
					HostUnreachable = 10065,
					/**
					 * A blocking operation is in progress.
					 */
					InProgress = 10036,
					/**
					 * A blocking System::Net::Sockets::Socket call was canceled.
					 */
					Interrupted = 10004,
					/**
					 * An invalid argument was supplied to a System::Net::Sockets::Socket member.
					 */
					InvalidArgument = 10022,
					/**
					 * The application has initiated an overlapped operation that cannot be completed immediately.
					 */
					IOPending = 997,
					/**
					 * The System::Net::Sockets::Socket is already connected.
					 */
					IsConnected = 10056,
					/**
					 * The datagram is too long.
					 */
					MessageSize = 10040,
					/**
					 * The network is not available.
					 */
					NetworkDown = 10050,
					/**
					 * The application tried to set an option on a connection that has already timed out.
					 */
					NetworkReset = 10052,
					/**
					 * No route to the remote host exists.
					 */
					NetworkUnreachable = 10051,
					/**
					 * No free buffer space is available for a System::Net::Sockets::Socket operation.
					 */
					NoBufferSpaceAvailable = 10055,
					/**
					 * The requested name or IP address was not found on the name server.
					 */
					NoData = 11004,
					/**
					 * The error is unrecoverable or the requested database cannot be located.
					 */
					NoRecovery = 11003,
					/**
					 * The application tried to send or receive data, and the System::Net::Sockets::Socket is not connected.
					 */
					NotConnected = 10057,
					/**
					 * The underlying socket provider has not been initialized.
					 */
					NotInitialized = 10093,
					/**
					 * A System::Net::Sockets::Socket operation was attempted on a non-socket.
					 */
					NotSocket = 10038,
					/**
					 * The overlapped operation was aborted due to the closure of the System::Net::Sockets::Socket.
					 */
					OperationAborted = 995,
					/**
					 * The address family is not supported by the protocol family.
					 */
					OperationNotSupported = 10045,
					/**
					 * Too many processes are using the underlying socket provider.
					 */
					ProcessLimit = 10067,
					/**
					 * The protocol family is not implemented or has not been configured.
					 */
					ProtocolFamilyNotSupported = 10046,
					/**
					 * The protocol is not implemented or has not been configured.
					 */
					ProtocolNotSupported = 10043,
					/**
					 * An unknown, invalid, or unsupported option or level was used with a System::Net::Sockets::Socket.
					 */
					ProtocolOption = 10042,
					/**
					 * The protocol type is incorrect for this System::Net::Sockets::Socket.
					 */
					ProtocolType = 10041,
					/**
					 * A request to send or receive data was disallowed because the System::Net::Sockets::Socket has already been closed.
					 */
					Shutdown = 10058,
					/**
					 * An unspecified System::Net::Sockets::Socket error has occurred.
					 */
					SocketError = -1,
					/**
					 * The support for the specified socket type does not exist in this address family.
					 */
					SocketNotSupported = 10044,
					/**
					 * The System::Net::Sockets::Socket operation succeeded.
					 */
					Success = 0,
					/**
					 * The network subsystem is unavailable.
					 */
					SystemNotReady = 10091,
					/**
					 * The connection attempt timed out, or the connected host has failed to respond.
					 */
					TimedOut = 10060,
					/**
					 * There are too many open sockets in the underlying socket provider.
					 */
					TooManyOpenSockets = 10024,
					/**
					 * The name of the host could not be resolved. Try again later.
					 */
					TryAgain = 11002,
					/**
					 * The specified class was not found.
					 */
					TypeNotFound = 10109,
					/**
					 * The version of the underlying socket provider is out of range.
					 */
					VersionNotSupported = 10092,
					/**
					 * An operation on a nonblocking socket cannot be completed immediately.
					 */
					WouldBlock = 10035
				};
			};

			/**
			 * Defines constants that are used by the System::Net::Sockets::Socket::Shutdown(System::Net::Sockets::SocketShutdown) method.
			 */
			struct SocketShutdown
			{
				enum type
				{
					/**
					 * Disables a System::Net::Sockets::Socket for both sending and receiving.
					 */
					Both = 2,
					/**
					 * Disables a System::Net::Sockets::Socket for receiving.
					 */
					Recieve = 0,
					/**
					 * Disables a System::Net::Sockets::Socket for sending.
					 */
					Send = 1
				};
			};

			/**
			 * Specifies the type of socket that an instance of the System::Net::Sockets::Socket class represents.
			 */
			struct SocketType
			{
				enum type
				{
					/**
					 * An unknown Socket type.
					 */
					Unknown = -1,
					/**
					 * A socket type that supports reliable, two-way, connection-based byte streams without the duplication of data and without preservation of boundaries. A System::Net::Sockets::Socket of this type communicates with a single peer and requires a remote host connection before communication can begin. This socket type uses the Transmission Control Protocol (System::Net::Sockets::ProtocolType::Tcp) and the System::Net::Sockets::AddressFamily.can be either System::Net::Sockets::AddressFamily::InterNetwork or System::Net::Sockets::AddressFamily::InterNetworkV6.
					 */
					Stream = 1,
					/**
					 * Supports datagrams, which are connectionless, unreliable messages of a fixed (typically small) maximum length. Messages might be lost or duplicated and might arrive out of order. A Socket of type System::Net::Sockets::SocketType::Dgram requires no connection prior to sending and receiving data, and can communicate with multiple peers. System::Net::Sockets::SocketType::Dgram uses the Datagram Protocol (System::Net::Sockets::ProtocolType::Udp) and the System::Net::Sockets::AddressFamily::InterNetwork or System::Net::Sockets::AddressFamily::InterNetworkV6System::Net::Sockets::AddressFamily.
					 */
					Dgram = 2,
				};
			};

			/**
			 * Specifies the addressing scheme that an instance of the System::Net::Sockets::Socket class can use.
			 */
			typedef AddressFamily::type 		AddressFamily_t;
			/**
			 * Specifies the protocols that the System::Net::Sockets::Socket class supports.
			 */
			typedef ProtocolType::type  		ProtocolType_t;
			/**
			 * The type of asynchronous socket operation most recently performed with this object.
			 */
			typedef SocketAsyncOperation::type	SocketAsyncOperation_t;
			/**
			 * Defines error codes for the System::Net::Sockets::Socket class.
			 */
			typedef SocketError::type			SocketError_t;
			/**
			 * Defines constants that are used by the System::Net::Sockets::Socket::Shutdown(System::Net::Sockets::SocketShutdown) method.
			 */
			typedef SocketShutdown::type		SocketShutdown_t;
			/**
			 * Specifies the type of socket that an instance of the System::Net::Sockets::Socket class represents.
			 */
			typedef SocketType::type			SocketType_t;
		}
	}
}

#endif //_SYSTEM_NET_ENUMS_
