/*****************************************************************************
 *	IPEndPoint.h															 *
 *																			 *
 *	System::Net::IPEndPoint class definition file.  						 *
 *	Copyright (c) XFX Team. All rights reserved.							 *
 *****************************************************************************/
#ifndef _SYSTEM_NET_IPENDPOINT_
#define _SYSTEM_NET_IPENDPOINT_

#include <System/Net/EndPoint.h>
#include <System/Net/IPAddress.h>

namespace System
{
	namespace Net
	{
		/**
		 * Represents a network endpoint as an IP address and a port number.
		 */
		class IPEndPoint : public EndPoint
		{
		private:
			IPAddress address;
			int port;

		public:
			IPAddress getAddress() const;
			void setAddress(IPAddress value);
			AddressFamily_t getAddressFamily() const;
			int getPort() const;
			void setPort(const int value);

			static const int MaxPort = 65535;
			static const int MinPort = 0;

			IPEndPoint(const long long address, const int port);
			IPEndPoint(IPAddress * const address, const int port);

			EndPoint * Create(SocketAddress socketAddress);
			bool Equals(Object const * const obj) const;
			int GetHashCode() const;
			SocketAddress * Serialize();
			const String ToString() const;
		};
	}
}

#endif
