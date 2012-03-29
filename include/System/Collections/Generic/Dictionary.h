/********************************************************
 *	Dictionary.h										*
 *														*
 *	XFX Generic Dictionary class definition file		*
 *	Copyright © XFX Team. All Rights Reserved			*
 ********************************************************/
#ifndef _SYSTEM_COLLECTIONS_GENERIC_DICTIONARY_
#define _SYSTEM_COLLECTIONS_GENERIC_DICTIONARY_

#include <System/Array.h>
#include <System/String.h>
#include "EqualityComparer.h"
#include "Interfaces.h"
#include "KeyValuePair.h"

#include <sassert.h>

namespace System
{
	namespace Collections
	{
		namespace Generic
		{
			// Represents a collection of keys and values.
			template <class TKey, class TValue>
			class Dictionary : public ICollection<KeyValuePair<TKey, TValue> >, virtual Object //public IDictionary<TKey, TValue>, 
			{
			private:
				template <class UKey, class UValue>
				struct Entry
				{
					int hashCode;
					int next;
					UKey& key;
					UValue& value;
				};

				static const int defaultCapacity = 4;
				int buckets[];
				static const char* ComparerName;
				IEqualityComparer<TKey>* comparer;
				int count;
				Entry<TKey, TValue>* entries;
				int _actualSize;
				static const char* HashSizeName;
				static const char* KeyValuePairsName;
				int version;
				static const char* VersionName;

				void Add(const KeyValuePair<TKey, TValue>& keyValuePair);
				bool Contains(const KeyValuePair<TKey, TValue>& keyValuePair) const;
				void CopyTo(KeyValuePair<TKey, TValue> array[], const int index) const;
				void EnsureCapacity(int capacity);
				int FindEntry(TKey key) const;
				bool Remove(const KeyValuePair<TKey, TValue>& keyValuePair);
				void Initialize(const int capacity);
				void Insert(const TKey& key, const TValue& value, const bool add);
				void Resize();

			public:
				// Represents the collection of keys in a Dictionary<,>. 
				template <class UKey, class UValue>
				class KeyCollection : public ICollection<UKey>
				{
				private:
					Dictionary<UKey, UValue>* _dictionary;

				public:
					int Count() const;

					KeyCollection(const Dictionary<UKey, UValue>* dictionary);
					KeyCollection(const KeyCollection<UKey, UValue> &obj);
					~KeyCollection();

					void Add(const UKey& item);
					void Clear();
					bool Contains(const UKey& item) const;
					void CopyTo(UKey array[], const int arrayIndex) const;
					bool Remove(const UKey& item);
				};

				// Represents the collection of values in a Dictionary<,>.
				template <class UKey, class UValue>
				class ValueCollection : public ICollection<UValue>
				{
				private:
					Dictionary<UKey, UValue> *_dictionary;

				public:
					int Count() const;

					ValueCollection(const Dictionary<UKey, UValue>* dictionary);
					ValueCollection(const ValueCollection<UKey, UValue> &obj);

					void Add(const UValue& item);
					void Clear();
					bool Contains(const UValue& item) const;
					void CopyTo(UValue array[], const int arrayIndex) const;
					bool Remove(const UValue& item);
				};

			public:
				IEqualityComparer<TKey>* Comparer() const;

				int Count() const;
				bool IsReadOnly() const;
				KeyCollection<TKey, TValue> Keys() const;
				ValueCollection<TKey, TValue> Values() const;
				TValue& operator[](const TKey& key);

				Dictionary();
				Dictionary(const IDictionary<TKey, TValue>* dictionary);
				Dictionary(const int capacity);
				virtual ~Dictionary();

				void Add(const TKey& key, const TValue& value);
				void Clear();
				bool ContainsKey(const TKey& key) const;
				bool ContainsValue(const TValue& value) const;

				bool Remove(const TKey& key);
				bool TryGetValue(const TKey& key, out TValue value) const;
			};

