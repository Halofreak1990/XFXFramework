#pragma once

#include <System/Windows/Controls/Enums.h>
#include <System/Windows/Controls/Panel.h>

namespace System
{
	namespace Windows
	{
		struct Size;

		namespace Controls
		{
			class StackPanel : public Panel
			{
			protected:
				Size ArrangeOverride(const Size arrangeSize);
				Size MeasureOverride(const Size constraint);

			public:
				Orientation_t Orientation;

				StackPanel();
			};
		}
	}
}
