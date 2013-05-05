#pragma once

#include <System/Windows/RoutedEventArgs.h>
#include <System/Windows/Point.h>

namespace System
{
	namespace Windows
	{
		class UIElement;

		namespace Input
		{
			// 
			class MouseEventArgs : public RoutedEventArgs
			{
			public:
				Point GetPosition(UIElement const * const relativeTo) const;
			};

			typedef Event<Object*, MouseEventArgs*> MouseEventHandler;
		}
	}
}
