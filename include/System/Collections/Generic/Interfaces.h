/********************************************************
 *	Interfaces.h										*
 *														*
 *	XFX Generic Interfaces definition file				*
 *	Copyright (c) XFX Team. All Rights Reserved			*
 ********************************************************/
#ifndef _SYSTEM_COLLECTIONS_GENERIC_INTERFACES_
#define _SYSTEM_COLLECTIONS_GENERIC_INTERFACES_

#include <System/Object.h>
#include <System/Types.h>

namespace System
{
	namespace Collections
	{
		namespace Generic
		{
			// Defines methods to manipulate generic collections.
			template <class T>
			interface ICollection
			{
			public:
				virtual void Add(const T& item)=0;
				virtual void Clear()=0;
				virtual bool Contains(const T& item) const =0;
				virtual void CopyTo(T array[], const int arrayIndex) const =0;
				virtual bool Remove(const T& item)=0;

				virtual int Count() const =0;
				virtual bool IsReadOnly() const =0;

				virtual ~ICollection() { }
			};

			// Defines a method that a type implements to compare two objects.
			template <class T>
			interface IComparer
			{
			public:
				virtual int Compare(const T x, const T y) const =0;

				virtual ~IComparer() { }
			};

			// Represents a generic collection of key/value pairs.
			template <class TKey, class TValue>
			interface IDictionary
			{
			public:
				virtual void Add(const TKey& key, const TValue& value)=0;
				virtual bool ContainsKey(const TKey& key)const =0;
				virtual bool Remove(const TKey& key)=0;
				virtual bool TryGetValue(const TKey& key, out TValue value)const =0;

				virtual ICollection<TKey>* getKeys()const =0;
				virtual ICollection<TValue>* getValues()const =0;

				virtual ~IDictionary() { }
			};

			// Supports a simple iteration over a generic collection.
			template <class T>
			interface IEnumerator
			{
			public:
				virtual T& Current() const =0;
				virtual bool MoveNext()=0;
				virtual void Reset()=0;

				virtual ~IEnumerator() { }
			};

			// Exposes the enumerator, which supports a simple iteration over a collection of a specified type.
			template <class T>
			interface IEnumerable
			{
			public:
				virtual IEnumerator<T>* GetEnumerator()=0;

				virtual ~IEnumerable() { }
			};

			// Defines methods to support the comparison of objects for equality.
			template <class T>
			interface IEqualityComparer
			{
			public:
				virtual bool Equals(const T x, const T y) const =0;
				virtual int GetHashCode(const T obj) const =0;

				virtual ~IEqualityComparer() { }
			};

			// Represents a collection of objects that can be individually accessed by index.
			template <class T>
			interface IList : public ICollection<T>
			{
			public:
				virtual int IndexOf(const T& item) const =0;
				virtual void Insert(const int index, const T& item)=0;
				virtual void RemoveAt(const int index)=0;

				virtual T& operator[](const int index)=0;

				virtual ~IList() {}
			};
		}
	}
}

#endif //_SYSTEM_COLLECTIONS_GENERIC_INTERFACES_
