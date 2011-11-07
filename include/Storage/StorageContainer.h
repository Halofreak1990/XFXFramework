/********************************************************
 *	StorageContainer.h									*
 *														*
 *	XFX StorageContainer definition file				*
 *	Copyright © XFX Team. All Rights Reserved			*
 ********************************************************/
#ifndef _XFX_STORAGE_STORAGECONTAINER_
#define _XFX_STORAGE_STORAGECONTAINER_

#include <System/Delegates.h>
#include <System/Interfaces.h>
#include <System/IO/DirectoryInfo.h>
#include "../Enums.h"

using namespace System;
using namespace System::IO;

namespace XFX
{
	namespace Storage
	{
		class StorageDevice;
	
		// Represents a logical collection of storage files.
		class StorageContainer : public IDisposable, virtual Object
		{
			friend class StorageDevice;

		private:
			bool isDisposed;
			DirectoryInfo containerFolder;
		    StorageDevice* device;
		    PlayerIndex_t playerIndex;
			char* titleName;

			void Dispose(bool disposing);
			virtual ~StorageContainer();

		public:
			EventHandler Disposing;

			bool IsDisposed();
			char* Path();
			StorageDevice* getStorageDevice();
			static char* TitleLocation();
			char* TitleName();
				
			void Delete();
			void Dispose();
		};
	}
}

#endif //_XFX_STORAGE_STORAGECONTAINER_
