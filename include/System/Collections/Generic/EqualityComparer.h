/*****************************************************************************
 *	EqualityComparer.h 														 *
 *																			 *
 *	XFX System::Collections::Generic::EqualityComparer class definition file *
 *	Copyright (c) XFX Team. All rights reserved 							 *
 *****************************************************************************/
#ifndef _SYSTEM_COLLECTIONS_GENERIC_EQUALITYCOMPARER_
#define _SYSTEM_COLLECTIONS_GENERIC_EQUALITYCOMPARER_

#include <System/Object.h>
#include "Interfaces.h"

namespace System
{
	namespace Collections
	{
		namespace Generic
		{
			template <class T>
			class EqualityComparer : public IEqualityComparer<T>, public Object
			{
			private:
				static EqualityComparer<T> defaultComparer;

			public:
				static EqualityComparer<T> Default();

				bool Equals(const T x, const T y) const;
				int GetHashCode(const T obj) const;
				static const Type& GetType();
			};
		}
	}
}

#endif //_SYSTEM_COLLECTIONS_GENERIC_EQUALITYCOMPARER_
