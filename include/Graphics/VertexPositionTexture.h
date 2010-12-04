/********************************************************
 *	VertexPositionTexture.h								*
 *														*
 *	XFX VertexPositionTexture definition file			*
 *	Copyright © XFX Team. All Rights Reserved			*
 ********************************************************/
#ifndef _VERTEXPOSITIONTEXTURE_
#define _VERTEXPOSITIONTEXTURE_

#include "VertexElement.h"

namespace XFX
{
	class Vector2;
	class Vector3;
	
	namespace Graphics
	{
		/// <summary>
		/// Describes a custom vertex format structure that contains position and one
    	/// set of texture coordinates.
		/// </summary>
		class VertexPositionTexture
		{
			public:
				Vector3 Position;
				Vector2 TextureCoordinate;
				static const VertexElement VertexElements[];
				
				static int SizeInBytes();
				
				VertexPositionTexture(Vector3 &position, Vector2 &textureCoordinate);
				
				int Equals(const VertexPositionTexture &other);
				int GetHashCode();
			
				int operator!=(const VertexPositionTexture &other);
				int operator==(const VertexPositionTexture &other);
		};
	}
}

#endif //_VERTEXPOSITIONTEXTURE_
