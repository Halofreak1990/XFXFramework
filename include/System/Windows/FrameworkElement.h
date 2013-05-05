#pragma once

#include <System/Windows/Thickness.h>
#include <System/Windows/UIElement.h>

namespace System
{
	namespace Windows
	{
		class DependencyObject;
		struct Size;

		// Provides a framework of common APIs for objects that participate in layout.
		class FrameworkElement : public UIElement
		{
		protected:
			FrameworkElement();

			virtual Size ArrangeOverride(const Size finalSize);
			virtual Size MeasureOverride(const Size finalSize);

		public:
			int Height;
			HorizontalAlignment_t HorizontalAlignment;
			// Gets or sets the outer margin of a System::Windows::FrameworkElement.
			Thickness Margin;
			DependencyObject* Parent;
			VerticalAlignment_t VerticalAlignment;
			int Width;

			virtual ~FrameworkElement();

			int GetType() const;
		};
	}
}
