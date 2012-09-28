#ifndef _SYSTEM_NET_SOCKETADDRESS_
#define _SYSTEM_NET_SOCKETADDRESS_

#include "../Object.h"
#include "../Types.h"
#include "Sockets/Enums.h"

using namespace System::Net::Sockets;

namespace System
{
	namespace Net
	{
		// Stores serialized information from System::Net::EndPoint derived classes.
		class SocketAddress : public virtual Object
		{
		private:
			AddressFamily_t addressFamily;
			int bufferSize;

		public:
			AddressFamily_t getFamily();
			int getSize();
			byte operator[](int offset);

			SocketAddress(AddressFamily_t family);
			SocketAddress(AddressFamily_t family, int size);

			char* ToString();
		};
	}
}

#endif //_SYSTEM_NET_SOCKETADDRESS_
