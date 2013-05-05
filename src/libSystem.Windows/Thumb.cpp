#include <System/Windows/Controls/Primitives/Thumb.h>

namespace System
{
	namespace Windows
	{
		namespace Controls
		{
			namespace Primitives
			{
				Thumb::Thumb()
				{
				}

				void Thumb::CancelDrag()
				{
					// TODO: calculate change, if any
					DragCompleted(this, new DragCompletedEventArgs(0, 0, true));
				}

				int Thumb::GetType() const
				{
				}

				void Thumb::OnGotFocus(RoutedEventArgs* e)
				{
				}

				void Thumb::OnLostFocus(RoutedEventArgs* e)
				{
				}

				void Thumb::OnMouseEnter(MouseEventArgs* e)
				{
				}

				void Thumb::OnMouseLeave(MouseEventArgs* e)
				{
				}

				void Thumb::OnMouseMove(MouseEventArgs* e)
				{
				}

				bool Thumb::operator ==(const Thumb& right) const
				{
					return Object::ReferenceEquals(*this, right);
				}

				bool Thumb::operator !=(const Thumb& right) const
				{
					return !Object::ReferenceEquals(*this, right);
				}
			}
		}
	}
}
