#pragma once

#include <System/Windows/RoutedEventArgs.h>
#include <System/Windows/Input/Enums.h>

namespace System
{
	namespace Windows
	{
		namespace Input
		{
			// Provides event data for the System::Windows::UIElement.KeyUp and System::Windows::UIElement.KeyDown events.
			class KeyEventArgs : public RoutedEventArgs
			{
			private:
				Keys_t key;

			public:
				bool Handled;
				Keys_t getKey() const;
			};

			typedef Event<Object*, KeyEventArgs*> KeyEventHandler;
		}
	}
}
