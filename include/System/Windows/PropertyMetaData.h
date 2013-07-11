/*****************************************************************************
 *	PropertyMetaData.h														 *
 *																			 *
 *	System::Windows::PropertyMetaData definition file						 *
 *	Copyright (c) XFX Team. All rights reserved								 *
 *****************************************************************************/
#ifndef _SYSTEM_WINDOWS_PROPERTYMETADATA_
#define _SYSTEM_WINDOWS_PROPERTYMETADATA_

namespace System
{
	namespace Windows
	{
		/**
		 * Defines certain behavior aspects of a dependency property, including conditions it was registered with.
		 */
		template <typename T>
		class PropertyMetaData
		{
		public:
			/**
			 * Gets the default value for the dependency property.
			 */
			T const DefaultValue;

			/**
			 * Creates a new instance of the PropertyMetaData class using a property default value.
			 *
			 * @param defaultValue
			 * A default value for the property where this System::Windows::PropertyMetadata is applied.
			 */
			PropertyMetaData(T defaultValue);
		};

		///////////////////////////////////////////////////////////////////////

		template <typename T>
		PropertyMetaData<T>::PropertyMetaData(T const defaultValue)
			: DefaultValue(defaultValue)
		{
		}
	}
}

#endif //_SYSTEM_WINDOWS_PROPERTYMETADATA_
