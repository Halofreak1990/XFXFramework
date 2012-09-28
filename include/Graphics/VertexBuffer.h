#ifndef _XFX_GRAPHICS_VERTEXBUFFER_
#define _XFX_GRAPHICS_VERTEXBUFFER_

#include "GraphicsResource.h"
#include "VertexDeclaration.h"

namespace XFX
{
	namespace Graphics
	{
		// Represents a list of 3D vertices to be streamed to the graphics device.
		class VertexBuffer : public GraphicsResource
		{
		public:
			VertexBuffer();
			VertexBuffer(GraphicsDevice * const graphicsDevice, VertexDeclaration vertexDeclaration, int vertexCount, BufferUsage_t usage);

			template <typename T>
			void GetData(int offsetInBytes, T data[], int startIndex, int elementCount, int vertexStride);
			template <typename T>
			void GetData(T data[], int startIndex, int elementCount);
			int GetType() const;
			template <typename T>
			void SetData(int offsetInBytes, T data[], int startIndex, int elementCount, int vertexStride);
			template <typename T>
			void SetData(T data[], int startIndex, int elementCount);
		};
	}
}

#endif //_XFX_GRAPHICS_VERTEXBUFFER_
