#ifndef _GAMERSERVICES_ENUMS_H_
#define _GAMERSERVICES_ENUMS_H_

namespace XFX
{
	namespace GamerServices
	{
		/// <summary>
		/// Indicates how sensitive this gamer prefers controller input to be.
		/// </summary>
		struct ControllerSensitivity
		{
			enum type
			{
				High,
				Low,
				Medium
			};
		};

		/// <summary>
		/// Indicates how difficult this gamer likes things to be.
		/// </summary>
		struct GameDifficulty
		{
			enum type
			{
				Easy,
				Hard,
				Normal
			};
		};

		/// <summary>
		/// This style of social gaming preferred by this Xbox Live member.
		/// </summary>
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

		/// <summary>
		/// Defines the different icons for a message box.
		/// </summary>
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

		/// <summary>
		/// Determines where notifications appear on the screen.
		/// </summary>
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
		
		/// <summary>
		/// Indicates which camera angle this gamer prefers to use in racing games.
		/// </summary>
		struct RacingCameraAngle
		{
			enum type
			{
				Back,
				Front,
				Inside
			};
		};

		typedef ControllerSensitivity::type		ControllerSensitivity_t;
		typedef GameDifficulty::type			GameDifficulty_t;
		typedef GamerZone::type					GamerZone_t;
		typedef MessageBoxIcon::type			MessageBoxIcon_t;
		typedef NotificationPosition::type		NotificationPosition_t;
		typedef RacingCameraAngle::type			RacingCameraAngle_t;
	}
}

#endif //_GAMERSERVICES_ENUMS_H_
