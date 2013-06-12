#ifndef _SYSTEM_WINDOWS_ENUMS_
#define _SYSTEM_WINDOWS_ENUMS_

namespace System
{
	namespace Windows
	{
		// Describes the kind of value that a GridLength object is holding.
		struct GridUnitType
		{
			enum type
			{
				Auto,
				Pixel,
				Star
			};
		};

		// 
		struct HorizontalAlignment
		{
			enum type
			{
				// 
				Left,
				// 
				Center,
				// 
				Right,
				// 
				Stretch
			};
		};

		// Specifies the buttons to include when you display a message box.
		struct MessageBoxButton
		{
			enum type
			{
				// Displays only the OK button.
				Ok,
				// Displays both the OK and Cancel buttons.
				OkCancel
			};
		};

		// Represents a user's response to a message box.
		struct MessageBoxResult
		{
			enum type
			{
				// This value is not currently used.
				None,
				// The user clicked the OK button.
				Ok,
				// The user clicked the Cancel button or pressed ESC.
				Cancel,
				// This value is not currently used.
				Yes = 6,
				// This value is not currently used.
				No = 7
			};
		};

		// Describes how a child element is vertically positioned or stretched within a parent's layout slot.
		struct VerticalAlignment
		{
			enum type
			{
				// The element is aligned to the top of the parent's layout slot.
				Top,
				// The element is aligned to the center of the parent's layout slot.
				Center,
				// The element is aligned to the bottom of the parent's layout slot.
				Bottom,
				// The element is stretched to fill the entire layout slot of the parent element.
				Stretch
			};
		};

		// Specifies the display state of an element.
		struct Visibility
		{
			enum type
			{
				// Do not display the element, and do not reserve space for it in layout.
				Collapsed = 1,
				// Display the element.
				Visible = 0
			};
		};

		// 
		struct WindowState
		{
			enum type
			{
				// 
				Normal,
				// 
				Maximized
			};
		};

		// Defines constants that indicate the appearance of the title bar and border of an application window.
		struct WindowStyle
		{
			enum type
			{
				// The window displays a title bar and border.
				SingleBorderWindow,
				// The window does not display a title bar or border.
				None,
				// The window does not display a title bar or border, and the window corners are rounded.
				BorderlessRoundCornersWindow
			};
		};

		// Describes the kind of value that a GridLength object is holding.
		typedef GridUnitType::type			GridUnitType_t;
		// 
		typedef HorizontalAlignment::type	HorizontalAlignment_t;
		// Specifies the buttons to include when you display a message box.
		typedef MessageBoxButton::type		MessageBoxButton_t;
		// Represents a user's response to a message box.
		typedef MessageBoxResult::type		MessageBoxResult_t;
		// Describes how a child element is vertically positioned or stretched within a parent's layout slot.
		typedef VerticalAlignment::type		VerticalAlignment_t;
		// Specifies the display state of an element.
		typedef Visibility::type			Visibility_t;
		// 
		typedef WindowState::type			WindowState_t;
		// Defines constants that indicate the appearance of the title bar and border of an application window.
		typedef WindowStyle::type			WindowStyle_t;
	}
}

#endif //_SYSTEM_WINDOWS_ENUMS_
