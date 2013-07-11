/********************************************************
 *	Dictionary.h										*
 *														*
 *	XFX Generic Dictionary class definition file		*
 *	Copyright (c) XFX Team. All Rights Reserved			*
 ********************************************************/
#ifndef _SYSTEM_COLLECTIONS_GENERIC_DICTIONARY_
#define _SYSTEM_COLLECTIONS_GENERIC_DICTIONARY_

#include <System/Array.h>
#include <System/String.h>
#include "EqualityComparer.h"
#include "Interfaces.h"
#include "KeyValuePair.h"
#include "List.h"

#include <sassert.h>

namespace System
{
	namespace Collections
	{
		namespace Generic
		{
			// Represents a collection of keys and values.
			template <class TKey, class TValue>
			class Dictionary : public IDictionary<TKey, TValue>, public ICollection<KeyValuePair<TKey, TValue> >, public IEnumerable<KeyValuePair<TKey, TValue> >, public Object
			{
			private:
				template <class UKey, class UValue>
				struct Entry
				{
					UKey Key;
					UValue Value;
					Entry* next;

					Entry(UKey key, UValue value)
						: Key(key), Value(value), next(NULL)
					{
					}
				};
				static const int defaultCapacity = 4;
				
				IEqualityComparer<TKey>* comparer;
				int _count;
				Entry<TKey, TValue>** _internalStorage;
				int _size;
				int _version;

				void Add(const KeyValuePair<TKey, TValue>& keyValuePair);
				bool Contains(const KeyValuePair<TKey, TValue>& keyValuePair) const;
				void CopyTo(KeyValuePair<TKey, TValue> array[], const int index) const;
				void EnsureCapacity(int capacity);
				Entry<TKey, TValue>* FindEntry(const TKey& key) const;
				bool Remove(const KeyValuePair<TKey, TValue>& keyValuePair);
				void Initialize(const int capacity);
				//void Insert(const TKey& key, const TValue& value, const bool add);
				void Resize();

			public:
				// Represents the collection of keys in a Dictionary<,>. 
				template <class UKey, class UValue>
				class KeyCollection : public ICollection<UKey>
				{
				private:
					Dictionary<UKey, UValue> const * const _dictionary;

				public:
					int Count() const;
					bool IsReadOnly() const { return true; }

					KeyCollection(Dictionary<UKey, UValue> const * const dictionary);

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
					Dictionary<UKey, UValue> const * const _dictionary;

				public:
					int Count() const;
					bool IsReadOnly() const { return true; }

					ValueCollection(Dictionary<UKey, UValue> const * const dictionary);

					void Add(const UValue& item);
					void Clear();
					bool Contains(const UValue& item) const;
					void CopyTo(UValue array[], const int arrayIndex) const;
					bool Remove(const UValue& item);
				};

			public:
				IEqualityComparer<TKey>* getComparer() const;

				int Count() const;
				bool IsReadOnly() const;
				KeyCollection<TKey, TValue>* getKeys() const;
				ValueCollection<TKey, TValue>* getValues() const;
				TValue& operator[](const TKey& key);

				Dictionary();
				Dictionary(const IDictionary<TKey, TValue>* dictionary);
				Dictionary(const int capacity);
				virtual ~Dictionary();

				void Add(const TKey& key, const TValue& value);
				void Clear();
				bool ContainsKey(const TKey& key) const;
				bool ContainsValue(const TValue& value) const;
				IEnumerator<KeyValuePair<TKey, TValue> >* GetEnumerator();
				static int GetType();
				bool Remove(const TKey& key);
				bool TryGetValue(const TKey& key, out TValue value) const;

			private:
				struct DictionaryEnumerator : IEnumerator<KeyValuePair<TKey, TValue> >
				{
				private:
					Dictionary<TKey, TValue>* _parentDictionary;
					Entry<TKey, TValue>* currentEntry;

				public:
					DictionaryEnumerator(Dictionary<TKey, TValue>* _parentDictionary);

					KeyValuePair<TKey, TValue>& Current() const;
					bool MoveNext();
					void Reset();
				};
			};

			///////////////////////////////////////////////////////////////////

			template <class TKey, class TValue>
			int Dictionary<TKey, TValue>::Count() const
			{
				return _count;
			}

			template <class TKey, class TValue>
			bool Dictionary<TKey, TValue>::IsReadOnly() const
			{
				return false;
			}

