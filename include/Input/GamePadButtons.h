/*****************************************************************************
 *	GamePadButtons.h														 *
 *																			 *
 *	XFX::Input::GamePadButtons structure definition file					 *
 *	Copyright (c) XFX Team. All Rights Reserved 							 *
 *****************************************************************************/
#ifndef _XFX_INPUT_GAMEPADBUTTONS_
#define _XFX_INPUT_GAMEPADBUTTONS_

#include "Enums.h"
#include <System/Object.h>

using namespace System;

namespace XFX
{
	namespace Input
	{
		/**
		 * Identifies whether the buttons on an Xbox Controller are pressed or released.
		 */
		struct GamePadButtons : Object
		{
			const ButtonState_t A;
			const ButtonState_t B;
			const ButtonState_t Back;
			const ButtonState_t Black;
			const ButtonState_t LeftStick;
			const ButtonState_t RightStick;
			const ButtonState_t Start;
			const ButtonState_t White;
			const ButtonState_t X;
			const ButtonState_t Y;
			
			GamePadButtons(const uint /* Buttons */ buttons);
			GamePadButtons();
			GamePadButtons(const GamePadButtons &obj);

			bool Equals(Object const * const obj) const;
			bool Equals(const GamePadButtons obj) const;
			int GetHashCode() const;
			static const Type& GetType();
			const String ToString() const;

			bool operator !=(const GamePadButtons& right) const;
			bool operator ==(const GamePadButtons& right) const;

			inline GamePadButtons operator=(const GamePadButtons& right)
			{
				return (right == *this) ? *this : GamePadButtons(right);
			}
		};
	}
}

#endif //_XFX_INPUT_GAMEPADBUTTONS_
