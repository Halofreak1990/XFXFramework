/*****************************************************************************
 *	Button.h																 *
 *																			 *
 *	System::Windows::Controls::Button definition file						 *
 *	Copyright (c) XFX Team. All rights reserved 							 *
 *****************************************************************************/
#ifndef _SYSTEM_WINDOWS_CONTROLS_BUTTON_
#define _SYSTEM_WINDOWS_CONTROLS_BUTTON_

#include <System/Windows/Controls/Primitives/ButtonBase.h>

using namespace System::Windows::Controls::Primitives;

namespace System
{
	namespace Windows
	{
		namespace Controls
		{
			/**
			 * Represents a button control.
			 */
			class Button : public ButtonBase
			{
			protected:
				void OnClick();

			public:
				Button();
				~Button();

				static const Type& GetType();

				bool operator ==(const Button& right) const;
				bool operator !=(const Button& right) const;
			};
		}
	}
}

#endif //_SYSTEM_WINDOWS_CONTROLS_BUTTON_
