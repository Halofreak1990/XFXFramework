/********************************************************
 *	VertexPositionTexture.h								*
 *														*
 *	XFX VertexPositionTexture definition file			*
 *	Copyright © XFX Team. All Rights Reserved			*
 ********************************************************/
#ifndef _XFX_GRAPHICS_VERTEXPOSITIONTEXTURE_
#define _XFX_GRAPHICS_VERTEXPOSITIONTEXTURE_

#include "VertexDeclaration.h"

namespace XFX
{
	struct Vector2;
	struct Vector3;
	
	namespace Graphics
	{
		// Describes a custom vertex format structure that contains position and one set of texture coordinates.
		struct VertexPositionTexture : Object
		{
		private:
			static const VertexElement vertexArray[];

		public:
			Vector3 Position;
			Vector2 TextureCoordinate;
			VertexDeclaration getVertexDeclaration() const;
			
			VertexPositionTexture();
			VertexPositionTexture(const Vector3 position, const Vector2 textureCoordinate);
			
			bool Equals(Object const * const obj) const;
			int GetHashCode() const;
			int GetType() const;
			const char* ToString() const;
		
			bool operator!=(const VertexPositionTexture& other) const;
			bool operator==(const VertexPositionTexture& other) const;
		};
	}
}

#endif //_XFX_GRAPHICS_VERTEXPOSITIONTEXTURE_
