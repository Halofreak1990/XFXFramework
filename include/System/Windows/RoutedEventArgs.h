#ifndef _SYSTEM_WINDOWS_ROUTEDEVENTARGS_
#define _SYSTEM_WINDOWS_ROUTEDEVENTARGS_

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

			RoutedEventArgs(Object * const originalSource) : _originalSource(originalSource) { }

		public:
			Object* getOriginalSource() const { return _originalSource; }

			RoutedEventArgs() : _originalSource(null) { }
			virtual ~RoutedEventArgs() { }
		};

		typedef Event<Object * const, RoutedEventArgs * const> RoutedEventHandler;
	}
}

#endif //_SYSTEM_WINDOWS_ROUTEDEVENTARGS_
