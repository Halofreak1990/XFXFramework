/*****************************************************************************
 *	VertexPositionColor.h													 *
 *																			 *
 *	XFX::Graphics::VertexPositionColor definition file  					 *
 *	Copyright (c) XFX Team. All Rights Reserved 							 *
 *****************************************************************************/
#ifndef _XFX_GRAPHICS_VERTEXPOSITIONCOLOR_
#define _XFX_GRAPHICS_VERTEXPOSITIONCOLOR_

#include "Color.h"
#include <Vector3.h>
#include "IVertexType.h"
#include "VertexElement.h"

using namespace System;

namespace XFX
{
	namespace Graphics
	{
		// Describes a custom vertex format structure that contains position and color information.
		struct VertexPositionColor : IVertexType, Object
		{
		private:
			static const VertexElement vertexArray[];

		public:
			Vector3 Position;
			XFX::Graphics::Color Color;

			VertexDeclaration getVertexDeclaration() const;

			VertexPositionColor();
			VertexPositionColor(const Vector3 position, const XFX::Graphics::Color color);

			bool Equals(Object const * const obj) const;
			int GetHashCode() const;
			static int GetType();
			const String& ToString() const;

			bool operator!=(const VertexPositionColor& other) const;
			bool operator==(const VertexPositionColor& other) const;
		};
	}
}

#endif //_XFX_GRAPHICS_VERTEXPOSITIONCOLOR_
