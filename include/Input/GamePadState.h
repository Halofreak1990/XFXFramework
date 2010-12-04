/********************************************************
 *	GamePadState.h										*
 *														*
 *	XFX GamePadState definition file					*
 *	Copyright © XFX Team. All Rights Reserved			*
 ********************************************************/
#ifndef _GAMEPADSTATE_
#define _GAMEPADSTATE_

#include "GamePadButtons.h"
#include "GamePadThumbSticks.h"
#include "GamePadTriggers.h"

namespace XFX
{
	namespace Input
	{
		/// <summary>
		/// Represents specific information about the state of an Xbox 360 Controller, including the current state of buttons
		/// and sticks.
		/// </summary>
		struct GamePadState
		{
			GamePadButtons Buttons;
			GamePadDPad DPad;
			bool IsConnected;
			GamePadThumbSticks ThumbSticks;
			GamePadTriggers Triggers;

			bool IsButtonDown(Buttons_t button);
			bool IsButtonUp(Buttons_t button);

			operator==(GamePadState other);
			operator!=(GamePadState other);
		};
	}
}

#endif //_GAMEPADSTATE_
