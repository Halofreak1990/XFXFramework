/********************************************************
 *	ContentManager.h									*
 *														*
 *	XFX ContentManager definition file					*
 *	Copyright © XFX Team. All Rights Reserved			*
 ********************************************************/
#ifndef _XFX_CONTENT_CONTENTMANAGER_
#define _XFX_CONTENT_CONTENTMANAGER_

#include <System/Collections/Generic/List.h>
#include <System/IO/Stream.h>
#include <System/Interfaces.h>
#include <System/String.h>

using namespace System;
using namespace System::Collections::Generic;
using namespace System::IO;

namespace XFX
{
	namespace Content
	{		
		// The ContentManager is the run-time component which loads managed objects from the binary files produced by the design time content pipeline. It also manages the lifespan of the loaded objects, disposing the content manager will also dispose any assets which are themselves System.IDisposable.
		class ContentManager : public IDisposable, virtual Object
		{
		private:
			List<IDisposable*> disposableAssets;
			//Dictionary<const char*, Object*>* loadedAssets;
			bool disposed;
			IServiceProvider* _provider;

		protected:
			virtual void Dispose(bool disposing);
			virtual Stream* OpenStream(char* assetName);
			template <class T>
			T ReadAsset(char* assetName); //! usage: T ReadAsset<T>(assetName); where T is the preferred type, i.e. Texture2D
			
		public:
			char* RootDirectory;

			ContentManager(IServiceProvider* provider);
			ContentManager(IServiceProvider* provider, const char* rootDirectory);
			virtual ~ContentManager();
		
			void Dispose();
			template <class T>
			T Load(const char* assetName); //! usage: T Load<T>(assetName); where T is the preferred type, i.e. Texture2D
			virtual void Unload();
		};
	}
}

#endif //_XFX_CONTENT_CONTENTMANAGER_
