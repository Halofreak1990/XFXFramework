/********************************************************
 *	StorageDevice.h										*
 *														*
 *	XFX StorageDevice definition file					*
 *	Copyright © XFX Team. All Rights Reserved			*
 ********************************************************/
#ifndef _XFX_STORAGE_STORAGEDEVICE_
#define _XFX_STORAGE_STORAGEDEVICE_

#include <System/Object.h>
#include "../Enums.h"

using namespace System;

namespace XFX
{
	namespace GamerServices
	{
		class Guide;
	}

	namespace Storage
	{
		class StorageContainer;
		
		// Represents a storage device for user data, such as a memory unit or hard drive.
		class StorageDevice : virtual Object
		{
		private:
			friend class XFX::GamerServices::Guide;

			PlayerIndex_t _playerIndex;
			unsigned int _deviceIndex;

			StorageDevice(unsigned int deviceIndex, PlayerIndex_t playerIndex);
			virtual ~StorageDevice();

		public:
			Int64 FreeSpace();
			bool IsConnected();
			Int64 TotalSpace();
			
			StorageContainer OpenContainer(char* titleName) __attribute__((nonnull (1)));
		};
	}
}

#endif //_XFX_STORAGE_STORAGEDEVICE_
