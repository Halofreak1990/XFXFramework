#pragma once

#include <System/Windows/Media/Brush.h>
#include <System/Windows/Media/Color.h>

namespace System
{
	namespace Windows
	{
		namespace Media
		{
			// Paints an area with a solid color.
			class SolidColorBrush : public Brush
			{
			public:
				System::Windows::Media::Color Color;

				SolidColorBrush();
				SolidColorBrush(const System::Windows::Media::Color color);

				static int GetType();
			};
		}
	}
}
