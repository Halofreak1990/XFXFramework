/*****************************************************************************
 *	UIElement.h																 *
 *																			 *
 *	System::Windows::UIElement definition file								 *
 *	Copyright (c) XFX Team. All rights reserved								 *
 *****************************************************************************/
#ifndef _SYSTEM_WINDOWS_UIELEMENT_
#define _SYSTEM_WINDOWS_UIELEMENT_

#include <System/Windows/DependencyObject.h>
#include <System/Windows/DependencyProperty.h>
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

		/**
		 * System::Windows::UIElement is a base class for most of the objects that have visual appearance and can process basic input.
		 */
		class UIElement : public DependencyObject
		{
		protected:
			UIElement();

		public:
			Size getRenderSize() const;
			byte Opacity;
			static const DependencyProperty<byte> OpacityProperty;
			/**
			 * Gets or sets the visibility of a System::Windows::UIElement. A System::Windows::UIElement that is not visible does not render and does not communicate its desired size to layout.
			 */
			Visibility_t getVisibility() const;
			void setVisibility(const Visibility_t value);
			static const DependencyProperty<Visibility_t> VisibilityProperty;
			
			virtual ~UIElement();

			void Arrange(const Rect finalRect);
			static const Type& GetType();
			void InvalidateArrange();
			void InvalidateMeasure();
			void Measure(const Size availableSize);
			/**
			 * Ensures that all positions of child objects of a System::Windows::UIElement are properly updated for layout.
			 */
			void UpdateLayout();

			bool operator==(const UIElement& right) const;
			bool operator!=(const UIElement& right) const;

			RoutedEventHandler	GotFocus;
			KeyEventHandler		KeyDown;
			KeyEventHandler		KeyUp;
			RoutedEventHandler	LostFocus;
			MouseEventHandler	MouseEnter;
			MouseEventHandler	MouseLeave;
			EventHandler		MouseLeftButtonDown;
			EventHandler		MouseLeftButtonUp;
			MouseEventHandler	MouseMove;
			EventHandler		MouseWheel;
		};
	}
}

#endif //_SYSTEM_WINDOWS_UIELEMENT_