			template <class TKey, class TValue>
			Dictionary<TKey, TValue>::KeyCollection<TKey, TValue>* Dictionary<TKey, TValue>::getKeys() const
			{
				return new KeyCollection<TKey, TValue>(this);
			}

			template <class TKey, class TValue>
			Dictionary<TKey, TValue>::ValueCollection<TKey, TValue>* Dictionary<TKey, TValue>::getValues() const
			{
				return new ValueCollection<TKey, TValue>(this);
			}

			template <class TKey, class TValue>
			Dictionary<TKey, TValue>::Dictionary()
				: _count(0), _size(defaultCapacity), _version(0)
			{
				_internalStorage = new Entry<TKey, TValue>*[defaultCapacity];

				for (int i = 0; i < _size; i++)
					_internalStorage[i] = NULL;
			}

			template <class TKey, class TValue>
			Dictionary<TKey, TValue>::Dictionary(const IDictionary<TKey, TValue>* dictionary)
				: _count(0), _size(dictionary->Keys()->Count()), _version(0)
			{
				_internalStorage = new Entry<TKey, TValue>*[_size];

				IEnumerator<KeyValuePair<TKey, TValue> >* enumerator = dictionary->GetEnumerator();
				enumerator->Reset();

				while (enumerator->MoveNext())
				{
					this->Add(enumerator->Current());
				}
			}

			template <class TKey, class TValue>
			Dictionary<TKey, TValue>::Dictionary(const int capacity)
				: _count(0), _size(capacity), _version(0)
			{
				_internalStorage = new Entry<TKey, TValue>*[capacity];

				for (int i = 0; i < _size; i++)
					_internalStorage[i] = NULL;
			}

			template <class TKey, class TValue>
			Dictionary<TKey, TValue>::~Dictionary()
			{
				for (int i = 0; i < _size; i++)
				{
					if (_internalStorage[i] != NULL)
					{
						Entry<TKey, TValue>* prevEntry = NULL;
						Entry<TKey, TValue>* entry = _internalStorage[i];
						while (entry != NULL)
						{
							prevEntry = entry;
							entry = entry->next;
							delete prevEntry;
						}
					}
				}

				delete[] _internalStorage;
			}

			template <class TKey, class TValue>
			void Dictionary<TKey, TValue>::Add(const TKey& key, const TValue& value)
			{
				int hash = key.GetHashCode() % _size;

				if (_internalStorage[hash] == NULL)
					_internalStorage[hash] = new Entry<TKey, TValue>(TKey(key), TValue(value));
				else
				{
					Entry<TKey, TValue>* entry = _internalStorage[hash];
					while (entry->next != NULL)
						entry = entry->next;

					if (entry->Key == key)
						return; // throw error
					else
						entry->next = new Entry<TKey, TValue>(TKey(key), TValue(value));
				}

				_count++;
			}

			template <class TKey, class TValue>
			void Dictionary<TKey, TValue>::Add(const KeyValuePair<TKey, TValue>& keyValuePair)
			{
				int hash = keyValuePair.Key.GetHashCode() % _size;

				if (_internalStorage[hash] == NULL)
					_internalStorage[hash] = new Entry<TKey, TValue>(keyValuePair.Key, keyValuePair.Value);
				else
				{
					Entry<TKey, TValue>* entry = _internalStorage[hash];
					while (entry->next != NULL)
						entry = entry->next;

					if (entry->Key == keyValuePair.Key)
						return; // throw error
					else
						entry->next = new Entry<TKey, TValue>(keyValuePair.Key, keyValuePair.Value);
				}

				_count++;
			}

			template <class TKey, class TValue>
			bool Dictionary<TKey, TValue>::Contains(const KeyValuePair<TKey, TValue>& keyValuePair) const
			{
				// TODO: implement
				return false;
			}

			template <class TKey, class TValue>
			bool Dictionary<TKey, TValue>::ContainsKey(const TKey& key) const
			{
				int hash = key.GetHashCode() % _size;

				if (_internalStorage[hash] != NULL)
				{
					Entry<TKey, TValue>* entry = _internalStorage[hash];
					while (entry->next != NULL)
						entry = entry->next;

					return (entry->Key == key);
				}
				return false;
			}

			template <class TKey, class TValue>
			bool Dictionary<TKey, TValue>::ContainsValue(const TValue& value) const
			{
				// TODO: implement
				return false;
			}

			template <class TKey, class TValue>
			void Dictionary<TKey, TValue>::CopyTo(KeyValuePair<TKey, TValue> array[], const int arrayIndex) const
			{
				sassert(false, "Function not implemented.");
			}

