// Copyright (C) XFX Team
// All rights reserved.
// 
// Redistribution and use in source and binary forms, with or without 
// modification, are permitted provided that the following conditions are met:
// 
//* Redistributions of source code must retain the above copyright 
//notice, this list of conditions and the following disclaimer.
//* Redistributions in binary form must reproduce the above copyright 
//notice, this list of conditions and the following disclaimer in the 
//documentation and/or other materials provided with the distribution.
//* Neither the name of the copyright holder nor the names of any 
//contributors may be used to endorse or promote products derived from 
//this software without specific prior written permission.
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

#include <System/Windows/FrameworkElement.h>
#include <System/Windows/Size.h>

#include <System/Type.h>

namespace System
{
	namespace Windows
	{
		const DependencyProperty<int> FrameworkElement::HeightProperty = DependencyProperty<int>::Register("Height", FrameworkElement::GetType());

		const DependencyProperty<Thickness> FrameworkElement::MarginProperty = DependencyProperty<Thickness>::Register("Margin", FrameworkElement::GetType());

		const DependencyProperty<VerticalAlignment_t> FrameworkElement::VerticalAlignmentProperty = DependencyProperty<VerticalAlignment_t>::Register("VerticalAlignment", FrameworkElement::GetType());

		const DependencyProperty<int> FrameworkElement::WidthProperty = DependencyProperty<int>::Register("Width", FrameworkElement::GetType());

		const Type FrameworkElementTypeInfo("FrameworkElement", "System::Windows::FrameworkElement", TypeCode::Object);

		Thickness FrameworkElement::getMargin() const
		{
			return GetValue(MarginProperty);
		}

		void FrameworkElement::setMargin(const Thickness value)
		{
			SetValue(MarginProperty, value);
		}

		int FrameworkElement::getWidth() const
		{
			return GetValue(WidthProperty);
		}

		void FrameworkElement::setWidth(const int value)
		{
			SetValue(WidthProperty, value);
		}

		FrameworkElement::FrameworkElement()
			: HorizontalAlignment(HorizontalAlignment::Stretch),
			  VerticalAlignment(VerticalAlignment::Stretch)
		{
			SetValue(HeightProperty, Int32::MinValue);
			SetValue(MarginProperty, Thickness(0));
			SetValue(WidthProperty, Int32::MinValue);
		}

		FrameworkElement::~FrameworkElement()
		{
			delete Parent;
		}

		Size FrameworkElement::ArrangeOverride(const Size finalSize)
		{
		}

		const Type& FrameworkElement::GetType()
		{
			return FrameworkElementTypeInfo;
		}

		Size FrameworkElement::MeasureOverride(const Size finalSize)
		{
		}
	}
}
