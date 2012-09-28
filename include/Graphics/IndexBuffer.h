#ifndef _XFX_GRAPHICS_INDEXBUFFER_
#define _XFX_GRAPHICS_INDEXBUFFER_

#include "Enums.h"
#include "GraphicsResource.h"

namespace XFX
{
	namespace Graphics
	{
		class GraphicsDevice;

		// Describes the rendering order of the vertices in a vertex buffer.
		class IndexBuffer : public GraphicsResource
		{
		private:
			BufferUsage_t _usage;
			int _indexCount;
			IndexElementSize_t _elementSize;

		protected:
			void Dispose(bool disposing);

		public:
			IndexBuffer();
			IndexBuffer(GraphicsDevice * const graphicsDevice, IndexElementSize_t indexElementSize, int indexCount, BufferUsage_t usage);

			template <typename T>
			void CopyData(int offsetInBytes, T data[], int startIndex, int elementCount, uint options, bool isSetting);
			template <typename T>
			void GetData(int offsetInBytes, T data[], int startIndex, int elementCount);
			template <typename T>
			void GetData(T data[], int startIndex, int elementCount);
			int GetType() const;
			template <typename T>
			void SetData(int offsetInBytes, T data[], int startIndex, int elementCount);
			template <typename T>
			void SetData(T data[], int startIndex, int elementCount);
		};
	}
}

#endif //_XFX_GRAPHICS_INDEXBUFFER_
