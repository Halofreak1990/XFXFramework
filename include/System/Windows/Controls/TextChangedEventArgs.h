#pragma once

#include <System/Windows/RoutedEventArgs.h>

namespace System
{
	namespace Windows
	{
		namespace Controls
		{
			class TextChangedEventArgs : public RoutedEventArgs
			{

			};

			typedef Event<Object*, TextChangedEventArgs> TextChangedEventHandler;
		}
	}
}
