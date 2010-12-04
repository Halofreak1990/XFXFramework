/********************************************************
 *	StorageDeviceNotConnectedException.h				*
 *														*
 *	XFX StorageDeviceNotConnectedException definition	*
 *	Copyright © XFX Team. All Rights Reserved			*
 ********************************************************/
#ifndef _XFX_STORAGE_STORAGEDEVICENOTCONNECTEDEXCEPTION_
#define _XFX_STORAGE_STORAGEDEVICENOTCONNECTEDEXCEPTION_

#include <System/Exception.h>

namespace XFX
{
	namespace Storage
	{
		/// <summary>
		/// The exception that is thrown when the requested StorageDevice is not connected
		/// </summary>
		class StorageDeviceNotConnectedException : ExternalException
		{
		public:
			StorageDeviceNotConnectedException();
			StorageDeviceNotConnectedException(char* message);
			StorageDeviceNotConnectedException(char* message, Exception innerException);
		};
	}
}

#endif //_XFX_STORAGE_STORAGEDEVICENOTCONNECTEDEXCEPTION_
