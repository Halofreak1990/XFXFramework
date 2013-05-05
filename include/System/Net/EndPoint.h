#ifndef _SYSTEM_NET_ENDPOINT_
#define _SYSTEM_NET_ENDPOINT_

#include "Sockets/Enums.h"
#include "../Object.h"

using namespace System::Net::Sockets;

namespace System
{
	namespace Net
	{
		class SocketAddress;

		// Identifies a network address. This is an abstract class.
		class EndPoint : public virtual Object
		{
		protected:
			EndPoint();

		public:
			AddressFamily_t getAddressFamily();

			virtual EndPoint* Create(SocketAddress socketAddress);
			virtual SocketAddress Serialize();
		};
	}
}

#endif //_SYSTEM_NET_ENDPOINT_
