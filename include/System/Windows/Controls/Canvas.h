#ifndef _SYSTEM_WINDOWS_CONTROLS_CANVAS_
#define _SYSTEM_WINDOWS_CONTROLS_CANVAS_

#include <System/Windows/Controls/Panel.h>

namespace System
{
	namespace Windows
	{
		namespace Controls
		{
			/**
			 * Defines an area within which you can explicitly position child objects by using coordinates that are relative to the area.
			 */
			class Canvas : public Panel
			{
			protected:
				Size ArrangeOverride(const Size arrangeSize);
				Size MeasureOverride(const Size constraint);

			public:
				static const DependencyProperty<Int32> LeftProperty;
				static const DependencyProperty<Int32> TopProperty;
				static const DependencyProperty<Int32> ZIndexProperty;

				Canvas();

				static int GetLeft(UIElement * const element);
				static int GetTop(UIElement * const element);
				static int GetZIndex(UIElement * const element);
				static const Type& GetType();
				static void SetLeft(UIElement * const element, const int left);
				static void SetTop(UIElement * const element, const int top);
				static void SetZIndex(UIElement * const element, const int zIndex);

				bool operator==(const Canvas& right) const;
				bool operator!=(const Canvas& right) const;
			};
		}
	}
}

#endif //_SYSTEM_WINDOWS_CONTROLS_CANVAS_
