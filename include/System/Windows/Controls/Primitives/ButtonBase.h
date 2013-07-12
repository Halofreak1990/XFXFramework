/*****************************************************************************
 *	ButtonBase.h															 *
 *																			 *
 *	System::Windows::Controls::Primitives::ButtonBase definition file		 *
 *	Copyright (c) XFX Team. All rights reserved 							 *
 *****************************************************************************/
#ifndef _SYSTEM_WINDOWS_CONTROLS_PRIMITIVES_BUTTONBASE_
#define _SYSTEM_WINDOWS_CONTROLS_PRIMITIVES_BUTTONBASE_

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
				/**
				 * Represents the base class for all button controls, such as System::Windows::Controls::Button, System::Windows::Controls::Primitives::RepeatButton, and System::Windows::Controls::HyperlinkButton.
				 */
				class ButtonBase : public ContentControl
				{
				private:
					bool isFocused;

				protected:
					ButtonBase();

					virtual void OnClick();
					void OnGotFocus(RoutedEventArgs * const e);
					void OnKeyDown(KeyEventArgs * const e);
					void OnKeyUp(KeyEventArgs * const e);
					void OnMouseEnter(MouseEventArgs * const e);
					void OnMouseLeave(MouseEventArgs * const e);
					void OnMouseMove(MouseEventArgs * const e);

					void UpdateVisualState(bool useTransitions);

				public:
					bool IsFocused() const;

					virtual ~ButtonBase();

					static const Type& GetType();
					
					RoutedEventHandler Click;

					bool operator ==(const ButtonBase& right) const;
					bool operator !=(const ButtonBase& right) const;
				};
			}
		}
	}
}

#endif //_SYSTEM_WINDOWS_CONTROLS_PRIMITIVES_BUTTONBASE_
