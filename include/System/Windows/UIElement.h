#pragma once

#include <System/Windows/DependencyObject.h>
#include <System/Windows/Enums.h>
#include <System/Windows/Rect.h>
#include <System/Windows/Input/KeyEventArgs.h>
#include <System/Windows/Input/MouseEventArgs.h>

using namespace System::Windows::Input;

namespace System
{
	namespace Windows
	{
		struct Size;

		// System::Windows::UIElement is a base class for most of the objects that have visual appearance and can process basic input.
		class UIElement : public DependencyObject, public Object
		{
		protected:
			UIElement();

		public:
			Size getRenderSize() const;
			byte Opacity;
			// Gets or sets the visibility of a System::Windows::UIElement. A System::Windows::UIElement that is not visible does not render and does not communicate its desired size to layout.
			Visibility_t Visibility;
			
			virtual ~UIElement();

			void Arrange(const Rect finalRect);
			int GetType() const;
			void InvalidateArrange();
			void InvalidateMeasure();
			void Measure(const Size availableSize);
			// Ensures that all positions of child objects of a System::Windows::UIElement are properly updated for layout.
			void UpdateLayout();

			bool operator==(const UIElement& right) const;
			bool operator!=(const UIElement& right) const;

			RoutedEventHandler	GotFocus;
			KeyEventHandler		KeyDown;
			KeyEventHandler		KeyUp;
			RoutedEventHandler	LostFocus;
			MouseEventHandler	MouseEnter;
			MouseEventHandler	MouseLeave;
			Event<Object*, EventArgs> MouseLeftButtonDown;
			Event<Object*, EventArgs> MouseLeftButtonUp;
			MouseEventHandler	MouseMove;
			Event<Object*, EventArgs> MouseWheel;
		};
	}
}
