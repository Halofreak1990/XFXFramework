#pragma once

#include <System/ComponentModel/CancelEventArgs.h>

namespace System
{
	namespace ComponentModel
	{
		// 
		class ClosingEventArgs : public CancelEventArgs
		{
		public:
			ClosingEventArgs();
			bool IsCancelable;

			static int GetType();
		};
	}
}
