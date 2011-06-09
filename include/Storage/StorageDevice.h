/********************************************************
 *	StorageDevice.h										*
 *														*
 *	XFX StorageDevice definition file					*
 *	Copyright © XFX Team. All Rights Reserved			*
 ********************************************************/
#ifndef _XFX_STORAGE_STORAGEDEVICE_
#define _XFX_STORAGE_STORAGEDEVICE_

#include <System/Types.h>
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
		
		/// <summary>
		/// Represents a storage device for user data, such as a memory unit or hard drive.
		/// </summary>
		class StorageDevice : virtual Object
		{
			friend class XFX::GamerServices::Guide;

		private:
			PlayerIndex_t _playerIndex;
			uint _deviceIndex;

			StorageDevice(uint deviceIndex, PlayerIndex_t playerIndex);

		public:
			long long FreeSpace();
			bool IsConnected();
			long long TotalSpace();
			
			StorageContainer OpenContainer(char* titleName);
		};
	}
}

#endif //_XFX_STORAGE_STORAGEDEVICE_