			//////////////////////////////////////////////////////////////////////

			template <class TKey, class TValue>
			int Dictionary<TKey, TValue>::Count() const
			{
				return count;
			}

			template <class TKey, class TValue>
			bool Dictionary<TKey, TValue>::IsReadOnly() const
			{
				return false;
			}

			template <class TKey, class TValue>
			Dictionary<TKey, TValue>::Dictionary()
			{
				entries = new Entry<TKey, TValue>[defaultCapacity];
				count = 0;
			}

			template <class TKey, class TValue>
			Dictionary<TKey, TValue>::Dictionary(const IDictionary<TKey, TValue>* dictionary)
			{
				int itemCount = dictionary->Keys()->Count();

				entries = new Entry<TKey, TValue>[itemCount];

				for (int i = 0; i < itemCount; i++)
				{
					// TODO: get items
				}
			}

			template <class TKey, class TValue>
			Dictionary<TKey, TValue>::Dictionary(const int capacity)
			{
				entries = new Entry<TKey, TValue>[capacity];
				count = 0;
			}

			template <class TKey, class TValue>
			Dictionary<TKey, TValue>::~Dictionary()
			{
				delete[] entries;
			}

			template <class TKey, class TValue>
			void Dictionary<TKey, TValue>::Add(const TKey& key, const TValue& value)
			{
				Insert(key, value, true);
			}

			template <class TKey, class TValue>
			void Dictionary<TKey, TValue>::Add(const KeyValuePair<TKey, TValue>& keyValuePair)
			{
				Insert(keyValuePair.Key, keyValuePair.Value, true);
			}

			template <class TKey, class TValue>
			bool Dictionary<TKey, TValue>::Contains(const KeyValuePair<TKey, TValue>& keyValuePair) const
			{
				for (int i = 0; i < count; i++)
				{
					if (entries[i].key == keyValuePair.Key && entries[i].value == keyValuePair.Value)
						return true;
				}
				return false;
			}

			template <class TKey, class TValue>
			void Dictionary<TKey, TValue>::CopyTo(KeyValuePair<TKey, TValue> array[], const int index) const
			{
				return;
			}

			template <class TKey, class TValue>
			void Dictionary<TKey, TValue>::EnsureCapacity(int capacity)
			{
				if (_actualSize < capacity)
				{
					int num = (_actualSize == 0) ? defaultCapacity : _actualSize * 2;
					if (num > 0x7fefffff)
					{
						num = 0x7fefffff;
					}
					if (num < capacity)
					{
						num = capacity;
					}
					
					if (num != _actualSize)
					{
						if (num > 0)
						{
							Entry<TKey, TValue>* destinationArray = new Entry<TKey, TValue>[num];
							if (count > 0)
							{
								Array::Copy(entries, 0, destinationArray, 0, count);
							}
							delete[] entries;
							entries = destinationArray;
						}
						else
						{
							delete[] entries;
							entries = new Entry<TKey, TValue>[0];
							
						}
						_actualSize = num;
					}
				}
			}

			template <class TKey, class TValue>
			int Dictionary<TKey, TValue>::FindEntry(TKey key) const
			{
				for (int i = 0; i < count; i++)
				{
					if (entries[i].key == key)
						return i;
				}
				return -1;
			}

			template <class TKey, class TValue>
			void Dictionary<TKey, TValue>::Insert(const TKey& key, const TValue& value, const bool add)
			{
				int index = FindEntry(key);

				if (index >=0)
				{
					sassert(add, "Attempting to add duplicate Key/Value pair to dictionary.");

					entries[index].value = value;
					return;
				}

				entries[count].key = key;
				entries[count].value = value;
				count++;
			}

			template <class TKey, class TValue>
			bool Dictionary<TKey, TValue>::Remove(const KeyValuePair<TKey, TValue>& keyValuePair)
			{
				return false;
			}

