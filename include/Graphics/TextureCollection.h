/********************************************************
 *	TextureCollection.h									*
 *														*
 *	XFX TextureCollection definition file				*
 *	Copyright © XFX Team. All Rights Reserved			*
 ********************************************************/
#ifndef _XFX_GRAPHICS_TEXTURECOLLECTION_
#define _XFX_GRAPHICS_TEXTURECOLLECTION_

#include <System/Collections/Generic/List.h>
#include "Texture.h"

using namespace System;
using namespace System::Collections::Generic;

namespace XFX
{
	namespace Graphics
	{
		// Represents a collection of Texture objects.
		class TextureCollection : virtual Object
		{
		private:
			bool disposed;
			List<Texture*> textures;
			void Dispose(bool disposing);

		public:
			TextureCollection();
			virtual ~TextureCollection();

			void Dispose();

			Texture* operator[](int index);
		};
	}
}

#endif //_XFX_GRAPHICS_TEXTURECOLLECTION_
