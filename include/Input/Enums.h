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
		// Enumerates input device buttons.
		struct Buttons
		{
			enum type
			{
				A = 0x1000,
				B = 0x2000,
				Back = 0x20,
				Black = 0x100,
				DPadDown = 0x02,
				DPadLeft = 0x04,
				DPadRight = 0x08,
				DPadUp = 0x01,
				LeftStick = 0x40,
				LeftThumbstickDown = 0x20000000,
				LeftThumbstickLeft = 0x200000,
				LeftThumbstickRight = 0x40000000,
				LeftThumbstickUp = 0x10000000,
				LeftTrigger = 0x800000,
				RightStick = 0x80,
				RightThumbstickDown = 0x2000000,
				RightThumbstickLeft = 0x8000000,
				RightThumbstickRight = 0x4000000,
				RightThumbstickUp = 0x1000000,
				RightTrigger = 0x400000,
				Start = 0x10,
				White = 0x200,
				X = 0x4000,
				Y = 0x8000
			};
		};

		// Identifies the state of a mouse button or Xbox Controller button.
		struct ButtonState
		{
			enum type
			{
				Pressed = 1,
				Released = 0
			};
		};

		// Specifies a type of dead zone processing to apply to Xbox controller analog sticks when calling GamePad::GetState.
		struct GamePadDeadZone
		{
			enum type
			{
				Circular,
				IndependantAxes,
				None
			};
		};

		// Describes the type of a given Xbox controller.
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

		// Identifies a particular key on a keyboard.
		struct Keys
		{
			enum type
			{
				A = 0x41,
				B = 0x42,
				Back = 0x08,
				C = 0x43,
				D = 0x44,
				Down = 0x28,
				E = 0x45,
				End = 0x23,
				Enter = 0x0D,
				Escape = 0x1B,
				F = 0x46,
				G = 0x47,
				H = 0x48,
				I = 0x49,
				J = 0x4A,
				K = 0x4B,
				L = 0x4C,
				M = 0x4D,
				N = 0x4E,
				None = 0x00,
				O = 0x4F,
				P = 0x50,
				Q = 0x51,
				R = 0x52,
				S = 0x53,
				Space = 0x20,
				T = 0x54,
				U = 0x55,
				V = 0x56,
				W = 0x57,
				X = 0x58,
				Y = 0x59,
				Z = 0x5A
			};
		};

		// Identifies the state of a keyboard key.
		struct KeyState
		{
			enum type
			{
				Down = 1,
				Up = 0
			};
		};

		typedef Buttons::type			Buttons_t;
		typedef ButtonState::type		ButtonState_t;
		typedef GamePadDeadZone::type	GamePadDeadZone_t;
		typedef GamePadType::type		GamePadType_t;
		typedef Keys::type				Keys_t;
		typedef KeyState::type			KeyState_t;
	}
}

#endif //_XFX_INPUT_ENUMS_
