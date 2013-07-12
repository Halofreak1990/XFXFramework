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

#include <System/Windows/Controls/Primitives/ToggleButton.h>
#include <System/Boolean.h>
#include <System/String.h>
#include <System/Type.h>

namespace System
{
	namespace Windows
	{
		namespace Controls
		{
			namespace Primitives
			{
				const Type ToggleButtonTypeInfo("ToggleButton", "System::Windows::Controls::Primitives::ToggleButton", TypeCode::Object);

				ToggleButton::ToggleButton()
				{
				}

				ToggleButton::~ToggleButton()
				{
				}

				const Type& ToggleButton::GetType()
				{
					return ToggleButtonTypeInfo;
				}

				void ToggleButton::OnClick()
				{
					this->OnToggle();
					ButtonBase::OnClick();
				}

				void ToggleButton::OnContentChanged(Object *oldContent, Object *newContent)
				{
					ButtonBase::OnContentChanged(oldContent, newContent);
					ButtonBase::UpdateVisualState(true);
				}

				void ToggleButton::OnToggle()
				{
					Nullable<bool> isChecked = this->IsChecked;
					if (isChecked == true)
					{
						this->IsChecked = this->IsThreeState ? Nullable<bool>::Null : ((Nullable<bool>) false);
					}
					else
					{
						this->IsChecked = Nullable<bool>(isChecked.HasValue());
					}
				}

				const String ToggleButton::ToString() const
				{
					return String::Format("{ToggleButton Content:%s IsChecked:%s}", (Content) ? (const char *)Content->ToString() : "", (IsChecked != null) ? (const char *)Boolean::ToString(IsChecked.getValue()) : "null");
				}

				bool ToggleButton::operator ==(const ToggleButton& right) const
				{
					return Object::ReferenceEquals(*this, right);
				}

				bool ToggleButton::operator !=(const ToggleButton& right) const
				{
					return !Object::ReferenceEquals(*this, right);
				}
			}
		}
	}
}
