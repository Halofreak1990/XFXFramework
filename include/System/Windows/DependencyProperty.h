/*****************************************************************************
 *	DependencyProperty.h													 *
 *																			 *
 *	System::Windows::DependencyProperty definition file						 *
 *	Copyright (c) XFX Team. All rights reserved								 *
 *****************************************************************************/
#ifndef _SYSTEM_WINDOWS_DEPENDENCYPROPERTY_
#define _SYSTEM_WINDOWS_DEPENDENCYPROPERTY_

#include <System/Collections/Generic/Dictionary.h>
#include "PropertyMetaData.h"

using namespace System::Collections::Generic;

namespace System
{
	namespace Windows
	{
		template <typename T>
		class DependencyProperty
		{
		private:
			static Dictionary<int, Dictionary<String&, Object *> > _registeredProperties;

		public:
			static DependencyProperty<T> Register(const String& propertyName, const int type);
			static DependencyProperty<T> Register(const String& propertyName, const int type, PropertyMetaData<T> const * propertyMetaData);
		};

		///////////////////////////////////////////////////////////////////////

		template <typename T>
		DependencyProperty<T> DependencyProperty<T>::Register(const String& propertyName, const int type)
		{
			Register(propertyName, type, new PropertyMetaData<T>(null));
		}

		template <typename T>
		DependencyProperty<T> DependencyProperty<T>::Register(const String& propertyName, const int type, PropertyMetaData<T> const * propertyMetaData)
		{
		}
	}
}

#endif //_SYSTEM_WINDOWS_DEPENDENCYPROPERTY_
