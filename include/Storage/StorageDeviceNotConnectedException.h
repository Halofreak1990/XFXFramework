/********************************************************
 *	StorageDeviceNotConnectedException.h				*
 *														*
 *	XFX StorageDeviceNotConnectedException definition	*
 *	Copyright (c) XFX Team. All Rights Reserved			*
 ********************************************************/
#ifndef _XFX_STORAGE_STORAGEDEVICENOTCONNECTEDEXCEPTION_
#define _XFX_STORAGE_STORAGEDEVICENOTCONNECTEDEXCEPTION_

#include <System/Runtime/InteropServices/ExternalException.h>

using namespace System::Runtime::InteropServices;

namespace XFX
{
	namespace Storage
	{
		/**
		 * The exception that is thrown when the requested StorageDevice is not connected
		 */
		class StorageDeviceNotConnectedException : public ExternalException
		{
		public:
			StorageDeviceNotConnectedException();
			StorageDeviceNotConnectedException(const String& message);
			StorageDeviceNotConnectedException(const String& message, Exception * const innerException);
		};
	}
}

#endif //_XFX_STORAGE_STORAGEDEVICENOTCONNECTEDEXCEPTION_
