/********************************************************
 *	VertexElement.h										*
 *														*
 *	XFX VertexElement definition file					*
 *	Copyright (c) XFX Team. All Rights Reserved			*
 ********************************************************/
#ifndef _XFX_GRAPHICS_VERTEXELEMENT_
#define _XFX_GRAPHICS_VERTEXELEMENT_

#include <System/Object.h>
#include <System/Types.h>
#include <Graphics/Enums.h>

using namespace System;

namespace XFX
{
	namespace Graphics
	{
		// Defines input vertex data to the pipeline.
		struct VertexElement : Object
		{
			int Offset;
			int UsageIndex;
			VertexElementFormat_t VertexElementFormat;
			VertexElementUsage_t VertexElementUsage;
		
			VertexElement(const int offset, const VertexElementFormat_t elementFormat, const VertexElementUsage_t elementUsage, const int usageIndex);
			VertexElement(const VertexElement &obj);
		
			bool Equals(Object const * const obj) const;
			int GetHashCode() const;
			static int GetType();
			const String ToString() const;
		
			bool operator!=(const VertexElement& other) const;
			bool operator==(const VertexElement& other) const;
		};
	}
}

#endif //_XFX_GRAPHICS_VERTEXELEMENT_
