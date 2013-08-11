/*****************************************************************************
 *	ModelMeshPart.h 														 *
 *																			 *
 *	XFX::Graphics::ModelMeshPart class definition file  					 *
 *	Copyright (c) XFX Team. All Rights Reserved 							 *
 *****************************************************************************/
#ifndef _XFX_GRAPHICS_MODELMESHPART_
#define _XFX_GRAPHICS_MODELMESHPART_

#include "Effect.h"
#include "IndexBuffer.h"
#include "VertexBuffer.h"

namespace XFX
{
	namespace Graphics
	{
		/**
		 * Represents a batch of geometry information to submit to the graphics device during rendering. Each ModelMeshPart is a subdivision of a ModelMesh object. The ModelMesh class is split into multiple ModelMeshPart objects, typically based on material information.
		 */
		class ModelMeshPart
		{
		public:
			/**
			 * Gets or sets the material effect for this mesh part.
			 */
			XFX::Graphics::Effect* Effect;
			/**
			 * Gets the index buffer for this mesh part.
			 */
			IndexBuffer getIndexBuffer();
			/**
			 * Gets the number of vertices used during a draw call.
			 */
			int getNumVertices();
			/**
			 * Gets the number of primitives to render.
			 */
			int getPrimitiveCount();
			/**
			 * Gets the location in the index array at which to start reading vertices.
			 */
			int getStartIndex();
			/**
			 * Gets or sets an object identifying this model mesh part.
			 */
			Object* Tag;
			/**
			 * Gets the vertex buffer for this mesh part.
			 */
			VertexBuffer getVertexBuffer();
			/**
			 * Gets the offset (in vertices) from the top of vertex buffer.
			 */
			int getVertexOffset();
		};
	}
}

#endif //_XFX_GRAPHICS_MODELMESHPART_
