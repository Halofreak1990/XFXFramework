/********************************************************
 *	GamePadCapabilities.h								*
 *														*
 *	XFX GamePadCapabilities definition file				*
 *	Copyright © XFX Team. All Rights Reserved			*
 ********************************************************/
#ifndef GAMEPADCAPABILITIES_H
#define GAMEPADCAPABILITIES_H

#include "GamePadType.h"

namespace XFX
{
	namespace Input
	{
		struct GamePadCapabilities
		{
			GamePadType GamePadType;
			int HasAButton;
			int HasBButton;
			int HasBackButton;
			int HasDPadDownButton;
			int HasDPadLeftButton;
			int HasDPadRightButton;
			int HasDPadUpButton;
			int HasLeftStickButton;
			int HasLeftTrigger;
			int HasLeftVibrationMotor;
			int HasLeftXThumbStick;
			int HasLeftYThumbStick;
			int HasRightStickButton;
			int HasRightTrigger;
			int HasRightVibrationMotor;
			int HasRightXThumbStick;
			int HasRightYThumbStick;
			int HasStartButton;
			int HasWhiteButton;
			int HasXButton;
			int HasYButton;
			int IsConnected;
		};
	}
}

#endif //GAMEPADCAPABILITIES_H
