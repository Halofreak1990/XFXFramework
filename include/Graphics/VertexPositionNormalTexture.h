/********************************************************
 *	VertexPositionNormalTexture.h						*
 *														*
 *	XFX VertexPositionNormalTexture definition file		*
 *	Copyright © XFX Team. All Rights Reserved			*
 ********************************************************/
#ifndef _XFX_GRAPHICS_VERTEXPOSITIONNORMALTEXTURE_
#define _XFX_GRAPHICS_VERTEXPOSITIONNORMALTEXTURE_

#include "VertexElement.h"

using namespace System;

namespace XFX
{
	struct Vector2;
	struct Vector3;

	namespace Graphics
	{
		// Describes a custom vertex format structure that contains position, normal data, and one set of texture coordinates.
		struct VertexPositionNormalTexture : virtual Object
		{
		public:
			Vector3 Normal;
			Vector3 Position;
			Vector2 TextureCoordinate;
			static const VertexElement VertexElements[];
			
			static int SizeInBytes();
			
			VertexPositionNormalTexture(const Vector3 position, const Vector3 normal, const Vector2 textureCoordinate);
			
			bool Equals(const VertexPositionNormalTexture other) const;
			int GetHashCode() const;
			const char* ToString() const;
		
			bool operator!=(const VertexPositionNormalTexture other) const;
			bool operator==(const VertexPositionNormalTexture other) const;
		};
	}
}

#endif //_XFX_GRAPHICS_VERTEXPOSITIONNORMALTEXTURE_
