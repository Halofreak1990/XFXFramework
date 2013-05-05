#include <System/Net/SocketAddress.h>

namespace System
{
	namespace Net
	{
		AddressFamily_t SocketAddress::getFamily()
		{
			return addressFamily;
		}

		int SocketAddress::getSize()
		{
			return bufferSize;
		}

		SocketAddress::SocketAddress(AddressFamily_t family)
		{
			addressFamily = family;

		}

		SocketAddress::SocketAddress(AddressFamily_t family, int size)
		{
			addressFamily = family;
			bufferSize = size;
		}
	}
}
