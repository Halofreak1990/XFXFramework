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

using namespace System::Collections::Generic;

namespace XFX
{
	namespace Graphics
	{
		/// <summary>
		/// 
		/// </summary>
		class TextureCollection
		{
		private:
			bool disposed;
			List<Texture> textures;
			void Dispose();
			void Dispose(bool disposing);

		public:
			TextureCollection();
			~TextureCollection();

			Texture operator[](int index);
		};
	}
}

#endif //_XFX_GRAPHICS_TEXTURECOLLECTION_
