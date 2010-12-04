/********************************************************
 *	VertexElement.h										*
 *														*
 *	XFX VertexElement definition file					*
 *	Copyright © XFX Team. All Rights Reserved			*
 ********************************************************/
#ifndef _VERTEXELEMENT_
#define _VERTEXELEMENT_

#include <System.h>
#include <Graphics/Enums.h>

namespace XFX
{
	namespace Graphics
	{
		/// <summary>
		/// Defines input vertex data to the pipeline.
		/// </summary>
		class VertexElement
		{
			public:
				short Offset;
				short Stream;
				BYTE UsageIndex;
				VertexElementFormat_t VertexElementFormat_;
				VertexElementMethod_t VertexElementMethod_;
				VertexElementUsage_t VertexElementUsage_;
			
				VertexElement(short stream, short offset, VertexElementFormat_t elementFormat, VertexElementMethod_t elementMethod, VertexElementUsage_t elementUsage, BYTE usageIndex);
			
				int Equals(const VertexElement &other);
				int GetHashCode();
			
				int operator!=(const VertexElement &other);
				int operator==(const VertexElement &other);
		};
	}
}

#endif //_VERTEXELEMENT_
