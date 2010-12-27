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
		/// <summary>
		/// Represents specific information about the state of an Xbox Controller, including the current state of buttons
		/// and sticks.
		/// </summary>
		struct GamePadState
		{
			GamePadButtons Buttons;
			GamePadDPad DPad;
			bool IsConnected;
			GamePadThumbSticks ThumbSticks;
			GamePadTriggers Triggers;

			GamePadState(GamePadThumbSticks thumbSticks, GamePadTriggers triggers, GamePadButtons buttons, GamePadDPad dPad);
			GamePadState(Vector2 leftThumbStick, Vector2 rightThumbStick, float leftTrigger, float rightTrigger, Buttons_t buttons[]);
			GamePadState();
			GamePadState(const GamePadState &obj);

			bool Equals(const GamePadState obj);
			int GetHashCode();

			bool IsButtonDown(Buttons_t button);
			bool IsButtonUp(Buttons_t button);

			bool operator==(const GamePadState other);
			bool operator!=(const GamePadState other);
		};
	}
}

#endif //_XFX_INPUT_GAMEPADSTATE_
