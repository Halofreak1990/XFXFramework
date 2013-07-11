/*****************************************************************************
 *	VertexPositionNormalTexture.h											 *
 *																			 *
 *	XFX::Graphics::VertexPositionNormalTexture definition file  			 *
 *	Copyright (c) XFX Team. All Rights Reserved 							 *
 *****************************************************************************/
#ifndef _XFX_GRAPHICS_VERTEXPOSITIONNORMALTEXTURE_
#define _XFX_GRAPHICS_VERTEXPOSITIONNORMALTEXTURE_

#include "IVertexType.h"
#include <Vector2.h>
#include <Vector3.h>
#include "VertexElement.h"

using namespace System;

namespace XFX
{
	namespace Graphics
	{
		// Describes a custom vertex format structure that contains position, normal data, and one set of texture coordinates.
		struct VertexPositionNormalTexture : IVertexType, Object
		{
		private:
			static const VertexElement vertexArray[];

		public:
			Vector3 Position;
			Vector3 Normal;
			Vector2 TextureCoordinate;
			VertexDeclaration getVertexDeclaration() const;
			
			VertexPositionNormalTexture();
			VertexPositionNormalTexture(const Vector3 position, const Vector3 normal, const Vector2 textureCoordinate);
			
			bool Equals(Object const * const obj) const;
			int GetHashCode() const;
			static int GetType();
			const String ToString() const;
		
			bool operator!=(const VertexPositionNormalTexture& other) const;
			bool operator==(const VertexPositionNormalTexture& other) const;
		};
	}
}

#endif //_XFX_GRAPHICS_VERTEXPOSITIONNORMALTEXTURE_
