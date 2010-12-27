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
		/// <summary>
		/// Allows retrieval of user interaction with an XBOX Controller
		/// and setting of controller vibration motors.
		/// </summary>
		class GamePad
		{
		private:
			GamePad(); // Private constructor to prevent instantiation.

		public:
			static GamePadState GetState(PlayerIndex_t playerIndex);
			static GamePadState GetState(PlayerIndex_t playerIndex, GamePadDeadZone_t deadZoneMode);
			static int SetVibration(PlayerIndex_t playerIndex, float leftMotor, float rightMotor);
		};
	}
}

#endif //_XFX_INPUT_GAMEPAD_
