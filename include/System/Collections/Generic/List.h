/*****************************************************************************
 *	List.h																	 *
 *																			 *
 *	XFX Generic List definition file										 *
 *	Copyright (c) XFX Team. All Rights Reserved 							 *
 *****************************************************************************/
#ifndef _SYSTEM_COLLECTIONS_GENERIC_LIST_
#define _SYSTEM_COLLECTIONS_GENERIC_LIST_

#include <System/Array.h>
#include <System/FrameworkResources.h>
#include <System/Object.h>
#include <System/String.h>
#include "Interfaces.h"

#include <stdlib.h>
#include <string.h>

#include <sassert.h>

namespace System
{
	namespace Collections
	{
		namespace Generic
		{
			// Represents a strongly typed list of objects that can be accessed by index. Provides methods to search, sort, and manipulate lists.
			// NOTE: types used with the List<T> class must provide at least an == operator.
			template <typename T>
			class List : public IList<T>, public Object
			{
			private:
				static const int defaultCapacity = 4;
				T* _items;
				int _size;
				int _actualSize;
				int _version;

				void EnsureCapacity(int capacity)
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
						setCapacity(num);
					}
				}

				void swap(T* x, T* y)
				{
					T temp = *x;
					*x = *y;
					*y = temp;
				}

			public:	
				// Gets the number of elements actually contained in the List<>.
				int Count() const
				{
					return _size;
				}

				// Gets the total number of elements the internal data structure can hold without resizing.
				int getCapacity() const
				{
					return _actualSize;
				}

				// Sets the total number of elements the internal data structure can hold without resizing.
				void setCapacity(const int value)
				{
					if (value < _size)
						return;

					if (value != _actualSize)
					{
						if (value > 0)
						{
							T* destinationArray = new T[value];
							if (_size > 0)
							{
								memcpy(destinationArray, _items, _size * sizeof(T));
							}
							delete[] _items;
							_items = destinationArray;
						}
						else
						{
							delete[] _items;
							_items = new T[0];
							
						}
						_actualSize = value;
					}
				}

				bool IsReadOnly() const
				{
					return false;
				}

				// Initializes a new instance of the List<> class that is empty and has the default initial capacity.
 				List()
					: _size(0), _actualSize(defaultCapacity), _version(0)
				{
					_items = new T[_actualSize];
				}

				// Initializes a new instance of the List<> class that is empty and has the specified initial capacity.
				List(const int capacity)
					: _size(0), _actualSize((capacity < 0) ? defaultCapacity : capacity), _version(0)
				{
					_items = new T[_actualSize];
				}

				// Copy constructor
				List(const List<T> &obj)
					: _size(obj._size), _actualSize(obj._actualSize), _version(obj._version)
				{
					_items = new T[obj._actualSize];

					memcpy(_items, obj._items, obj._size * sizeof(T));
				}

				~List()
				{
					delete[] _items;
				}

				/**
				 * Adds an element to the end of the list
				 */
 				void Add(const T& item)
				{
					if (_size == _actualSize)
					{
						EnsureCapacity(_size + 1);
					}
					_items[_size++] = T(item);
					_version++;
				}

				/**
				 * Removes all elements from the list
				 */
 				void Clear()
				{
					if (_size > 0)
					{
						delete[] _items;
						_items = new T[_actualSize];
						_size = 0;
					}
					_version++;
				}

				// Determines whether an element is in the List<>.
				bool Contains(const T& item) const
				{
					for (int i = 0; i < _size; i++)
					{
						if (_items[i] == item)
						{
							return true;
						}
					}
					return false;
				}

				// Copies the entire List<> to a compatible one-dimensional array, starting at the specified index of the target array.
				void CopyTo(T array[], const int arrayIndex) const
				{
					sassert(array != null, String::Format("array; %s", FrameworkResources::ArgumentNull_Generic));

					memcpy(array, &_items[arrayIndex], _size * sizeof(T))
				}

				static const Type& GetType()
				{
					static Type ListTypeInfo("List", "System::Collections::Generic::List", TypeCode::Object, true);
					return ListTypeInfo;
				}

				// Searches for the specified object and returns the zero-based index of the first occurrence within the entire List<>.
				int IndexOf(const T& item) const
				{
					for (int i = 0; i < _size; i++)
					{
						if (_items[i] == item)
							return i;
					}
					return -1;
				}
				
