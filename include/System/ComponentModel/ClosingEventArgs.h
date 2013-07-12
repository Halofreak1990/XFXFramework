/*****************************************************************************
 *	ClosingEventArgs.h  													 *
 *																			 *
 *	System::ComponentModel::ClosingEventArgs definition file				 *
 *	Copyright (c) XFX Team. All rights reserved 							 *
 *****************************************************************************/
#ifndef _SYSTEM_COMPONENTMODEL_CLOSINGEVENTARGS_
#define _SYSTEM_COMPONENTMODEL_CLOSINGEVENTARGS_

#include <System/ComponentModel/CancelEventArgs.h>

namespace System
{
	namespace ComponentModel
	{
		/**
		 *
		 */
		class ClosingEventArgs : public CancelEventArgs
		{
		public:
			ClosingEventArgs();
			bool IsCancelable;

			static const Type& GetType();
		};
	}
}

#endif //_SYSTEM_COMPONENTMODEL_CLOSINGEVENTARGS_
