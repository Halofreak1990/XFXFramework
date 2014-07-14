/*****************************************************************************
 *	NetworkInterface.h  													 *
 *																			 *
 *	System::Net::Sockets::NetworkInterface class definition file.			 *
 *	Copyright (c) XFX Team. All rights reserved.							 *
 *****************************************************************************/
#ifndef _SYSTEM_NET_NETWORKINFORMATION_NETWORKINTERFACE_
#define _SYSTEM_NET_NETWORKINFORMATION_NETWORKINTERFACE_

namespace System
{
	namespace Net
	{
		namespace NetworkInformation
		{
			/**
			 * Provides availability information for a network interface.
			 */
			class NetworkInterface
			{
			protected:
				NetworkInterface();
				virtual ~NetworkInterface();

			public:
				static bool GetIsNetworkAvailable();
			};
		}
	}
}

#endif //_SYSTEM_NET_NETWORKINFORMATION_NETWORKINTERFACE_
