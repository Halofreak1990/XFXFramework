#include <System/Windows/Controls/Control.h>
#include <System/Int32.h>
#include <System/Windows/Media/SolidColorBrush.h>

namespace System
{
	namespace Windows
	{
		namespace Controls
		{
			Control::Control()
				: Background(null), BorderBrush(null), BorderThickness(3), Foreground(new SolidColorBrush(Color::White)), Padding(0), TabIndex(Int32::MaxValue)
			{
			}

			Control::~Control()
			{
				delete Background;
				delete BorderBrush;
				delete Foreground;
			}

			void Control::OnGotFocus(RoutedEventArgs* e)
			{
				GotFocus(this, e);
			}

			void Control::OnKeyDown(KeyEventArgs* e)
			{
				KeyDown(this, e);
			}

			void Control::OnKeyUp(KeyEventArgs* e)
			{
				KeyUp(this, e);
			}

			void Control::OnLostFocus(RoutedEventArgs* e)
			{
				LostFocus(this, e);
			}

			void Control::OnMouseEnter(MouseEventArgs* e)
			{
				MouseEnter(this, e);
			}

			void Control::OnMouseLeave(MouseEventArgs* e)
			{
				MouseEnter(this, e);
			}

			void Control::OnMouseMove(MouseEventArgs* e)
			{
				MouseMove(this, e);
			}

			bool Control::Focus()
			{
				//! TODO: implement

				return true;
			}

			int Control::GetType()
			{
			}

			bool Control::operator ==(const Control& right) const
			{
				return Object::ReferenceEquals(*this, right);
			}

			bool Control::operator !=(const Control& right) const
			{
				return !Object::ReferenceEquals(*this, right);
			}
		}
	}
}
