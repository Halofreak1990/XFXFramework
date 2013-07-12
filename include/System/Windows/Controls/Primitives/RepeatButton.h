/*****************************************************************************
 *	RepeatButton.h  														 *
 *																			 *
 *	System::Windows::Controls::Primitives::RepeatButton definition file 	 *
 *	Copyright (c) XFX Team. All rights reserved 							 *
 *****************************************************************************/
#ifndef _SYSTEM_WINDOWS_CONTROLS_PRIMITIVES_REPEATBUTTON_
#define _SYSTEM_WINDOWS_CONTROLS_PRIMITIVES_REPEATBUTTON_

#include "ButtonBase.h"
#include <System/Windows/Input/KeyEventArgs.h>
#include <System/Windows/Input/MouseButtonEventArgs.h>

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
				 * Represents a control that raises its System::Windows::Controls::Primitives::ButtonBase::Click event repeatedly from the time it is pressed until it is released.
				 */
				class RepeatButton : public ButtonBase
				{
				protected:
					void OnClick();
					void OnKeyDown(KeyEventArgs * const e);
					void OnKeyUp(KeyEventArgs * const e);
					void OnLostMouseCapture(MouseEventArgs * const e);
					void OnMouseEnter(MouseEventArgs * const e);
					void OnMouseLeave(MouseEventArgs * const e);
					void OnMouseLeftButtonDown(MouseButtonEventArgs * const e);
					void OnMouseLeftButtonUp(MouseButtonEventArgs * const e);

				public:
					int Delay;
					int Interval;

					RepeatButton();

					static const Type& GetType();
				};
			}
		}
	}
}

#endif //_SYSTEM_WINDOWS_CONTROLS_PRIMITIVES_REPEATBUTTON_
