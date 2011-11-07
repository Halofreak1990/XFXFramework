#ifndef _SYSTEM_COLLECTIONS_GENERIC_COMPARER_
#define _SYSTEM_COLLECTIONS_GENERIC_COMPARER_

#include <System/Types.h>
#include "Interfaces.h"

namespace System
{
	namespace Collections
	{
		namespace Generic
		{
			// Provides a base class for implementations of the System::Collections::Generic::IComparer<T1> generic interface.
			template <class T>
			class Comparer : public IComparer<T>
			{
			private:
				static Comparer<T> defaultComparer;
				static Comparer<T> CreateComparer();

			protected:
				Comparer();

			public:
				static Comparer<T> Default();

				virtual int Compare(T x, T y)=0;
			};
		}
	}
}

#endif //_SYSTEM_COLLECTIONS_GENERIC_COMPARER_
