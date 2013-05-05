#pragma once

#include <System/Event.h>

namespace System
{
	namespace Windows
	{
		// Contains state information and event data associated with a routed event.
		class RoutedEventArgs : public EventArgs
		{
		private:
			Object* _originalSource;

			friend class FrameworkElement;

			RoutedEventArgs(Object* originalSource) : _originalSource(originalSource) { }

		public:
			Object* getOriginalSource() const { return _originalSource; }

			RoutedEventArgs() : _originalSource(null) { }
			virtual ~RoutedEventArgs() { }
		};

		typedef Event<Object*, RoutedEventArgs*> RoutedEventHandler;
	}
}
