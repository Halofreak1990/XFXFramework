/*****************************************************************************
 *	CancelEventArgs.h														 *
 *																			 *
 *	System::ComponentModel::CancelEventArgs definition file 				 *
 *	Copyright (c) XFX Team. All rights reserved 							 *
 *****************************************************************************/
#ifndef _SYSTEM_COMPONENTMODEL_CANCELEVENTARGS_
#define _SYSTEM_COMPONENTMODEL_CANCELEVENTARGS_

#include <System/EventArgs.h>

namespace System
{
	namespace ComponentModel
	{
		/**
		 * Provides data for a cancelable event.
		 */
		class CancelEventArgs : public EventArgs
		{
		public:
			bool Cancel;

			CancelEventArgs();
			CancelEventArgs(const bool value);

			static const Type& GetType();
		};
	}
}

#endif //_SYSTEM_COMPONENTMODEL_CANCELEVENTARGS_
