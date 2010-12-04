/********************************************************
 *	Enums.h												*
 *														*
 *	XFX::Input enumeration definition file				*
 *	Copyright © XFX Team. All Rights Reserved			*
 ********************************************************/
#ifndef _XFX_INPUT_ENUMS_
#define _XFX_INPUT_ENUMS_

namespace XFX
{
	namespace Input
	{
		/// <summary>
		/// Enumerates input device buttons.
		/// </summary>
		struct Buttons
		{
			enum type
			{
				A = 0,
				B = 1,
				Back = 0x20,
				Black = 4,
				DPadDown = 0x02,
				DPadLeft = 0x04,
				DPadRight = 0x08,
				DPadUp = 0x01,
				LeftStick = 0x40,
				LeftThumbStickDown,
				LeftThumbStickLeft,
				LeftThumbStickRight,
				LeftThumbStickUp,
				LeftTrigger = 6,
				RightStick = 0x80,
				RightThumbStickDown,
				RightThumbStickLeft,
				RightThumbStickRight,
				RightThumbStickUp,
				RightTrigger = 7,
				Start = 0x10,
				White = 5,
				X = 2,
				Y = 3
			};
		};

		/// <summary>
		/// Identifies the state of a mouse button or Xbox Controller button.
		/// </summary>
		struct ButtonState
		{
			enum type
			{
				Pressed = 1,
				Released = 0
			};
		};

		/// <summary>
		/// Specifies a type of dead zone processing to apply to Xbox controller analog sticks when calling GamePad::GetState.
		/// </summary>
		struct GamePadDeadZone
		{
			enum type
			{
				Circular,
				IndependantAxes,
				None
			};
		};

		/// <summary>
		/// Describes the type of a given Xbox controller.
		/// </summary>
		struct GamePadType
		{
			enum type
			{
				ArcadeStick,
				DancePad,
				DrumKit,
				FlightStick,
				GamePad,
				Guitar,
				Unknown,
				Wheel
			};
		};

		/// <summary>
		/// Identifies the state of a keyboard key.
		/// </summary>
		struct KeyState
		{
			enum type
			{
				Down = 1,
				Up = 0
			};
		};

		typedef Buttons::type Buttons_t;
		typedef ButtonState::type ButtonState_t;
		typedef GamePadDeadZone::type GamePadDeadZone_t;
		typedef GamePadType::type GamePadType_t;
		typedef KeyState::type KeyState_t;
	}
}

#endif //_XFX_INPUT_ENUMS_
