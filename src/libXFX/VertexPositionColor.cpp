// Copyright (C) XFX Team
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

#include <Graphics/VertexPositionColor.h>
#include <System/String.h>

namespace XFX
{
	namespace Graphics
	{
		const VertexElement vertexArray[] =
		{
			VertexElement(0, VertexElementFormat::Vector3, VertexElementUsage::Position, 0),
			VertexElement(12, VertexElementFormat::Color, VertexElementUsage::Color, 0)
		};

		VertexDeclaration VertexPositionColor::getVertexDeclaration() const
		{
			return VertexDeclaration(vertexArray, 2);
		}

		VertexPositionColor::VertexPositionColor()
			: Position(Vector3::Zero), Color(Color::Black)
		{
		}

		VertexPositionColor::VertexPositionColor(const Vector3 position, const XFX::Graphics::Color color)
			: Position(position), Color(color)
		{
		}

		bool VertexPositionColor::Equals(Object const * const obj) const
		{
			return is(this, obj) ? (*this == *(VertexPositionColor*)obj) : false;
		}

		int VertexPositionColor::GetHashCode() const
		{
			return Position.GetHashCode() ^ this->Color.GetHashCode();
		}

		const char* VertexPositionColor::ToString() const
		{
			return String::Format("{Position:%s Color:%s}", Position.ToString(), Color.ToString());
		}

		bool VertexPositionColor::operator !=(const VertexPositionColor& other) const
		{
			return (this->Color != other.Color || Position != other.Position);
		}

		bool VertexPositionColor::operator ==(const VertexPositionColor& other) const
		{
			return (this->Color == other.Color && Position == other.Position);
		}
	}
}
