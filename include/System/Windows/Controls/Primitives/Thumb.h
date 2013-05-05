#pragma once

#include <System/Windows/Controls/Control.h>
#include <System/Windows/Controls/Enums.h>
#include <System/Windows/Controls/Primitives/DragCompletedEventArgs.h>
#include <System/Windows/Controls/Primitives/DragDeltaEventArgs.h>
#include <System/Windows/Controls/Primitives/DragStartedEventArgs.h>

namespace System
{
	namespace Windows
	{
		namespace Controls
		{
			namespace Primitives
			{
				// Represents a control that can be dragged by the user.
				class Thumb : public Control
				{
				protected:
					void OnGotFocus(RoutedEventArgs* e);
					void OnLostFocus(RoutedEventArgs* e);
					void OnMouseEnter(MouseEventArgs* e);
					void OnMouseLeave(MouseEventArgs* e);
					void OnMouseMove(MouseEventArgs* e);

				public:
					ClickMode_t ClickMode;

					Thumb();

					void CancelDrag();
					int GetType() const;

					bool operator ==(const Thumb& right) const;
					bool operator !=(const Thumb& right) const;

					DragCompletedEventHandler DragCompleted;
				};
			}
		}
	}
}
