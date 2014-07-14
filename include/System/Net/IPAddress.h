/*****************************************************************************
 *	IPAddress.h 															 *
 *																			 *
 *	System::Net::IPAddress class definition file.							 *
 *	Copyright (c) XFX Team. All rights reserved.							 *
 *****************************************************************************/
#ifndef _SYSTEM_NET_IPADDRESS_
#define _SYSTEM_NET_IPADDRESS_

#include <System/Types.h>
#include <System/Object.h>
#include <System/Net/Sockets/Enums.h>

using namespace System::Net::Sockets;

namespace System
{
	namespace Net
	{
		/**
		 * Provides an Internet Protocol (IP) address.
		 */
		class IPAddress : public Object
		{
		private:
			byte* addressBytes;
			AddressFamily_t addressFamily;

		public:
			AddressFamily_t getAddressFamily() const;
			bool IsIPv6LinkLocal() const;
			bool IsIPv6Multicast() const;
			bool IsIPv6SiteLocal() const;
			long long getScopeId() const;
			void setScopeId(long long value);

			static const IPAddress Any;
			static const IPAddress Broadcast;
			static const IPAddress IPv6Any;
			static const IPAddress IPv6Loopback;
			static const IPAddress IPv6None;
			static const IPAddress Loopback;
			static const IPAddress None;

			IPAddress(byte addressBytes[]);
			IPAddress(byte address[], long long scopeid);
			IPAddress(long long newAddress);
			~IPAddress();

			bool Equals(Object const * const obj) const;
			byte* GetAddressBytes() const;
			int GetHashCode() const;
			static int HostToNetworkOrder(int host);
			static long long HostToNetworkOrder(long long host);
			static short HostToNetworkOrder(short host);
			static bool IsLoopback(IPAddress const * const address);
			static int NetworkToHostOrder(int network);
			static long long NetworkToHostOrder(long long network);
			static short NetworkToHostOrder(short network);
			static IPAddress Parse(const String& ipString);
			static bool TryParse(const String& ipString, out IPAddress& address);
			const String ToString() const;
		};
	}
}

#endif //_SYSTEM_NET_IPADDRESS_