			template <class TKey, class TValue>
			template <class UKey, class UValue>
			int Dictionary<TKey, TValue>::KeyCollection<UKey, UValue>::Count() const
			{
				return _dictionary->Count();
			}

			template <class TKey, class TValue>
			template <class UKey, class UValue>
			Dictionary<TKey, TValue>::KeyCollection<UKey, UValue>::KeyCollection(const Dictionary<UKey, UValue>* dictionary)
			{
				_dictionary = dictionary;
			}

			template <class TKey, class TValue>
			template <class UKey, class UValue>
			Dictionary<TKey, TValue>::KeyCollection<UKey, UValue>::KeyCollection(const KeyCollection<UKey, UValue> &obj)
			{
				_dictionary = obj._dictionary;
			}

			template <class TKey, class TValue>
			template <class UKey, class UValue>
			Dictionary<TKey, TValue>::KeyCollection<UKey, UValue>::~KeyCollection()
			{
				delete _dictionary;
			}

			template <class TKey, class TValue>
			template <class UKey, class UValue>
			void Dictionary<TKey, TValue>::KeyCollection<UKey, UValue>::Add(const UKey& item)
			{
				sassert(false, "Adding keys directly to the Dictionary::Keycollection is not supported.");

				return;
			}

			template <class TKey, class TValue>
			template <class UKey, class UValue>
			void Dictionary<TKey, TValue>::KeyCollection<UKey, UValue>::Clear()
			{
				sassert(false, "Directly clearing the Dictionary::KeyCollection is not supported.");

				return;
			}

			template <class TKey, class TValue>
			template <class UKey, class UValue>
			bool Dictionary<TKey, TValue>::KeyCollection<UKey, UValue>::Contains(const UKey& item) const
			{
				return _dictionary.ContainsKey(item);
			}

			template <class TKey, class TValue>
			template <class UKey, class UValue>
			void Dictionary<TKey, TValue>::KeyCollection<UKey, UValue>::CopyTo(UKey array[], const int arrayIndex) const
			{
				sassert(array != NULL, String::Format("array; %s", FrameworkResources::ArgumentNull_Generic));

				sassert(arrayIndex >=0, String::Format("arrayIndex; %s", FrameworkResources::ArgumentOutOfRange_NeedNonNegNum));

				// TODO: implement
			}

			template <class TKey, class TValue>
			template <class UKey, class UValue>
			bool Dictionary<TKey, TValue>::KeyCollection<UKey, UValue>::Remove(const UKey& item)
			{
				sassert(false, "Removing keys directly from the Dictionary::KeyCollection is not supported.");

				return false;
			}

			template <class TKey, class TValue>
			template <class UKey, class UValue>
			Dictionary<TKey, TValue>::ValueCollection<UKey, UValue>::ValueCollection(const Dictionary<UKey, UValue>* dictionary)
			{
				_dictionary = dictionary;
			}

			template <class TKey, class TValue>
			void Dictionary<TKey, TValue>::Clear()
			{
				// TODO: implement
			}

			template <class TKey, class TValue>
			bool Dictionary<TKey, TValue>::Remove(const TKey& key)
			{
				int index = FindEntry(key);
				if (index >= 0)
				{
					// TODO: implement
				}
				return false;
			}

			template <class TKey, class TValue>
			bool Dictionary<TKey, TValue>::TryGetValue(const TKey& key, out TValue value) const
			{
				int index = FindEntry(key);
				if(index >= 0)
				{
					value = entries[index].value;
					return true;
				}
				value = TValue();
				return false;
			}

			template <class TKey, class TValue>
			TValue& Dictionary<TKey, TValue>::operator [](const TKey& key)
			{
				int index = FindEntry(key);

				sassert(index >= 0, "");

				return entries[index];
			}
		}
	}
}

#endif //_SYSTEM_COLLECTIONS_GENERIC_DICTIONARY_
