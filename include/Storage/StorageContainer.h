/*****************************************************************************
 *	StorageContainer.h  													 *
 *																			 *
 *	XFX::Storage::StorageContainer class definition file					 *
 *	Copyright (c) XFX Team. All Rights Reserved 							 *
 *****************************************************************************/
#ifndef _XFX_STORAGE_STORAGECONTAINER_
#define _XFX_STORAGE_STORAGECONTAINER_

#include <System/Event.h>
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

		/**
		 * Represents a logical collection of storage files.
		 */
		class StorageContainer : public IDisposable, public Object
		{
			friend class StorageDevice;

		private:
			bool isDisposed;
			DirectoryInfo containerFolder;
			StorageDevice* device;
			PlayerIndex_t playerIndex;
			String titleName;

			void Dispose(bool disposing);
			virtual ~StorageContainer();

		public:
			EventHandler Disposing;

			bool IsDisposed() const;
			const String Path() const;
			StorageDevice* getStorageDevice() const;
			static const String TitleLocation();
			const String TitleName() const;

			void Delete();
			void Dispose();
		};
	}
}

#endif //_XFX_STORAGE_STORAGECONTAINER_
