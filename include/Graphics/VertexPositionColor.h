/********************************************************
 *	VertexPositionColor.h								*
 *														*
 *	XFX VertexPositionColor definition file				*
 *	Copyright © XFX Team. All Rights Reserved			*
 ********************************************************/
#ifndef _XFX_GRAPHICS_VERTEXPOSITIONCOLOR_
#define _XFX_GRAPHICS_VERTEXPOSITIONCOLOR_

#include "Color.h"
#include <Vector3.h>
#include "VertexElement.h"

namespace XFX
{
	namespace Graphics
	{
		/// <summary>
		/// Describes a custom vertex format structure that contains position and color information.
		/// </summary>
		struct VertexPositionColor
		{
			Vector3 Position;
			Color Color_;
			static int SizeInBytes();
			static const VertexElement VertexElements[];

			VertexPositionColor(Vector3 position, Color color);

			bool Equals(const VertexPositionColor obj);
			int GetHashCode();

			bool operator!=(const VertexPositionColor other);
			bool operator==(const VertexPositionColor other);
		};
	}
}

#endif //_XFX_GRAPHICS_VERTEXPOSITIONCOLOR_
