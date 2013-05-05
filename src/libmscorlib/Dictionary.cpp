// Copyright (C) 2010-2012, XFX Team
// All rights reserved.
// 
// Redistribution and use in source and binary forms, with or without 
// modification, are permitted provided that the following conditions are met:
// 
//     * Redistributions of source code must retain the above copyright 
//       notice, this list of conditions and the following disclaimer.
//     * Redistributions in binary form must reproduce the above copyright 
//       notice, this list of conditions and the following disclaimer in the 
//       documentation and/or other materials provided with the distribution.
//     * Neither the name of the copyright holder nor the names of any 
//       contributors may be used to endorse or promote products derived from 
//       this software without specific prior written permission.
// 
// THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS" 
// AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE 
// IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE 
// ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT OWNER OR CONTRIBUTORS BE 
// LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR 
// CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF 
// SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS 
// INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN 
// CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) 
// ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE 
// POSSIBILITY OF SUCH DAMAGE.

#include <System/Array.h>
#include <System/Collections/Generic/Dictionary.h>
#include <System/Collections/Generic/EqualityComparer.h>
#include "HashHelpers.h"

#if DEBUG
#include <stdio.h>
#endif

namespace System
{
	namespace Collections
	{
		namespace Generic
		{
			template <class TKey, class TValue>
			const char* Dictionary<TKey, TValue>::ComparerName = "Comparer";
			template <class TKey, class TValue>
			const char* Dictionary<TKey, TValue>::HashSizeName = "HashSize";
			template <class TKey, class TValue>
			const char* Dictionary<TKey, TValue>::KeyValuePairsName = "KeyValuePairs";
			template <class TKey, class TValue>
			const char* Dictionary<TKey, TValue>::VersionName = "Version";

			template <class TKey, class TValue>
			Dictionary<TKey, TValue>::Dictionary(IDictionary<TKey,TValue>* dictionary)
			{
				/*foreach (KeyValuePair<TKey, TValue> pair in dictionary)
				{
					Add(pair.Key, pair.Value);
				}*/
			}

			template <class TKey, class TValue>
			Dictionary<TKey, TValue>::~Dictionary()
			{
				delete[] buckets;
				delete[] entries;
			}

			template <class TKey, class TValue>
			IEqualityComparer<TKey>* Dictionary<TKey, TValue>::Comparer()
			{
				return comparer;
			}

			template <class TKey, class TValue>
			void Dictionary<TKey, TValue>::Add(TKey key, TValue value)
			{
				Insert(key, value, true);
			}

			template <class TKey, class TValue>
			void Dictionary<TKey, TValue>::Add(KeyValuePair<TKey, TValue> keyValuePair)
			{
				Add(keyValuePair.Key(), keyValuePair.Value());
			}

			template <class TKey, class TValue>
			void Dictionary<TKey, TValue>::Clear()
			{
				if(count > 0)
				{
					for(int i = 0; i < Array::Length(buckets); i++)
					{
						buckets[i] = -1;
					}
					Array::Clear(entries, 0, count);
					freeList = -1;
					count = 0;
					freeCount = 0;
					version++;
				}
			}

			template <class TKey, class TValue>
			bool Dictionary<TKey, TValue>::Contains(KeyValuePair<TKey, TValue> keyValuePair)
			{
				int index = FindEntry(keyValuePair.Key());
				return ((index >= 0) && EqualityComparer<TValue>::Default().Equals(entries[index].value, keyValuePair.Value()));
			}

			template <class TKey, class TValue>
			void Dictionary<TKey, TValue>::CopyTo(KeyValuePair<TKey, TValue> array[], int index)
			{
				CopyTo(array, index);
			}

			template <class TKey, class TValue>
			int Dictionary<TKey, TValue>::FindEntry(TKey key)
			{
				if (buckets != null)
				{
					int num = comparer->GetHashCode(key) & 0x7fffffff;
					for (int i = buckets[num % Array::Length(buckets)]; i >= 0; i = entries[i].next)
					{
						if ((entries[i].hashCode == num) && comparer->Equals(entries[i].key, key))
						{
							return i;
						}
					}
				}
				return -1;
			}

			template <class TKey, class TValue>
			void Dictionary<TKey, TValue>::Initialize(int capacity)
			{
				int prime = HashHelpers::GetPrime(capacity);
				buckets = new int[prime];
				for(int i = 0; i < Array::Length(buckets); i++)
				{
					buckets[i] = -1;
				}
				entries = new Entry<TKey, TValue>[prime];
				freeList = -1;
			}

			template <class TKey, class TValue>
			void Dictionary<TKey, TValue>::Insert(TKey key, TValue value, bool add)
			{
				int _freeList;
				if(buckets == null)
					Initialize(0);

				int num = comparer->GetHashCode(key) & 0x7fffffff;
				int index = num % Array::Length(buckets);
				for(int i = buckets[index]; i >= 0; i = entries[i].next)
				{
					if((entries[i].hashCode == num) && comparer->Equals(entries[i].key, key))
					{
						if(add)
						{
#if DEBUG
							printf("ARGUMENT in function %s, at line %i in file %s: %s\n", __FUNCTION__, __LINE__, __FILE__, "Adding duplicate of existing key.");
#endif
						}

						entries[i].value = value;
						version++;
						return;
					}
				}
				if(freeCount > 0)
				{
					_freeList = freeList;
					freeList = entries[_freeList].next;
					freeCount--;
				}
				else
				{
					if(count == Array::Length(entries))
					{
						Resize();
						index = num % Array::Length(buckets);
					}
					freeList = count;
					count++;
				}
				entries[_freeList].hashCode = num;
				entries[_freeList].next = buckets[index];
				entries[_freeList].key = key;
				entries[_freeList].value = value;
				buckets[index] = freeList;
				version++;
			}