			template <class TKey, class TValue>
			void Dictionary<TKey, TValue>::EnsureCapacity(int capacity)
			{
				/*if (_actualSize < capacity)
				{
					int num = (_size == 0) ? defaultCapacity : _size * 2;
					if (num > 0x7fefffff)
					{
						num = 0x7fefffff;
					}
					if (num < capacity)
					{
						num = capacity;
					}
					
					if (num != _size)
					{
						if (num > 0)
						{
							Entry<TKey, TValue>** destinationArray = new Entry<TKey, TValue>*[num];
							if (_count > 0)
							{
								for(int i = 0; i < _count; i++)
								{
									destinationArray[i] = entries[i];
								}
							}
							delete[] entries;
							entries = destinationArray;
						}
						else
						{
							delete[] entries;
							entries = new Entry<TKey, TValue>*[0];
							
						}
						_size = num;
					}
				}*/
			}

			template <class TKey, class TValue>
			Dictionary<TKey, TValue>::Entry<TKey, TValue>* Dictionary<TKey, TValue>::FindEntry(const TKey& key) const
			{
				// TODO: implement
				/*for (Entry<TKey, TValue>* e = *entries; e != NULL; e = e->next)
				{
					if (e->key == key)
						return e;
				}*/
				return NULL;
			}

			template <class TKey, class TValue>
			int Dictionary<TKey, TValue>::GetType()
			{
				// TODO: implement
			}

			//template <class TKey, class TValue>
			//void Dictionary<TKey, TValue>::Insert(const TKey& key, const TValue& value, const bool add)
			//{
			//	Entry<TKey, TValue>* e = FindEntry(key);

			//	if (e)
			//	{
			//		sassert(!add, "Attempting to add duplicate Key/Value pair to dictionary.");

			//		e->value = value;
			//		return;
			//	}

			//	while(e->next != NULL)
			//	{
			//		e = e->next;
			//	}

			//	// e now points to the last element in the list
			//	e->next = new Entry<TKey, TValue>();
			//	e = e->next;
			//	e->key = key;
			//	e->value = value;
			//	e->next = NULL;

			//	_count++;
			//}

