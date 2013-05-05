#pragma once

#include <System/Windows/FrameworkElement.h>

namespace System
{
	namespace Windows
	{
		namespace Controls
		{
			namespace Primitives
			{
				// Displays content on top of existing content, within the bounds of the control.
				class Popup : public FrameworkElement
				{
				public:
					UIElement* Child;
					bool getIsOpen() const;
					void setIsOpen(const bool value);
					int HorizontalOffset;
					int VerticalOffset

					Popup();

					
				};
			}
		}
	}
}
