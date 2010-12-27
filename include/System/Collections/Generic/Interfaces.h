/********************************************************
 *	Interfaces.h										*
 *														*
 *	XFX Generic Interfaces definition file				*
 *	Copyright © XFX Team. All Rights Reserved			*
 ********************************************************/
#ifndef _SYSTEM_COLLECTIONS_GENERIC_INTERFACES_
#define _SYSTEM_COLLECTIONS_GENERIC_INTERFACES_

#include <System/Types.h>

namespace System
{
	namespace Collections
	{
		namespace Generic
		{
			/// <summary>
			/// Defines methods to manipulate generic collections.
			/// </summary>
			template <class T>
			interface ICollection
			{
			public:
				virtual void Add(T item)=0;
				virtual void Clear()=0;
				virtual bool Contains(T item)=0;
				virtual void CopyTo(T array[], int arrayIndex)=0;
				virtual bool Remove(T item)=0;

				virtual int Count()=0;
				virtual bool IsReadOnly();
			};

			/// <summary>
			/// Defines a method that a type implements to compare two objects.
			/// </summary>
			template <class T>
			interface IComparer
			{
			public:
				virtual int Compare(T x, T y)=0;
			};

			/// <summary>
			/// Represents a generic collection of key/value pairs.
			/// </summary>
			template <class TKey, class TValue>
			interface IDictionary
			{
			public:
				virtual void Add(TKey key, TValue value)=0;
				virtual bool ContainsKey(TKey key)=0;
				virtual bool Remove(TKey key)=0;
				virtual bool TryGetValue(TKey key, out TValue value)=0;

				virtual ICollection<TKey> Keys()=0;
				virtual ICollection<TValue> Values()=0;
			};

			/// <summary>
			/// Supports a simple iteration over a generic collection.
			/// </summary>
			template <class T>
			interface IEnumerator
			{
			public:
				virtual T Current()=0;
			};

			/// <summary>
			/// Exposes the enumerator, which supports a simple iteration over a collection of a specified type.
			/// </summary>
			template <class T>
			interface IEnumerable
			{
			public:
				virtual IEnumerator<T> GetEnumerator()=0;
			};

			/// <summary>
			/// Defines methods to support the comparison of objects for equality.
			/// </summary>
			template <class T>
			interface IEqualityComparer
			{
			public:
				virtual bool Equals(T x, T y)=0;
				virtual int GetHashCode(T obj)=0;
			};

			/// <summary>
			/// Represents a collection of objects that can be individually accessed by index.
			/// </summary>
			template <class T>
			interface IList : public ICollection<T>
			{
			public:
				virtual int IndexOf(T item)=0;
				virtual void Insert(int index, T item)=0;
				virtual void RemoveAt(int index)=0;

				virtual T operator[](int index)=0;

				virtual ~IList();
			};
		}
	}
}

#endif //_SYSTEM_COLLECTIONS_GENERIC_INTERFACES_