			template <class TKey, class TValue>
			bool Dictionary<TKey, TValue>::Remove(const KeyValuePair<TKey, TValue>& keyValuePair)
			{
				Entry<TKey, TValue>* e = FindEntry(keyValuePair.Key);

				if (e)
				{
					// TODO: implement
					return true;
				}

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
			Dictionary<TKey, TValue>::KeyCollection<UKey, UValue>::KeyCollection(Dictionary<UKey, UValue> const * const dictionary)
				: _dictionary(dictionary)
			{
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
				return _dictionary->ContainsKey(item);
			}

			template <class TKey, class TValue>
			template <class UKey, class UValue>
			void Dictionary<TKey, TValue>::KeyCollection<UKey, UValue>::CopyTo(UKey array[], const int arrayIndex) const
			{
				sassert(array != NULL, String::Format("array; %s", FrameworkResources::ArgumentNull_Generic));

				sassert(arrayIndex >= 0, String::Format("arrayIndex; %s", FrameworkResources::ArgumentOutOfRange_NeedNonNegNum));

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
			Dictionary<TKey, TValue>::ValueCollection<UKey, UValue>::ValueCollection(Dictionary<UKey, UValue> const * const dictionary)
				: _dictionary(dictionary)
			{
			}

			template <class TKey, class TValue>
			template <class UKey, class UValue>
			int Dictionary<TKey, TValue>::ValueCollection<UKey, UValue>::Count() const
			{
				return _dictionary->Count();
			}

			template <class TKey, class TValue>
			template <class UKey, class UValue>
			void Dictionary<TKey, TValue>::ValueCollection<UKey, UValue>::Add(const UValue& item)
			{
				sassert(false, "Adding values directly to the Dictionary::Valuecollection is not supported.");

				return;
			}

			template <class TKey, class TValue>
			template <class UKey, class UValue>
			void Dictionary<TKey, TValue>::ValueCollection<UKey, UValue>::Clear()
			{
				sassert(false, "Directly clearing the Dictionary::ValueCollection is not supported.");

				return;
			}

			template <class TKey, class TValue>
			template <class UKey, class UValue>
			bool Dictionary<TKey, TValue>::ValueCollection<UKey, UValue>::Contains(const UValue& item) const
			{
				return _dictionary->ContainsValue(item);
			}

			template <class TKey, class TValue>
			template <class UKey, class UValue>
			void Dictionary<TKey, TValue>::ValueCollection<UKey, UValue>::CopyTo(UValue array[], const int arrayIndex) const
			{
				sassert(array != NULL, String::Format("array; %s", FrameworkResources::ArgumentNull_Generic));

				sassert(arrayIndex >= 0, String::Format("arrayIndex; %s", FrameworkResources::ArgumentOutOfRange_NeedNonNegNum));

				// TODO: implement
			}

			template <class TKey, class TValue>
			template <class UKey, class UValue>
			bool Dictionary<TKey, TValue>::ValueCollection<UKey, UValue>::Remove(const UValue& item)
			{
				sassert(false, "Removing values directly from the Dictionary::ValueCollection is not supported.");

				return false;
			}

			template <class TKey, class TValue>
			void Dictionary<TKey, TValue>::Clear()
			{
				for (int i = 0; i < _size; i++)
				{
					if (_internalStorage[i] != NULL)
					{
						Entry<TKey, TValue>* prevEntry = NULL;
						Entry<TKey, TValue>* entry = _internalStorage[i];
						while (entry != NULL)
						{
							prevEntry = entry;
							entry = entry->next;
							delete prevEntry;
						}
					}
				}

				_count = 0;
			}

			template <class TKey, class TValue>
			IEnumerator<KeyValuePair<TKey, TValue> >* Dictionary<TKey, TValue>::GetEnumerator()
			{
				return new DictionaryEnumerator(this);
			}

			template <class TKey, class TValue>
			bool Dictionary<TKey, TValue>::Remove(const TKey& key)
			{
				int hash = key.GetHashCode() % _size;

				if (_internalStorage[hash] != NULL)
				{
					Entry<TKey, TValue>* prevEntry = NULL;
					Entry<TKey, TValue>* entry = _internalStorage[hash];
					while (entry->next != NULL && entry->Key != key)
					{
						prevEntry = entry;
						entry = entry->next;
					}
					if (entry->Key == key)
					{
						if (prevEntry == NULL)
						{
							Entry<TKey, TValue>* nextEntry = entry->next;
							delete entry;
							_internalStorage[hash] = nextEntry;
						}
						else
						{
							Entry<TKey, TValue>* next = entry->next;
							delete entry;
							prevEntry->next = next;
						}
						return true;
					}
				}

				return false;
			}

			template <class TKey, class TValue>
			bool Dictionary<TKey, TValue>::TryGetValue(const TKey& key, out TValue value) const
			{
				int hash = key.GetHashCode() % _size;

				if (_internalStorage[hash] != NULL)
				{
					// TODO: implement
					return true;
				}
				return false;
			}

			template <class TKey, class TValue>
			Dictionary<TKey, TValue>::DictionaryEnumerator::DictionaryEnumerator(Dictionary<TKey,TValue> *_parentDictionary)
				: _parentDictionary(_parentDictionary)
			{
			}

			template <class TKey, class TValue>
			KeyValuePair<TKey, TValue>& Dictionary<TKey, TValue>::DictionaryEnumerator::Current() const
			{
				KeyValuePair<TKey, TValue>* kv = new KeyValuePair<TKey,TValue>(currentEntry->Key, currentEntry->Value);
				return *kv;
			}

			template <class TKey, class TValue>
			bool Dictionary<TKey, TValue>::DictionaryEnumerator::MoveNext()
			{
				// TODO: implement
				/*bool canMove = ((Entry<TKey, TValue>*)*(_parentDictionary->entries))->next != null;
				if (currentEntry == NULL)
					currentEntry = *(_parentDictionary->entries);
				else
					currentEntry = currentEntry->next;*/
			}

			template <class TKey, class TValue>
			void Dictionary<TKey, TValue>::DictionaryEnumerator::Reset()
			{
				currentEntry = NULL;
			}

			template <class TKey, class TValue>
			TValue& Dictionary<TKey, TValue>::operator [](const TKey& key)
			{
				int hash = key.GetHashCode() % _size;

				if (_internalStorage[hash] == NULL)
				{
					sassert(false, ""); // KeyNotFoundException
				}
				else
				{
					Entry<TKey, TValue>* entry = _internalStorage[hash];
					while (entry != NULL && entry->Key != key)
						entry = entry->next;
					if (entry == NULL)
						sassert(false, ""); // KeyNotFoundException
					else
						return entry->Value;
				}
			}
		}
	}
}

#endif //_SYSTEM_COLLECTIONS_GENERIC_DICTIONARY_
