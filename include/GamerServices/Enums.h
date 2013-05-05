/*****************************************************************************
 *	Enums.h 																 *
 *																			 *
 *	XFX::GamerServices enumerations definition file 						 *
 *	Copyright (c) XFX Team. All Rights Reserved 							 *
 *****************************************************************************/
#ifndef _XFX_GAMERSERVICES_ENUMS_H_
#define _XFX_GAMERSERVICES_ENUMS_H_

namespace XFX
{
	namespace GamerServices
	{
		// Indicates how sensitive this gamer prefers controller input to be.
		struct ControllerSensitivity
		{
			enum type
			{
				High,
				Low,
				Medium
			};
		};

		// Indicates how difficult this gamer likes things to be.
		struct GameDifficulty
		{
			enum type
			{
				Easy,
				Hard,
				Normal
			};
		};

		// This style of social gaming preferred by this Xbox Live member.
		struct GamerZone
		{
			enum type
			{
				Family,
				Pro,
				Recreation,
				Underground,
				Unknown
			};
		};

		// Defines the different icons for a message box.
		struct MessageBoxIcon
		{
			enum type
			{
				Alert,
				Error,
				None,
				Warning
			};
		};

		// Determines where notifications appear on the screen.
		struct NotificationPosition
		{
			enum type
			{
				BottomCenter,
				BottomLeft,
				BottomRight,
				Center,
				CenterLeft,
				CenterRight,
				TopCenter,
				TopLeft,
				TopRight
			};
		};
		
		// Indicates which camera angle this gamer prefers to use in racing games.
		struct RacingCameraAngle
		{
			enum type
			{
				Back,
				Front,
				Inside
			};
		};

		typedef ControllerSensitivity::type		ControllerSensitivity_t;	// Indicates how sensitive this gamer prefers controller input to be.
		typedef GameDifficulty::type			GameDifficulty_t;			// Indicates how difficult this gamer likes things to be.
		typedef GamerZone::type 				GamerZone_t;				// This style of social gaming preferred by this Xbox Live member.
		typedef MessageBoxIcon::type			MessageBoxIcon_t;			// Defines the different icons for a message box.
		typedef NotificationPosition::type		NotificationPosition_t; 	// Determines where notifications appear on the screen.
		typedef RacingCameraAngle::type 		RacingCameraAngle_t;		// Indicates which camera angle this gamer prefers to use in racing games.
	}
}

#endif //_GAMERSERVICES_ENUMS_H_