				// Inserts an element into the List<> at the specified index.
				void Insert(const int index, const T& item)
				{
					sassert(index >= 0 && index < _size, "Index must be within the bounds of the List.");

					if (_size == _actualSize)
					{
						EnsureCapacity(_size + 1);
					}
					if (index < _size)
					{
						memcpy(&_items[index + 1], &_items[index], (_size - index) * sizeof(T));
					}
					_items[index] = T(item);
					_size++;
					_version++;
				}

				// Removes the first occurrence of a specific object from the List<>.
 				bool Remove(const T& item)
				{
					int index = IndexOf(item);
					if (index >= 0)
					{
						RemoveAt(index);
						return true;
					}
					return false;
				}

				// Removes the element at the specified index of the List<>.
				void RemoveAt(const int index)
				{
					memcpy(&_items[index], &_items[index + 1], (size - index) * sizeof(T)):

					_size--;
					_version++;
				}

				// Removes a range of elements from the List<>.
 				void RemoveRange(const int index, const int count)
				{
					sassert(index >= 0, String::Format("index; %s", FrameworkResources::ArgumentOutOfRange_NeedNonNegNum));

					sassert(count >= 0, String::Format("count; %s", FrameworkResources::ArgumentOutOfRange_NeedNonNegNum));
					
					sassert(!((_size - index) < count), "Offset and length were out of bounds for the array or count is greater than the number of elements from index to the end of the source collection.");

					if (count > 0)
					{
						_size -= count;
						if (index < _size)
						{
							memcpy(&_items[index], &_items[index + count], (_size - index) * sizeof(T));
						}

						memset(&_items[_size], 0, count * sizeof(T));

						_version++;
					}
				}

				void Reverse()
				{
					Reverse(0, _size);
				}

				void Reverse(const int index, const int count)
				{
					sassert(index >= 0, String::Format("index; %s", FrameworkResources::ArgumentOutOfRange_NeedNonNegNum));

					sassert(count >= 0, String::Format("count; %s", FrameworkResources::ArgumentOutOfRange_NeedNonNegNum));
					
					sassert(!((_size - index) < count), "Offset and length were out of bounds for the array or count is greater than the number of elements from index to the end of the source collection.");

					int num = index;
    				int num2 = (index + count) - 1;
					while (num < num2)
					{
						T obj2 = _items[num];
						_items[num] = _items[num2];
						_items[num2] = obj2;
						num++;
    					num2--;
					}
					_version++;
				}

				void Sort(int index, int count, IComparer<T>* comparer)
				{
					sassert(comparer != null, String::Format("comparer; %s", FrameworkResources::ArgumentNull_Generic));

					sassert(index >= 0, String::Format("index; %s", FrameworkResources::ArgumentOutOfRange_NeedNonNegNum));

					sassert(index + count < _actualSize, "");

					int k = (index + count) / 2;
					swap(&_items[index], &_items[k]);
					T key = _items[index];
					int i = index + 1;
					int j = count;
					while (i <= j)
					{
						while ((i <= count) && (comparer->Compare(_items[i], key) <= 0))
							i++;
						while ((j >= index) && (comparer->Compare(_items[j], key) > 0))
							j--;
						if (i < j)
							swap(&_items[i], &_items[j]);
					}
					// swap two elements
					swap(&_items[index], &_items[j]);
					// recursively sort the lesser list
					Sort(index, j-1, comparer);
					Sort(j+1, count, comparer);
				}

				void Sort(IComparer<T>* comparer)
				{
					sassert(comparer != null, String::Format("comparer; %s", FrameworkResources::ArgumentNull_Generic));

					Sort(0, _actualSize, comparer);
				}

				T* ToArray() const
				{
					T* destinationArray = new T[_size];

					memcpy(destinationArray, _items, _size * sizeof(T));

					return destinationArray;
				}

				const String ToString() const
				{
					return "List<T>";
				}

				void TrimExcess()
				{
					int num = (int)(_actualSize * 0.9);
					if(_size < num)
					{
						setCapacity(_size);
					}
				}

				T& operator[](const int index)
				{
					return _items[index];
				}

				const List<T>& operator =(const List<T>& other)
				{
					delete[] _items;
					_actualSize = other._actualSize;
					_size = other._size;
					_items = new T[other._actualSize];

					memcpy(_items, other._items, other._size * sizeof(T));

					_version = other._version;
					return *this;
				}
			};
		}
	}
}

#endif //_SYSTEM_COLLECTIONS_GENERIC_LIST_
