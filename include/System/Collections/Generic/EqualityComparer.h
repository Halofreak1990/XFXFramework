#ifndef _SYSTEM_COLLECTIONS_GENERIC_EQUALITYCOMPARER_
#define _SYSTEM_COLLECTIONS_GENERIC_EQUALITYCOMPARER_

namespace System
{
	namespace Collections
	{
		namespace Generic
		{
			template <class T>
			class EqualityComparer : IEqualityComparer<T>
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
