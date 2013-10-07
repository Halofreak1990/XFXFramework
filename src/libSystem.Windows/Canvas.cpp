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

#include <System/Int32.h>
#include <System/Type.h>
#include <System/Windows/Controls/Canvas.h>
#include <System/Windows/Size.h>

namespace System
{
	namespace Windows
	{
		namespace Controls
		{
			const DependencyProperty<Int32> Canvas::LeftProperty = DependencyProperty<Int32>::Register("Left", Canvas::GetType());
			const DependencyProperty<Int32> Canvas::TopProperty = DependencyProperty<Int32>::Register("Top", Canvas::GetType());
			const DependencyProperty<Int32> Canvas::ZIndexProperty = DependencyProperty<Int32>::Register("ZIndex", Canvas::GetType());

			const Type CanvasTypeInfo("Canvas", "System::Windows::Controls::Canvas", TypeCode::Object);

			Canvas::Canvas()
			{
				// TODO: implement
			}

			Size Canvas::ArrangeOverride(const Size arrangeSize)
			{
				// TODO: implement
			}

			int Canvas::GetLeft(UIElement * const element)
			{
				return element->GetValue(Canvas::LeftProperty);
			}

			int Canvas::GetTop(UIElement * const element)
			{
				return element->GetValue(Canvas::TopProperty);
			}

			int Canvas::GetZIndex(UIElement * const element)
			{
				return element->GetValue(Canvas::ZIndexProperty);
			}

			const Type& Canvas::GetType()
			{
				return CanvasTypeInfo;
			}

			Size Canvas::MeasureOverride(const Size constraint)
			{
				// TODO: implement
			}

			void Canvas::SetLeft(UIElement * const element, const int left)
			{
				element->SetValue(Canvas::LeftProperty, left);
			}

			void Canvas::SetTop(UIElement * const element, const int top)
			{
				element->SetValue(Canvas::TopProperty, top);
			}

			void Canvas::SetZIndex(UIElement * const element, const int zIndex)
			{
				element->SetValue(Canvas::ZIndexProperty, zIndex);
			}

			bool Canvas::operator ==(const Canvas& right) const
			{
				return Object::ReferenceEquals(*this, right);
			}

			bool Canvas::operator !=(const Canvas& right) const
			{
				return !Object::ReferenceEquals(*this, right);
			}
		}
	}
}
