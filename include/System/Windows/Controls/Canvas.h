#ifndef _SYSTEM_WINDOWS_CONTROLS_CANVAS_
#define _SYSTEM_WINDOWS_CONTROLS_CANVAS_

#include <System/Windows/Controls/Panel.h>

namespace System
{
	namespace Windows
	{
		namespace Controls
		{
			// Defines an area within which you can explicitly position child objects by using coordinates that are relative to the area.
			class Canvas : public Panel
			{
			protected:
				Size ArrangeOverride(const Size arrangeSize);
				Size MeasureOverride(const Size constraint);

			public:
				static const String LeftProperty;
				static const String TopProperty;
				static const String ZIndexProperty;

				Canvas();

				static int GetLeft(const UIElement& element);
				static int GetTop(const UIElement& element);
				static int GetZIndex(const UIElement& element);
				int GetType() const;
				static void SetLeft(const UIElement& element, const int left);
				static void SetTop(const UIElement& element, const int top);
				static void SetZIndex(const UIElement& element, const int zIndex);

				bool operator==(const Canvas& right) const;
				bool operator!=(const Canvas& right) const;
			};
		}
	}
}

#endif //_SYSTEM_WINDOWS_CONTROLS_CANVAS_
