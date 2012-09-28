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

#include <Graphics/Viewport.h>
#include <System/String.h>
#include <Matrix.h>
#include <Rectangle.h>
#include <Vector3.h>

namespace XFX
{
	namespace Graphics
	{
		float Viewport::getAspectRatio() const
		{
			if ((Height != 0) && (Width != 0))
            {
                return (((float)Width) / ((float)Height));
            }
            return 0.0f;
		}

		Rectangle Viewport::getBounds() const
		{
			return Rectangle(X, Y, Width, Height);
		}

		void Viewport::setBounds(Rectangle value)
		{
			X = value.X;
			Y = value.Y;
			Width = value.Width;
			Height = value.Height;
		}

		Rectangle Viewport::getTitleSafeArea() const
		{
			// TODO calculate this
			return Rectangle(32, 32, 576, 416);
		}

		bool Viewport::WithinEpsilon(float a, float b)
		{
			float num = a - b;
			return ((-1.401298E-45f <= num) && (num <= 1.401298E-45f));
		}

		Viewport::Viewport()
			: Height(0), MaxDepth(1.0f), MinDepth(0.0f), Width(0), X(0), Y(0)
		{
		}

		Viewport::Viewport(const int x, const int y, const int width, const int height)
			: Height(height), Width(width), X(x), Y(y)
		{
		}

		Viewport::Viewport(const Rectangle bounds)
			: Height(bounds.Height), Width(bounds.Width), X(bounds.X), Y(bounds.Y)
		{
		}

		bool Viewport::Equals(const Object* obj) const
		{
			return is(this, obj) ? this->Equals(*(Viewport*)obj) : false;
		}

		bool Viewport::Equals(const Viewport obj) const
		{
			return (*this == obj);
		}

		int Viewport::GetHashCode() const
		{
			return ((int)getAspectRatio() + Height + MaxDepth + MinDepth + Width + X + Y);
		}

		int Viewport::GetType() const
		{
		}

		Vector3 Viewport::Project(const Vector3 source, const Matrix projection, const Matrix view, const Matrix world) const
		{
			Matrix matrix = Matrix::Multiply(Matrix::Multiply(world, view), projection);
			Vector3 vector = Vector3::Transform(source, matrix);
			float a = (((source.X * matrix.M14) + (source.Y * matrix.M24)) + (source.Z * matrix.M34)) + matrix.M44;
			if (!WithinEpsilon(a, 1))
			{
				vector = (Vector3) (vector / a);
			}
			vector.X = (((vector.X + 1) * 0.5f) * Width) + X;
			vector.Y = (((-vector.Y + 1) * 0.5f) * Height) + Y;
			vector.Z = (vector.Z * (MaxDepth - MinDepth)) + MinDepth;
			return vector;
		}

		Vector3 Viewport::Unproject(const Vector3 source, const Matrix projection, const Matrix view, const Matrix world) const
		{
			Vector3 position = Vector3();
			Matrix matrix = Matrix::Invert(Matrix::Multiply(Matrix::Multiply(world, view), projection));
			position.X = (((source.X - X) / ((float)Width)) * 2) - 1;
			position.Y = -((((source.Y - Y) / ((float)Height)) * 2) - 1);
			position.Z = (source.Z - MinDepth) / (MaxDepth - MinDepth);
			position = Vector3::Transform(position, matrix);
			float a = (((source.X * matrix.M14) + (source.Y * matrix.M24)) + (source.Z * matrix.M34)) + matrix.M44;
			if (!WithinEpsilon(a, 1))
			{
				position = (position / a);
			}
			return position;
		}

		const char* Viewport::ToString() const
		{
			return String::Format("{X:%i Y:%i Width:%i Height:%i MinDepth:%f MaxDepth:%f}", X, Y, Width, Height, MinDepth, MaxDepth);
		}

		bool Viewport::operator !=(const Viewport& right) const
		{
			return ((Height != right.Height) || (MaxDepth != right.MaxDepth) ||
				(MinDepth != right.MinDepth) || (Width != right.Width) ||
				(X != right.X) || (Y != right.Y));
		}

		bool Viewport::operator ==(const Viewport& right) const
		{
			return ((Height == right.Height) && (MaxDepth == right.MaxDepth) &&
				(MinDepth == right.MinDepth) && (Width == right.Width) && 
				(X == right.X) && (Y == right.Y));
		}
	}
}
