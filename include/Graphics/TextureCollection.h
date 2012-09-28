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
		class Texture2D;

		// Represents a collection of Texture objects.
		class TextureCollection : public Object
		{
		private:
			friend class Texture2D;

			bool disposed;
			List<Texture*> textures;
			void Dispose(bool disposing);

		public:
			TextureCollection();
			virtual ~TextureCollection();

			void Dispose();
			int GetType() const;

			Texture* operator[](const int index);
		};
	}
}

#endif //_XFX_GRAPHICS_TEXTURECOLLECTION_
