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

using namespace System;

namespace XFX
{
	namespace Graphics
	{
		// Describes a custom vertex format structure that contains position and color information.
		struct VertexPositionColor : virtual Object
		{
			Vector3 Position;
			Color Color_;
			static int SizeInBytes();
			static const VertexElement VertexElements[];

			VertexPositionColor(Vector3 position, Color color);

			bool Equals(const VertexPositionColor obj);
			int GetHashCode();
			char* ToString();

			bool operator!=(const VertexPositionColor other);
			bool operator==(const VertexPositionColor other);
		};
	}
}

#endif //_XFX_GRAPHICS_VERTEXPOSITIONCOLOR_
