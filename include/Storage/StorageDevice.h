/********************************************************
 *	StorageDevice.h										*
 *														*
 *	XFX StorageDevice definition file					*
 *	Copyright © XFX Team. All Rights Reserved			*
 ********************************************************/
#ifndef _XFX_STORAGE_STORAGEDEVICE_
#define _XFX_STORAGE_STORAGEDEVICE_

#include <System/Types.h>
#include "../Enums.h"

namespace XFX
{
	namespace Storage
	{
		class StorageContainer;
		
		/// <summary>
		/// Represents a storage device for user data, such as a memory unit or hard drive.
		/// </summary>
		class StorageDevice
		{
		private:
			PlayerIndex_t _playerIndex;
			bool _playerSpecified;

			StorageDevice(PlayerIndex_t playerIndex, bool playerSpecified);

		public:
			long long FreeSpace();
			bool IsConnected();
			long long TotalSpace();
			
			StorageContainer OpenContainer(char* titleName);
		}
	}
}

#endif //_XFX_STORAGE_STORAGEDEVICE_
