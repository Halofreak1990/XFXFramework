// Copyright (C) 2010-2012, XFX Team
// All rights reserved.
// 
// Redistribution and use in source and binary forms, with or without 
// modification, are permitted provided that the following conditions are met:
// 
//     * Redistributions of source code must retain the above copyright 
//       notice, this list of conditions and the following disclaimer.
//     * Redistributions in binary form must reproduce the above copyright 
//       notice, this list of conditions and the following disclaimer in the 
//       documentation and/or other materials provided with the distribution.
//     * Neither the name of the copyright holder nor the names of any 
//       contributors may be used to endorse or promote products derived from 
//       this software without specific prior written permission.
// 
// THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS" 
// AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE 
// IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE 
// ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT OWNER OR CONTRIBUTORS BE 
// LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR 
// CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF 
// SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS 
// INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN 
// CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) 
// ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE 
// POSSIBILITY OF SUCH DAMAGE.

#include <Graphics/VertexDeclaration.h>

namespace XFX
{
	namespace Graphics
	{
		int VertexDeclaration::getVertexStride() const
		{
			return vertexStride;
		}

		VertexDeclaration::VertexDeclaration(int vertexStride, VertexElement const * const elements, const int elementCount)
			: vertexStride(vertexStride), elementCount(elementCount) 
		{
			vertexElements = (VertexElement*)calloc(elementCount, sizeof(VertexElement));

			memcpy(vertexElements, elements, elementCount * sizeof(VertexElement));
		}

		VertexDeclaration::VertexDeclaration(VertexElement const * const elements, const int elementCount)
			: vertexStride(0), elementCount(elementCount)
		{
			vertexElements = (VertexElement*)calloc(elementCount, sizeof(VertexElement));

			memcpy(vertexElements, elements, elementCount * sizeof(VertexElement));
		}

		VertexDeclaration::VertexDeclaration(const VertexDeclaration &obj)
			: vertexStride(obj.vertexStride), elementCount(obj.elementCount)
		{
			// allocate memory for the VertexElement array
			vertexElements = (VertexElement*)calloc(elementCount, sizeof(VertexElement));

			// copy over the VertexElement data
			memcpy(vertexElements, obj.vertexElements, elementCount * sizeof(VertexElement);
		}

		VertexDeclaration::~VertexDeclaration()
		{
			if (!IsDisposed)
			{
				free(vertexElements);
			}
		}

		void VertexDeclaration::Dispose(bool disposing)
		{
			if (!IsDisposed)
			{
				free(vertexElements);
			}
		}

		int VertexDeclaration::GetType() const
		{
			// TODO: implement
		}

		VertexElement* VertexDeclaration::GetVertexElements() const
		{
			return vertexElements;
		}
	}
}
