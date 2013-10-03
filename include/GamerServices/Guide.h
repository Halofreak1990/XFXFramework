/*****************************************************************************
 *	Guide.h 																 *
 *																			 *
 *	XFX::GamerServices::Guide class definition file 						 *
 *	Copyright (c) XFX Team. All Rights Reserved 							 *
 *****************************************************************************/
#ifndef _XFX_GAMERSERVICES_GUIDE_
#define _XFX_GAMERSERVICES_GUIDE_

#include <System/Collections/Generic/Interfaces.h>
#include <System/Delegates.h>
#include <System/Interfaces.h>
#include <System/Nullable.h>
#include <System/TimeSpan.h>
#include <System/Types.h>
#include <Storage/StorageDevice.h>
#include "Enums.h"

using namespace System;
using namespace System::Collections::Generic;
using namespace XFX::Storage;

namespace XFX
{
	namespace GamerServices
	{
		/**
		 * Provides access to the Guide user interface.
		 */
		class Guide
		{
		private:
			static bool _isVisible;

			// Private constructor to prevent instantiation
			Guide();

		public:
			static bool IsScreenSaverEnabled;
			static bool IsVisible();
			static NotificationPosition_t NotificationPosition;

			static IAsyncResult* BeginShowKeyboardInput(const PlayerIndex_t player, String& title, String& description, String& defaultText, AsyncCallback callback, Object* state);
			static IAsyncResult* BeginShowMessageBox(const PlayerIndex_t player, String& title, String& text, IEnumerable<String>* buttons, const int focusButton, const MessageBoxIcon_t icon, AsyncCallback callback, Object* state);
			static IAsyncResult* BeginShowStorageDeviceSelector(int sizeInBytes, int directoryCount, AsyncCallback callback, Object* state);
			static IAsyncResult* BeginShowStorageDeviceSelector(AsyncCallback callback, Object* state);
			static IAsyncResult* BeginShowStorageDeviceSelector(const PlayerIndex_t player, const int sizeInBytes, const int directoryCount, AsyncCallback callback, Object* state);
			static IAsyncResult* BeginShowStorageDeviceSelector(const PlayerIndex_t player, AsyncCallback callback, Object* state);
			static void DelayNotifications(const TimeSpan timespan);
			static String EndShowKeyboardInput(IAsyncResult* result);
			static Nullable<int> EndShowMessageBox(IAsyncResult* result);
			static StorageDevice EndShowStorageDeviceSelector(IAsyncResult* result);
		};
	}
}

#endif //_XFX_GAMERSERVICES_GUIDE_
