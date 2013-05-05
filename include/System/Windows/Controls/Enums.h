#pragma once

namespace System
{
	namespace Windows
	{
		namespace Controls
		{
			// Specifies when the System::Windows::Controls::Primitives::ButtonBase::Click event should be raised for a control.
			struct ClickMode
			{
				enum type
				{
					Release,
					Press,
					Hover
				};
			};

			// Defines the different orientations that a control or layout can have.
			struct Orientation
			{
				enum type
				{
					Horizontal,
					Vertical
				};
			};

			// Specifies when the System::Windows::Controls::Primitives::ButtonBase::Click event should be raised for a control.
			typedef ClickMode::type		ClickMode_t;
			// Defines the different orientations that a control or layout can have.
			typedef Orientation::type	Orientation_t;
		}
	}
}
