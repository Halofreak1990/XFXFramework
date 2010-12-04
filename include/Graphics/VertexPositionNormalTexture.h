/********************************************************
 *	VertexPositionNormalTexture.h						*
 *														*
 *	XFX VertexPositionNormalTexture definition file		*
 *	Copyright © XFX Team. All Rights Reserved			*
 ********************************************************/
#ifndef _VERTEXPOSITIONNORMALTEXTURE_
#define _VERTEXPOSITIONNORMALTEXTURE_

#include "VertexElement.h"

#include <Vector2.h>
#include <Vector3.h>

namespace XFX
{
	namespace Graphics
	{
		/// <summary>
		/// Describes a custom vertex format structure that contains position, normal data,
    	/// and one set of texture coordinates.
		/// </summary>
		class VertexPositionNormalTexture
		{
			public:
				Vector3 Normal;
				Vector3 Position;
				Vector2 TextureCoordinate;
				static const VertexElement VertexElements[];
				
				static int SizeInBytes();
				
				VertexPositionNormalTexture(Vector3 &position, Vector3 &normal, Vector2 &textureCoordinate);
				
				int Equals(const VertexPositionNormalTexture &other);
				int GetHashCode();
			
				int operator!=(const VertexPositionNormalTexture &other);
				int operator==(const VertexPositionNormalTexture &other);
		};
	}
}

#endif //_VERTEXPOSITIONNORMALTEXTURE_
