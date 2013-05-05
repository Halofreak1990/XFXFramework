#include <System/Windows/Controls/Primitives/ButtonBase.h>

namespace System
{
	namespace Windows
	{
		namespace Controls
		{
			namespace Primitives
			{
				ButtonBase::ButtonBase()
				{
				}

				ButtonBase::~ButtonBase()
				{
				}

				bool ButtonBase::IsFocused() const
				{
					return isFocused;
				}

				void ButtonBase::OnClick()
				{
					RoutedEventArgs* rea = new RoutedEventArgs();
					//rea->_originalSource = this;
					Click(this, rea);
				}

				void ButtonBase::OnGotFocus(RoutedEventArgs* e)
				{
					Control::OnGotFocus(e);
					this->isFocused = true;
					this->UpdateVisualState(true);
				}

				void ButtonBase::UpdateVisualState(bool useTransitions)
				{
				}

				bool ButtonBase::operator ==(const ButtonBase& right) const
				{
					return Object::ReferenceEquals(*this, right);
				}

				bool ButtonBase::operator !=(const ButtonBase& right) const
				{
					return !Object::ReferenceEquals(*this, right);
				}
			}
		}
	}
}
