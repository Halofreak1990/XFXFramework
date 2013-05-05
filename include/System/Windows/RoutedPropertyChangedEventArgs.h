#pragma once

#include <System/Windows/RoutedEventArgs.h>

namespace System
{
	namespace Windows
	{
		template <typename T>
		class RoutedPropertyChangedEventArgs : public RoutedEventArgs
		{
		public:
			const T OldValue;
			const T NewValue;

			RoutedPropertyChangedEventArgs(const T oldValue, const T newValue)
				: OldValue(oldValue), NewValue(newValue)
			{
			}
		};
	}
}
