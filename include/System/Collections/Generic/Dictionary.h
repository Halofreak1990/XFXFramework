/********************************************************
 *	Dictionary.h										*
 *														*
 *	XFX Generic Dictionary class definition file		*
 *	Copyright © XFX Team. All Rights Reserved			*
 ********************************************************/
#ifndef _SYSTEM_COLLECTIONS_GENERIC_DICTIONARY_
#define _SYSTEM_COLLECTIONS_GENERIC_DICTIONARY_

#include "Interfaces.h"
#include "KeyValuePair.h"

namespace System
{
	namespace Collections
	{
		namespace Generic
		{
			/// <summary>
			/// Represents a collection of keys and values.
			/// </summary>
			template <class TKey, class TValue>
			class Dictionary : public IDictionary<TKey, TValue>, public ICollection<KeyValuePair<TKey, TValue> >
			{
			private:
				template <class UKey, class UValue>
				struct Entry
				{
					int hashCode;
					int next;
					UKey key;
					UValue value;
				};

			private:
				int buckets[];
				static const char* ComparerName;
				IEqualityComparer<TKey>* comparer;
				int count;
				Entry<TKey, TValue> entries[];
				int freeCount;
				int freeList;
				static const char* HashSizeName;
				static const char* KeyValuePairsName;
				int version;
				static const char* VersionName;

				void Add(KeyValuePair<TKey, TValue> keyValuePair);
				bool Contains(KeyValuePair<TKey, TValue> keyValuePair);
				void CopyTo(KeyValuePair<TKey, TValue> array[], int index);
				int FindEntry(TKey key);
				bool Remove(KeyValuePair<TKey, TValue> keyValuePair);
				void Initialize(int capacity);
				void Insert(TKey key, TValue value, bool add);
				void Resize();

			public:
				/// <summary>
				/// Represents the collection of keys in a Dictionary<,>. 
				/// </summary>
				template <class UKey, class UValue>
				class KeyCollection : public ICollection<UKey>, public IEnumerable<UKey>
				{
				private:
					Dictionary<TKey, TValue> *_dictionary;

				public:
					int Count();

					KeyCollection(Dictionary<TKey, TValue> dictionary);
					KeyCollection(const KeyCollection<UKey, UValue> &obj);

					void Add(UKey item);
					void Clear();
					bool Contains(UKey item);
					void CopyTo(UKey array[], int index);
					bool Remove(UKey item);
				};

				/// <summary>
				/// Represents the collection of values in a Dictionary<,>.
				/// </summary>
				template <class UKey, class UValue>
				class ValueCollection : public ICollection<UValue>, public IEnumerable<UValue>
				{
				private:
					Dictionary<TKey, TValue> *_dictionary;

				public:
					int Count();

					ValueCollection(Dictionary<TKey, TValue> dictionary);
					ValueCollection(const ValueCollection<UKey, UValue> &obj);

					void Add(UValue item);
					void Clear();
					bool Contains(UValue item);
					void CopyTo(UValue array[], int index);
					bool Remove(UValue item);
				};

			public:
				IEqualityComparer<TKey>* Comparer();
				int Count();
				KeyCollection<TKey, TValue> Keys();
				ValueCollection<TKey, TValue> Values();
				TValue operator[](TKey key);

				Dictionary();
				Dictionary(IDictionary<TKey, TValue> dictionary);
				Dictionary(int capacity);
				~Dictionary();

				void Add(TKey key, TValue value);
				void Clear();
				bool ContainsKey(TKey key);
				bool ContainsValue(TValue value);
				bool Remove(TKey key);
				bool TryGetValue(TKey key, out TValue value);
			};	
		}
	}
}

#endif //_SYSTEM_COLLECTIONS_GENERIC_DICTIONARY_
