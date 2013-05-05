#pragma once

#include <System/Windows/FrameworkElement.h>
#include <System/Windows/Media/Brush.h>

using namespace System::Windows::Media;

namespace System
{
	namespace Windows
	{
		namespace Controls
		{
			// Represents the base class for UI elements that use a System::Windows::Controls::ControlTemplate to define their appearance.
			class Control : public FrameworkElement
			{
			protected:
				Control();

				virtual void OnGotFocus(RoutedEventArgs* e);
				virtual void OnKeyDown(KeyEventArgs* e);
				virtual void OnKeyUp(KeyEventArgs* e);
				virtual void OnLostFocus(RoutedEventArgs* e);
				virtual void OnMouseEnter(MouseEventArgs* e);
				virtual void OnMouseLeave(MouseEventArgs* e);
				virtual void OnMouseMove(MouseEventArgs* e);

			public:
				Brush* Background;
				Brush* BorderBrush;
				Thickness BorderThickness;
				Brush* Foreground;
				HorizontalAlignment_t HorizontalContentAlignment;
				bool IsEnabled;
				bool IsTabStop;
				Thickness Padding;
				int TabIndex;
				VerticalAlignment_t VerticalContentAlignment;

				virtual ~Control();

				bool ApplyTemplate();
				bool Focus();
				int GetType() const;

				bool operator ==(const Control& right) const;
				bool operator !=(const Control& right) const;
			};
		}
	}
}
