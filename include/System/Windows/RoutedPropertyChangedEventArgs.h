/*****************************************************************************
 *	RoutedPropertyChangedEventArgs.h										 *
 *																			 *
 *	System::Windows::RoutedPropertyChangedEventArgs definition file 		 *
 *	Copyright (c) XFX Team. All rights reserved								 *
 *****************************************************************************/
#ifndef _SYSTEM_WINDOWS_ROUTEDPROPERTYCHANGEDEVENTARGS_
#define _SYSTEM_WINDOWS_ROUTEDPROPERTYCHANGEDEVENTARGS_

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

		template <typename T>
		class RoutedPropertyChangedEventArgs<T *> : public RoutedEventArgs
		{
		public:
			T const * const OldValue;
			T const * const NewValue;

			RoutedPropertyChangedEventArgs(T const * const oldValue, T const * const newValue)
				: OldValue(oldValue), NewValue(newValue)
			{
			}
		};
	}
}

#endif //_SYSTEM_WINDOWS_ROUTEDPROPERTYCHANGEDEVENTARGS_
