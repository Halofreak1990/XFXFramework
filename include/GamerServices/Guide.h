#ifndef _GUIDE_H_
#define _GUIDE_H_

#include <System.h>
/********************************************************
 *	Guide.h										*
 *														*
 *	XFX Guide definition file						*
 *	Copyright © XFX Team. All Rights Reserved			*
 ********************************************************/
#include <Storage/StorageDevice.h>

using namespace System;
using namespace XFX::Storage;

namespace XFX
{
	namespace GamerServices
	{
		/// <summary>
		/// Provides access to the Guide user interface.
		/// </summary>
		class Guide
		{
		private:
			static int _isVisible = false;

		public:
			static int IsScreenSaverEnabled();
			static int IsVisible();
			static NotificationPosition notificationPosition;

			static IAsyncResult BeginShowKeyboardInput(PlayerIndex_t player, String &title, String &description, String &defaultText, AsyncCallback &callback, object state);
			static IAsyncResult BeginShowStorageDeviceSelector(int sizeInBytes, int directoryCount, AsyncCallback callback, object state);
			static IAsyncResult BeginShowStorageDeviceSelector(AsyncCallback &callback, object state);
			static IAsyncResult BeginShowStorageDeviceSelector(PlayerIndex_t player, int sizeInBytes, int directoryCount, AsyncCallback callback, object state);
			static IAsyncResult BeginShowStorageDeviceSelector(PlayerIndex_t player, AsyncCallback callback, object state);
			static String EndShowKeyboardInput(IAsyncResult result);
			static StorageDevice EndShowStorageDeviceSelector(IAsyncResult result)
		};
	}
}

#endif //_GUIDE_H_
