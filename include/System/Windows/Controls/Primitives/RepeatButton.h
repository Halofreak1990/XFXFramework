#include "ButtonBase.h"
#include <System/Windows/Input/KeyEventArgs.h>
#include <System/Windows/Input/MouseButtonEventArgs.h>

using namespace System::Windows::Input;

namespace System
{
	namespace Windows
	{
		namespace Controls
		{
			namespace Primitives
			{
				// Represents a control that raises its System::Windows::Controls::Primitives::ButtonBase::Click event repeatedly from the time it is pressed until it is released.
				class RepeatButton : public ButtonBase
				{
				protected:
					void OnClick();
					void OnKeyDown(KeyEventArgs* e);
					void OnKeyUp(KeyEventArgs* e);
					void OnLostMouseCapture(MouseEventArgs* e);
					void OnMouseEnter(MouseEventArgs* e);
					void OnMouseLeave(MouseEventArgs* e);
					void OnMouseLeftButtonDown(MouseButtonEventArgs* e);
					void OnMouseLeftButtonUp(MouseButtonEventArgs* e);

				public:
					int Delay;
					int Interval;

					RepeatButton();

					static int GetType();

				};
			}
		}
	}
}
