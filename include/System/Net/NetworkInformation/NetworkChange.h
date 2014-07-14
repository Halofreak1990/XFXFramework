/*****************************************************************************
 *	NetworkInterface.h  													 *
 *																			 *
 *	System::Net::Sockets::NetworkInterface class definition file.			 *
 *	Copyright (c) XFX Team. All rights reserved.							 *
 *****************************************************************************/
#ifndef _SYSTEM_NET_NETWORKINFORMATION_NETWORKCHANGE_
#define _SYSTEM_NET_NETWORKINFORMATION_NETWORKCHANGE_

#include <System/Event.h>

namespace System
{
	namespace Net
	{
		namespace NetworkInformation
		{
			/**
			 * Allows applications to receive notification when the Internet Protocol (IP) address of a network interface, also called a network card or adapter, changes.
			 */
			class NetworkChange
			{
			protected:
				NetworkChange();
				virtual ~NetworkChange();

			public:
				NetworkAddressChangedEventHandler NetworkAddressChanged;
			};

			/**
			 * References one or more methods to be called when the address of a network interface changes.
			 */
			typedef Event<Object * const, EventArgs * const> NetworkAddressChangedEventHandler;
		}
	}
}

#endif //_SYSTEM_NET_NETWORKINFORMATION_NETWORKCHANGE_
