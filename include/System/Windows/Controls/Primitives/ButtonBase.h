#pragma once

#include <System/Windows/Controls/ContentControl.h>
#include <System/Windows/Input/KeyEventArgs.h>
#include <System/Windows/Input/MouseEventArgs.h>

using namespace System::Windows::Input;

namespace System
{
	namespace Windows
	{
		namespace Controls
		{
			namespace Primitives
			{
				// Represents the base class for all button controls, such as System::Windows::Controls::Button, System::Windows::Controls::Primitives::RepeatButton, and System::Windows::Controls::HyperlinkButton.
				class ButtonBase : public ContentControl
				{
				private:
					bool isFocused;

				protected:
					ButtonBase();

					virtual void OnClick();
					void OnGotFocus(RoutedEventArgs* e);
					void OnKeyDown(KeyEventArgs* e);
					void OnKeyUp(KeyEventArgs* e);
					void OnMouseEnter(MouseEventArgs* e);
					void OnMouseLeave(MouseEventArgs* e);
					void OnMouseMove(MouseEventArgs* e);

					void UpdateVisualState(bool useTransitions);

				public:
					bool IsFocused() const;

					virtual ~ButtonBase();

					static int GetType();
					
					RoutedEventHandler Click;

					bool operator ==(const ButtonBase& right) const;
					bool operator !=(const ButtonBase& right) const;
				};
			}
		}
	}
}
