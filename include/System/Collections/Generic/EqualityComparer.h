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
			class EqualityComparer : public IEqualityComparer<T>, virtual Object
			{
			private:
				static EqualityComparer<T> defaultComparer;

			public:
				static EqualityComparer<T> Default();

				bool Equals(T x, T y);
				int GetHashCode(T obj);
			};
		}
	}
}

#endif //_SYSTEM_COLLECTIONS_GENERIC_EQUALITYCOMPARER_
