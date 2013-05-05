/********************************************************
 *	GamePadState.h										*
 *														*
 *	XFX GamePadState definition file					*
 *	Copyright © XFX Team. All Rights Reserved			*
 ********************************************************/
#ifndef _XFX_INPUT_GAMEPADSTATE_
#define _XFX_INPUT_GAMEPADSTATE_

#include "GamePadButtons.h"

namespace XFX
{
	namespace Input
	{
		// Represents specific information about the state of an Xbox Controller, including the current state of buttons and sticks.
		struct GamePadState : Object
		{
			GamePadButtons Buttons;
			GamePadDPad DPad;
			bool IsConnected;
			GamePadThumbSticks ThumbSticks;
			GamePadTriggers Triggers;

			GamePadState(const GamePadThumbSticks thumbSticks, const GamePadTriggers triggers, const GamePadButtons buttons, const GamePadDPad dPad);
			GamePadState();
			GamePadState(const GamePadState &obj);

			bool Equals(const Object* obj) const;
			bool Equals(const GamePadState obj) const;
			int GetHashCode() const;
			int GetType() const;
			bool IsButtonDown(const Buttons_t button) const;
			bool IsButtonUp(const Buttons_t button) const;
			const char* ToString() const;

			bool operator==(const GamePadState& right) const;
			bool operator!=(const GamePadState& right) const;

			inline GamePadState operator =(const GamePadState right)
			{
				return (*this == right) ? *this : GamePadState(right);
			}
		};
	}
}

#endif //_XFX_INPUT_GAMEPADSTATE_
