// Copyright (C) XFX Team
// All rights reserved.
// 
// Redistribution and use in source and binary forms, with or without 
// modification, are permitted provided that the following conditions are met:
// 
//* Redistributions of source code must retain the above copyright 
//notice, this list of conditions and the following disclaimer.
//* Redistributions in binary form must reproduce the above copyright 
//notice, this list of conditions and the following disclaimer in the 
//documentation and/or other materials provided with the distribution.
//* Neither the name of the copyright holder nor the names of any 
//contributors may be used to endorse or promote products derived from 
//this software without specific prior written permission.
// 
// THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS" 
// AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE 
// IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE 
// ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT OWNER OR CONTRIBUTORS BE 
// LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR 
// CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF 
// SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS 
// INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN 
// CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) 
// ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE 
// POSSIBILITY OF SUCH DAMAGE.

#include <System/Net/DnsEndPoint.h>
#include <sassert.h>

namespace System
{
	namespace Net
	{
		AddressFamily_t DnsEndPoint::getAddressFamily() const
		{
			return addressFamily;
		}

		const String DnsEndPoint::getHost() const
		{
			return host;
		}

		int DnsEndPoint::getPort() const
		{
			return port;
		}

		DnsEndPoint::DnsEndPoint(const String& host, const int port)
			: addressFamily(AddressFamily::Unspecified), host(host), port(port)
		{
			sassert(host != String::Empty, "");
			sassert(port >= 0 && port <= 65535, "");
		}

		DnsEndPoint::DnsEndPoint(const String& host, const int port, AddressFamily_t addressFamily)
			: addressFamily(addressFamily), host(host), port(port)
		{
			sassert(host != String::Empty, "");
			sassert(port >= 0 && port <= 65535, "");
			sassert(addressFamily != AddressFamily::Unknown, "");
		}

		bool DnsEndPoint::Equals(Object const * const obj) const
		{
			if (is(this, obj))
			{
				DnsEndPoint * other = (DnsEndPoint *)obj;

				return host == other->host && port == other->port && addressFamily == other->addressFamily;
			}

			return false;
		}

		int DnsEndPoint::GetHashCode() const
		{
			return host.GetHashCode() + port + (int)addressFamily;
		}

		const String DnsEndPoint::ToString() const
		{
			const char * formatString = "%s/%s:%i";

			switch (addressFamily)
			{
			case AddressFamily::InterNetwork:
				return String::Format(formatString, (const char *)host, port, "InterNetwork");
			case AddressFamily::InterNetworkV6:
				return String::Format(formatString, (const char *)host, port, "InterNetworkV6");
			case AddressFamily::Unknown:
				return String::Format(formatString, (const char *)host, port, "Unknown");
			case AddressFamily::Unspecified:
				return String::Format(formatString, (const char *)host, port, "Unspecified");
			}
		}
	}
}
