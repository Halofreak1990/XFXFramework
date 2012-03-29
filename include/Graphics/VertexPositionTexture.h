/********************************************************
 *	VertexPositionTexture.h								*
 *														*
 *	XFX VertexPositionTexture definition file			*
 *	Copyright © XFX Team. All Rights Reserved			*
 ********************************************************/
#ifndef _XFX_GRAPHICS_VERTEXPOSITIONTEXTURE_
#define _XFX_GRAPHICS_VERTEXPOSITIONTEXTURE_

#include "VertexElement.h"

namespace XFX
{
	struct Vector2;
	struct Vector3;
	
	namespace Graphics
	{
		// Describes a custom vertex format structure that contains position and one set of texture coordinates.
		struct VertexPositionTexture : virtual Object
		{
		public:
			Vector3 Position;
			Vector2 TextureCoordinate;
			static const VertexElement VertexElements[];
			
			static int SizeInBytes();
			
			VertexPositionTexture(Vector3 position, Vector2 textureCoordinate);
			
			bool Equals(const VertexPositionTexture other);
			int GetHashCode();
			char* ToString();
		
			bool operator!=(const VertexPositionTexture other);
			bool operator==(const VertexPositionTexture other);
		};
	}
}

#endif //_XFX_GRAPHICS_VERTEXPOSITIONTEXTURE_
