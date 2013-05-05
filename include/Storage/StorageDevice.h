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
		class StorageDevice : public Object
		{
		private:
			friend class XFX::GamerServices::Guide;

			PlayerIndex_t _playerIndex;
			unsigned int _deviceIndex;

			StorageDevice(unsigned int deviceIndex, PlayerIndex_t playerIndex);
			virtual ~StorageDevice();

		public:
			long long FreeSpace() const;
			bool IsConnected() const;
			long long TotalSpace() const;
			
			int GetType() const;
			StorageContainer* OpenContainer(const char* titleName);
		};
	}
}

#endif //_XFX_STORAGE_STORAGEDEVICE_
