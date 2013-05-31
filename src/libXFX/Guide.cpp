// Copyright (C) XFX Team
// All rights reserved.
// 
// Redistribution and use in source and binary forms, with or without 
// modification, are permitted provided that the following conditions are met:
// 
//     * Redistributions of source code must retain the above copyright 
//       notice, this list of conditions and the following disclaimer.
//     * Redistributions in binary form must reproduce the above copyright 
//       notice, this list of conditions and the following disclaimer in the 
//       documentation and/or other materials provided with the distribution.
//     * Neither the name of the copyright holder nor the names of any 
//       contributors may be used to endorse or promote products derived from 
//       this software without specific prior written permission.
// 
// THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS" 
// AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE 
// IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE 
// ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT OWNER OR CONTRIBUTORS BE 
// LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR 
// CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF 
// SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS 
// INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN 
// CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) 
// ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE 
// POSSIBILITY OF SUCH DAMAGE.

#include <System/String.h>
#include <GamerServices/Guide.h>
#include <GamerServices/StorageDeviceAsyncResult.h>
#include <System/FrameworkResources.h>
#include <System/TimeSpan.h>

#include <sassert.h>

namespace XFX
{
	namespace GamerServices
	{
		bool Guide::IsVisible()
		{
			return _isVisible;
		}

		IAsyncResult* Guide::BeginShowKeyboardInput(const PlayerIndex_t player, String& title, String& description, String& defaultText, AsyncCallback callback, Object* state)
		{
			if (String::IsNullOrEmpty(title))
				title = String::Empty;

			if (String::IsNullOrEmpty(description))
				description = String::Empty;

			if (String::IsNullOrEmpty(defaultText))
				defaultText = String::Empty;

			// just return null to stop warning until this thing's coded
			return null;
		}

		IAsyncResult* Guide::BeginShowMessageBox(const PlayerIndex_t player, String& title, String& text, IEnumerable<String>* buttons, const int focusButton, const MessageBoxIcon_t icon, AsyncCallback callback, Object* state)
		{
			if (String::IsNullOrEmpty(title))
				title = String::Empty;

			sassert(buttons != NULL, String::Format("buttons: %s", FrameworkResources::ArgumentNull_Generic));

			// just return null to stop warning until this thing's coded
			return null;
		}

		IAsyncResult* Guide::BeginShowStorageDeviceSelector(const int sizeInBytes, const int directoryCount, AsyncCallback callback, Object* state)
		{
			// just return null to stop warning until this thing's coded
			return null;
		}

		IAsyncResult* Guide::BeginShowStorageDeviceSelector(AsyncCallback callback, Object* state)
		{
			// just return null to stop warning until this thing's coded
			return null;
		}

		IAsyncResult* Guide::BeginShowStorageDeviceSelector(const PlayerIndex_t player, const int sizeInBytes, const int directoryCount, AsyncCallback callback, Object* state)
		{
			// just return null to stop warning until this thing's coded
			return null;
		}

		IAsyncResult* Guide::BeginShowStorageDeviceSelector(const PlayerIndex_t player, AsyncCallback callback, Object* state)
		{
			// just return null to stop warning until this thing's coded
			return null;
		}

		const char* Guide::EndShowKeyboardInput(IAsyncResult* result)
		{
			// just return an empty string to stop warning until this thing's coded
			return "";
		}

		int Guide::EndShowMessageBox(IAsyncResult* result)
		{
			// Since C++ doesn't have a nullable type, we return -1, since it represents an invalid value anyways.
			return -1;
		}

		StorageDevice Guide::EndShowStorageDeviceSelector(IAsyncResult* asyncResult)
		{
			StorageDeviceAsyncResult* result = (StorageDeviceAsyncResult*)asyncResult;

			sassert(result, String::Format("asyncResult; %s", FrameworkResources::ArgumentNull_Generic));

			return StorageDevice(0, (PlayerIndex_t)result->playerIndex);
		}
	}
}