			template <class TKey, class TValue>
			bool Dictionary<TKey, TValue>::Remove(TKey key)
			{
				if(buckets != null)
				{
					int num = comparer->GetHashCode(key) & 0x7fffffff;
					int index = num % Array::Length(buckets);
					int num3 = -1;
					for(int i = buckets[index]; i >= 0; i = entries[i].next)
					{
						if((entries[i].hashCode == num) && comparer->Equals(entries[i].key, key))
						{
							if(num3 < 0)
							{
								buckets[index] = entries[i].next;
							}
							else
							{
								entries[num3].next = entries[i].next;
							}
							entries[i].hashCode = -1;
							entries[i].next = freeList;
							entries[i].key = TKey();
							entries[i].value = TValue();
							freeList = i;
							freeCount++;
							version++;
							return true;
						}
						num3 = i;
					}
				}
				return false;
			}

			template <class TKey, class TValue>
			void Dictionary<TKey, TValue>::Resize()
			{
				int prime = HashHelpers::GetPrime(count * 2);
				int* numArray = new int[prime];
				for(int i = 0; i < Array::Length(numArray); i++)
				{
					numArray[i] = -1;
				}
				Entry<TKey, TValue> destinationArray[] = new Entry<TKey, TValue>[prime];
				Array::Copy(entries, 0, destinationArray, 0, count);
				for(int j = 0; j < count; j++)
				{
					int index = destinationArray[j].hashCode % prime;
					destinationArray[j].next = numArray[index];
					numArray[index] = j;
				}
				buckets = numArray;
				entries = destinationArray;
			}

			template <class TKey, class TValue>
			bool Dictionary<TKey, TValue>::TryGetValue(TKey key, out TValue value)
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
			template <class UKey, class UValue>
			Dictionary<TKey, TValue>::KeyCollection<UKey, UValue>::KeyCollection(Dictionary<TKey,TValue> dictionary)
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
			int Dictionary<TKey, TValue>::KeyCollection<UKey, UValue>::Count()
			{
				return _dictionary.Count();
			}

			template <class TKey, class TValue>
			template <class UKey, class UValue>
			void Dictionary<TKey, TValue>::KeyCollection<UKey, UValue>::Add(UKey item)
			{
#if DEBUG
				printf("NOT_SUPPORTED in function %s, at line %i in file %s: %s\n", __FUNCTION__, __LINE__, __FILE__, "Adding keys directly to the Dictionary::Keycollection is not supported.");
#endif
			}

			template <class TKey, class TValue>
			template <class UKey, class UValue>
			void Dictionary<TKey, TValue>::KeyCollection<UKey, UValue>::Clear()
			{
#if DEBUG
				printf("NOT_SUPPORTED in function %s, at line %i in file %s: %s\n", __FUNCTION__, __LINE__, __FILE__, "Directly clearing the Dictionary::KeyCollection is not supported.");
#endif
			}

			template <class TKey, class TValue>
			template <class UKey, class UValue>
			bool Dictionary<TKey, TValue>::KeyCollection<UKey, UValue>::Contains(UKey item)
			{
				return _dictionary.ContainsKey(item);
			}

			template <class TKey, class TValue>
			template <class UKey, class UValue>
			void Dictionary<TKey, TValue>::KeyCollection<UKey, UValue>::CopyTo(UKey array[], int index)
			{
				if(array == null)
				{
#if DEBUG
					printf("ARGUMENT_NULL in function %s, at line %i in file %s, argument \"%s\"\n", __FUNCTION__, __LINE__, __FILE__, "array");
#endif
					return;
				}
				if((index < 0) ||(index > Array::Length(array)))
				{
#if DEBUG
					printf("ARGUMENT_OUT_OF_RANGE in function %s, at line %i in file %s, argument \"%s\": %s\n", __FUNCTION__, __LINE__, __FILE__, "index", "Non-negative array index required.");
#endif
					return;
				}
				if((Array::Length(array) - index) < _dictionary.Count())
				{
#if DEBUG
					printf("ARGUMENT in function %s, at line %i in file %s: %s\n", __FUNCTION__, __LINE__, __FILE__, "Array plus offset too small.");
#endif
					return;
				}
				int count = _dictionary.Count();
				Entry<UKey, UValue> entries[] = _dictionary.entries;
				for(int i = 0; i < count; i++)
				{
					if(entries[i].hashCode >= 0)
					{
						array[index++] = entries[i].key;
					}
				}
			}

			template <class TKey, class TValue>
			template <class UKey, class UValue>
			bool Dictionary<TKey, TValue>::KeyCollection<UKey, UValue>::Remove(UKey item)
			{
#if DEBUG
				printf("NOT_SUPPORTED in function %s, at line %i in file %s: %s\n", __FUNCTION__, __LINE__, __FILE__, "Removing keys directly from the Dictionary::KeyCollection is not supported.");
#endif
				return false;
			}
		}
	}
}
