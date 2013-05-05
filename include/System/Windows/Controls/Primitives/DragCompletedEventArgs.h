#pragma once

#include <System/Windows/RoutedEventArgs.h>

namespace System
{
	namespace Windows
	{
		namespace Controls
		{
			namespace Primitives
			{
				// Provides data for the System::Windows::Controls::Primitives::Thumb::DragCompleted event that occurs when a user completes a drag operation with the mouse of a System::Windows::Controls::Primitives::Thumb control.
				class DragCompletedEventArgs : public RoutedEventArgs
				{
				private:
					bool _canceled;
					int _horizontalChange;
					int _verticalChange;

				public:
					bool Canceled() const
					{
						return _canceled;
					}

					int getHorizontalChange() const
					{
						return _horizontalChange;
					}

					int getVerticalChange() const
					{
						return _verticalChange;
					}

					DragCompletedEventArgs(int horizontalChange, int verticalChange, bool canceled)
						: _canceled(canceled), _horizontalChange(horizontalChange), _verticalChange(verticalChange)
					{
					}
				};

				typedef Event<Object*, DragCompletedEventArgs*> DragCompletedEventHandler;
			}
		}
	}
}
