/*****************************************************************************
 *	FrameworkElement.h														 *
 *																			 *
 *	System::Windows::FrameworkElement definition file						 *
 *	Copyright (c) XFX Team. All rights reserved								 *
 *****************************************************************************/
#ifndef _SYSTEM_WINDOWS_FRAMEWORKELEMENT_
#define _SYSTEM_WINDOWS_FRAMEWORKELEMENT_

#include <System/Int32.h>
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
			static const DependencyProperty<Int32> HeightProperty;
			HorizontalAlignment_t HorizontalAlignment;
			static const DependencyProperty<HorizontalAlignment_t> HorizontalAlignmentProperty;
			// Gets or sets the outer margin of a System::Windows::FrameworkElement.
			Thickness getMargin() const;
			void setMargin(const Thickness value);
			static const DependencyProperty<Thickness> MarginProperty;
			DependencyObject* Parent;
			VerticalAlignment_t VerticalAlignment;
			static const DependencyProperty<VerticalAlignment_t> VerticalAlignmentProperty;
			int getWidth() const;
			void setWidth(const int value);
			static const DependencyProperty<Int32> WidthProperty;

			virtual ~FrameworkElement();

			static int GetType();
		};
	}
}

#endif //_SYSTEM_WINDOWS_FRAMEWORKELEMENT_
