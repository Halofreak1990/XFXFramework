#include <System/Windows/Controls/Primitives/ToggleButton.h>
#include <System/Boolean.h>
#include <System/String.h>

namespace System
{
	namespace Windows
	{
		namespace Controls
		{
			namespace Primitives
			{
				ToggleButton::ToggleButton()
				{
				}

				ToggleButton::~ToggleButton()
				{
				}

				int ToggleButton::GetType() const
				{
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

				const String& ToggleButton::ToString() const
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
