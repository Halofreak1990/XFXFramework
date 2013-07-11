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
		/**
		 * 
		 */
		template <typename T>
		class DependencyProperty
		{
		private:
			static Dictionary<int, Dictionary<String&, Object *> > _registeredProperties;

			DependencyProperty(const String& propertyName, const int type, T defaultValue)
				: DefaultValue(defaultValue), Name(propertyName)
			{
			}

		public:
			const T DefaultValue;
			const String Name;

			static DependencyProperty<T> Register(const String& propertyName, const int type);
			static DependencyProperty<T> Register(const String& propertyName, const int type, PropertyMetaData<T> const * propertyMetaData);
		};

		///////////////////////////////////////////////////////////////////////

		template <typename T>
		DependencyProperty<T> DependencyProperty<T>::Register(const String& propertyName, const int type)
		{
			Derived_from<T, Object *>():

			return Register(propertyName, type, new PropertyMetaData<T>(null));
		}

		template <typename T>
		DependencyProperty<T> DependencyProperty<T>::Register(const String& propertyName, const int type, PropertyMetaData<T> const * propertyMetaData)
		{
			Derived_from<T, Object *>():

			_registeredProperties.Add(type, Dictionary<String&, Object *>());
			_registeredProperties[type].Add(propertyName, propertyMetaData->DefaultValue);

			return DependencyProperty<T>(propertyName, type, propertyMetaData->DefaultValue);
		}
	}
}

#endif //_SYSTEM_WINDOWS_DEPENDENCYPROPERTY_
