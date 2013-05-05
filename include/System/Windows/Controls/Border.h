#pragma once

#include <System/Windows/CornerRadius.h>
#include <System/Windows/FrameworkElement.h>
#include <System/Windows/Media/Brush.h>

using namespace System::Windows::Media;

namespace System
{
	namespace Windows
	{
		namespace Controls
		{
			// Draws a border, background, or both around another object.
			class Border : public FrameworkElement
			{
			public:
				Border();
				~Border();

				Brush* Background;
				Brush* BorderBrush;
				Thickness BorderThickness;
				UIElement* Child;
				System::Windows::CornerRadius CornerRadius;
				Thickness Padding;

				int GetType() const;
			};
		}
	}
}
