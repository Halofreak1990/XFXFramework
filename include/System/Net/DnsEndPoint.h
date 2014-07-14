/*****************************************************************************
 *	DnsEndPoint.h															 *
 *																			 *
 *	System::Net::DnsEndPoint class definition file. 						 *
 *	Copyright (c) XFX Team. All rights reserved.							 *
 *****************************************************************************/
#ifndef _SYSTEM_NET_DNSENDPOINT_
#define _SYSTEM_NET_DNSENDPOINT_

#include "EndPoint.h"
#include <System/Net/Sockets/Enums.h>
#include <System/String.h>

using namespace System::Net::Sockets;

namespace System
{
	namespace Net
	{
		/**
		 * Represents a network endpoint as a host name or a string representation of an IP address and a port number.
		 */
		class DnsEndPoint : public EndPoint
		{
		private:
			AddressFamily_t addressFamily;
			int port;
			String host;

		public:
			AddressFamily_t getAddressFamily() const;
			const String getHost() const;
			int getPort() const;

			DnsEndPoint(const String& host, const int port);
			DnsEndPoint(const String& host, const int port, const AddressFamily_t addressFamily);

			bool Equals(Object const * const obj) const;
			int GetHashCode() const;
			const String ToString() const;
		};
	}
}

#endif //_SYSTEM_NET_DNSENDPOINT_
