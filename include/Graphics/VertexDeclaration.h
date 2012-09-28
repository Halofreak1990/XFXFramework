#ifndef _XFX_GRAPHICS_VERTEXDECLARATION_
#define _XFX_GRAPHICS_VERTEXDECLARATION_

#include "GraphicsResource.h"
#include "VertexElement.h"

namespace XFX
{
	namespace Graphics
	{
		// A vertex declaration, which defines per-vertex data.
		class VertexDeclaration : public GraphicsResource
		{
		private:
			int vertexStride;
			int elementCount;
			VertexElement* vertexElements;

		protected:
			void Dispose(bool disposing);

		public:
			int getVertexStride() const;

			VertexDeclaration(int vertexStride, VertexElement const * const elements, const int elementCount);
			VertexDeclaration(VertexElement const * const elements, const int elementCount);
			VertexDeclaration(const VertexDeclaration &obj);
			~VertexDeclaration();

			int GetType() const;
			VertexElement* GetVertexElements() const;
		};
	}
}

#endif //_XFX_GRAPHICS_VERTEXDECLARATION_
