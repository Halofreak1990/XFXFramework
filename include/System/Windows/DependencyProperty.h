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
		 * Represents a dependency property that is registered with the dependency property system. Dependency properties provide support for value expressions, data binding, animation, and property change notification.
		 */
		template <typename T>
		class DependencyProperty
		{
		private:
			static Dictionary<Type, Dictionary<String, Object *> > _registeredProperties;

			DependencyProperty(const String& propertyName, const Type& type, T defaultValue)
				: DefaultValue(defaultValue), Name(propertyName)
			{
			}

		public:
			const T DefaultValue;
			const String Name;

			/**
			 * Registers a dependency property with the specified property name and owner type.
			 *
			 * @param propertyName
			 * The name of the dependency property to register.
			 *
			 * @param type
			 * The owner type that is registering the dependency property.
			 *
			 * @return
			 * A dependency property identifier that should be used to set the value of a public static readonly field in your class. The identifier is then used both by your own code and any third-party user code to reference the dependency property later, for operations such as setting its value programmatically, or attaching a System::Windows::Data::Binding in code.
			 */
			static DependencyProperty<T> Register(const String& propertyName, const Type& type);
			/**
			 * Registers a dependency property with the specified property name, owner type, and property metadata for the property.
			 *
			 * @param propertyName
			 * The name of the dependency property to register.
			 *
			 * @param type
			 * The owner type that is registering the dependency property.
			 *
			 * @param
			 * A PropertyMetadata instance. This can contain a System::Windows::PropertyChangedCallback implementation reference.
			 *
			 * @return
			 * A dependency property identifier that should be used to set the value of a public static readonly field in your class. The identifier is then used both by your own code and any third-party user code to reference the dependency property later, for operations such as setting its value programmatically, or attaching a System::Windows::Data::Binding in code.
			 */
			static DependencyProperty<T> Register(const String& propertyName, const Type& type, PropertyMetadata<T> const * propertyMetadata);
		};

		///////////////////////////////////////////////////////////////////////

		template <typename T>
		DependencyProperty<T> DependencyProperty<T>::Register(const String& propertyName, const Type& type)
		{
			return Register(propertyName, type, new PropertyMetadata<T>(null));
		}

		template <typename T>
		DependencyProperty<T> DependencyProperty<T>::Register(const String& propertyName, const Type& type, PropertyMetadata<T> const * propertyMetaData)
		{
			_registeredProperties.Add(type, Dictionary<String, T>());
			_registeredProperties[type].Add(propertyName, propertyMetaData->DefaultValue);

			return DependencyProperty<T>(propertyName, type, propertyMetaData->DefaultValue);
		}
	}
}

#endif //_SYSTEM_WINDOWS_DEPENDENCYPROPERTY_
