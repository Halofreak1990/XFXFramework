#ifndef _SYSTEM_COMPONENTMODEL_CANCELEVENTARGS_
#define _SYSTEM_COMPONENTMODEL_CANCELEVENTARGS_

#include <System/EventArgs.h>

namespace System
{
	namespace ComponentModel
	{
		// Provides data for a cancelable event.
		class CancelEventArgs : public EventArgs
		{
		public:
			bool Cancel;

			CancelEventArgs();
			CancelEventArgs(const bool value);

			int GetType() const;
		};
	}
}

#endif //_SYSTEM_COMPONENTMODEL_CANCELEVENTARGS_
