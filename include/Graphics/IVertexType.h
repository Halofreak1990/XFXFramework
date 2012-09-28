#ifndef _XFX_GRAPHICS_IVERTEXTYPE_
#define _XFX_GRAPHICS_IVERTEXTYPE_

#include <Graphics/VertexDeclaration.h>

namespace XFX
{
	namespace Graphics
	{
		// Vertex type interface which is implemented by a custom vertex type structure.
		interface IVertexType
		{
		public:
			// Vertex declaration, which defines per-vertex data.
			VertexDeclaration getVertexDeclaration() const;
		};
	}
}

#endif //_XFX_GRAPHICS_IVERTEXTYPE_
