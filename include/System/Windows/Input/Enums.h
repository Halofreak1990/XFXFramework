#pragma once

namespace System
{
	namespace Windows
	{
		namespace Input
		{
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

			typedef Keys::type	Keys_t;
		}
	}
}
