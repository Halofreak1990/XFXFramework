/*****************************************************************************
 *	StorageDeviceAsyncResult.h  											 *
 *																			 *
 *	XFX::Storage::StorageDeviceAsyncResult class definition file			 *
 *	Copyright (c) XFX Team. All Rights Reserved 							 *
 *****************************************************************************/
#ifndef _XFX_STORAGE_STORAGEDEVICEASYNCRESULT_
#define _XFX_STORAGE_STORAGEDEVICEASYNCRESULT_

#include <System/Interfaces.h>

using namespace System;

namespace XFX
{
	namespace Storage
	{
		class StorageDeviceAsyncResult : public IAsyncResult
		{
		private:
			Object* _state;

		public:
			StorageDeviceAsyncResult(Object* state);

			Object* AsyncState();
			Threading::WaitHandle* AsyncWaitHandle();
			bool CompletedSynchronously() const;
			bool IsCompleted() const;
		};
	}
}

#endif //_XFX_STORAGE_STORAGEDEVICEASYNCRESULT_
