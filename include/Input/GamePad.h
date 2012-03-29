/********************************************************
 *	GamePad.h											*
 *														*
 *	XFX GamePad definition file							*
 *	Copyright © XFX Team. All Rights Reserved			*
 ********************************************************/
#ifndef _XFX_INPUT_GAMEPAD_
#define _XFX_INPUT_GAMEPAD_

#include <Enums.h>
#include "Enums.h"
#include "GamePadState.h"

namespace XFX
{
	namespace Input
	{
		// Allows retrieval of user interaction with an XBOX Controller
		// and setting of controller vibration motors.
		class GamePad
		{
		private:
			GamePad(); // Private constructor to prevent instantiation.

		public:
			static GamePadState GetState(const PlayerIndex_t playerIndex);
			static GamePadState GetState(const PlayerIndex_t playerIndex, const GamePadDeadZone_t deadZoneMode);
			static bool SetVibration(const PlayerIndex_t playerIndex, const float leftMotor, const float rightMotor);
		};
	}
}

#endif //_XFX_INPUT_GAMEPAD_
