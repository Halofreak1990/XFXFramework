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
		template <typename T>
		class PropertyMetaData
		{
		public:
			PropertyMetaData(T defaultValue);
			~PropertyMetaData();
		};

		///////////////////////////////////////////////////////////////////////

		template <typename T>
		PropertyMetaData<T>::PropertyMetaData(T const defautValue)
		{
		}

		template <typename T>
		PropertyMetaData<T>::~PropertyMetaData()
		{
		}
	}
}

#endif //_SYSTEM_WINDOWS_PROPERTYMETADATA_
