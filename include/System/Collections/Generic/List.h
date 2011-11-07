/********************************************************
 *	List.h												*
 *														*
 *	XFX Generic List definition file					*
 *	Copyright © XFX Team. All Rights Reserved			*
 ********************************************************/
#ifndef _SYSTEM_COLLECTIONS_GENERIC_LIST_
#define _SYSTEM_COLLECTIONS_GENERIC_LIST_

#include <System/Array.h>
#include <System/Object.h>
#include "Interfaces.h"

#include <stdlib.h>
#include <string.h>

#if DEBUG
#include <stdio.h>
#endif

namespace System
{
	namespace Collections
	{
		namespace Generic
		{
			// Represents a strongly typed list of objects that can be accessed by index. Provides methods to search, sort, and manipulate lists.
			template <class T>
			class List : public IList<T>, virtual Object
			{
			private:
				static const int _defaultCapacity = 4;
				T* _items;
				int _size;
				int _actualSize;
				int _version;

				void EnsureCapacity(int capacity)
				{
					if (_actualSize < capacity)
					{
						int num = (_actualSize == 0) ? _defaultCapacity : _actualSize * 2;
						if (num > 0x7fefffff)
						{
							num = 0x7fefffff;
						}
						if (num < capacity)
						{
							num = capacity;
						}
						_actualSize = num;
					}
				}

			public:	
				// Gets the number of elements actually contained in the List<>.
				int Count()
				{
					return _size;
				}

				// Gets the total number of elements the internal data structure can hold without resizing.
				int getCapacity()
				{
					return _actualSize;
				}

				// Sets the total number of elements the internal data structure can hold without resizing.
				void setCapacity(int value)
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
								Array::Copy(_items, 0, destinationArray, 0, _size);
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

				bool IsReadOnly()
				{
					return false;
				}

				// Initializes a new instance of the List<> class that is empty and has the default initial capacity.
 				List()
				{
					_actualSize = _defaultCapacity;

					_size = 0;

					_items = new T[_actualSize];
				}

				// Initializes a new instance of the List<> class that is empty and has the specified initial capacity.
				List(int capacity)
				{
					if (capacity < 0)
						_actualSize = _defaultCapacity;

					_actualSize = capacity;

					_size = 0;

					_items = new T[_actualSize];
				}

				List(const List &obj); // Copy constructor

				~List()
				{
					delete[] _items;
				}

				// Adds an element to the end of the list
 				void Add(T item)
				{
					if (_size == Array::Length(_items))
					{
						EnsureCapacity(_size + 1);
					}
					_items[_size++] = item;
					_version++;
				}

				//Removes all elements from the list
 				void Clear()
				{
					if (_size > 0)
					{
						delete _items;
						_items = new T[_actualSize];
						_size = 0;
					}
					_version++;
				}

				// Determines whether an element is in the List<>.
				bool Contains(T item)
				{
					for (int i = 0; i < _size; i++)
					{
						/*if (_items[i] == item)
						{
							return true;
						}*/
					}
					return false;
				}

				// Copies the entire List<> to a compatible one-dimensional array, starting at the beginning of the target array.
				void CopyTo(T array[])
				{
					Array::Copy(_items, 0, array, 0, _size);
				}

				// Copies the entire List<> to a compatible one-dimensional array, starting at the specified index of the target array.
				void CopyTo(T array[], int arrayIndex)
				{
					Array::Copy(_items, 0, array, arrayIndex, _size);
				}

				// Searches for the specified object and returns the zero-based index of the first occurrence within the entire List<>.
				int IndexOf(T item)
				{
					return Array::IndexOf(_items, item, 0, _size);
				}
				
				// Inserts an element into the List<> at the specified index.
				void Insert(int index, T item)
				{
					if (index > _size)
					{
						//throw ArgumentOutOfRangeException("index", "Index must be within the bounds of the List.");
						return;
					}
					if (_size == Array::Length(_items))
					{
						EnsureCapacity(_size + 1);
					}
					if (index < _size)
					{
						Array::Copy(_items, index, _items, index + 1, _size - index);
					}
					_items[index] = item;
					_size++;
					_version++;
				}

				// Removes the first occurrence of a specific object from the List<>.
 				bool Remove(T item)
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
				void RemoveAt(int index)
				{
					Array::Copy(_items, index + 1, _items, index, _size - index);
					_size--;
					_version++;
				}

				// Removes a range of elements from the List<>.
 				void RemoveRange(int index, int count)
				{
					if ((index < 0) || (count < 0))
					{
#if DEBUG
						printf("ARGUMENT_OUT_OF_RANGE in function %s, at line %i in file %s, argument \"%s\": %s\n", __FUNCTION__, __LINE__, __FILE__, (index < 0) ? "index" : "count", "Non-negative number required.");
#endif
						return;
					}
					if ((_size - index) < count)
					{
#if DEBUG
						printf("ARGUMENT in function %s, at line %i in file %s: %s\n", __FUNCTION__, __LINE__, __FILE__, "Offset and length were out of bounds for the array or count is greater than the number of elements from index to the end of the source collection.");
#endif
						return;
					}
					if (count > 0)
					{
						_size -= count;
						if (index < _size)
						{
							Array::Copy(_items, index + count, _items, index, _size - index);
						}
						Array::Clear(_items, _size, count);
						_version++;
					}
				}

				void Reverse()
				{
					Reverse(0, _size);
				}

				void Reverse(int index, int count)
				{
					if ((index < 0) || (count < 0))
					{
#if DEBUG
						printf("ARGUMENT_OUT_OF_RANGE in function %s, at line %i in file %s, argument \"%s\": %s\n", __FUNCTION__, __LINE__, __FILE__, (index < 0) ? "index" : "count", "Non-negative number required.");
#endif
						return;
					}
					if ((_size - index) < count)
					{
#if DEBUG
						printf("ARGUMENT in function %s, at line %i in file %s: %s\n", __FUNCTION__, __LINE__, __FILE__, "Offset and length were out of bounds for the array or count is greater than the number of elements from index to the end of the source collection.");
#endif
						return;
					}
					Array::Reverse(_items, index, count);
					_version++;
				}

				T* ToArray()
				{
					T* destinationArray = new T[_size];
					Array::Copy(_items, 0, destinationArray, 0, _size);
					return destinationArray;
				}

				char* ToString()
				{
					return "";
				}

				void TrimExcess()
				{
					int num = (int)(Array::Length(_items) * 0.9);
					if(_size < num)
					{
						setCapacity(_size);
					}
				}

				T operator[](int index)
				{
					return _items[index];
				}

				List<T> operator =(const List<T> other)
				{
					delete[] _items;
					_actualSize = other._actualSize;
					_size = other._size;
					_items = new T[other._actualSize];
					Array::Copy(other._items, 0, _items, 0, other._size);
					_version = other._version;
				}
			};

			//////////////////////////////////////////////////////////////////////

			template <class T>
			class List<T*> : public IList<T*>, virtual Object
			{
			private:
				static const int _defaultCapacity = 4;
				static T* _emptyArray;
				T* _items;
				int _size;
				int _actualSize;
				int _version;

				void EnsureCapacity(int capacity)
				{
					if (_actualSize < capacity)
					{
						int num = (_actualSize == 0) ? _defaultCapacity : _actualSize * 2;
						if (num > 0x7fefffff)
						{
							num = 0x7fefffff;
						}
						if (num < capacity)
						{
							num = capacity;
						}
						_actualSize = num;
					}
				}

			public:
				// Gets the number of elements actually contained in the List<>.
				int Count()
				{
					return _size;
				}

				bool IsReadOnly()
				{
					return false;
				}

				List()
				{
					_actualSize = _defaultCapacity;

					_size = 0;

					_items = new T[_actualSize];
				}

				List(int capacity)
				{
					if (capacity < 0)
						_actualSize = _defaultCapacity;

					_actualSize = capacity;

					_size = 0;

					_items = new T[_actualSize];
				}

				~List()
				{
					delete[] _items;
				}

				void Add(T* item)
				{
					if (_size == Array::Length(_items))
					{
						EnsureCapacity(_size + 1);
					}
					_items[_size++] = *item;
					_version++;
				}

				bool Contains(T* item)
				{
					for (int i = 0; i < _size; i++)
					{
						/*if (_items[i] == *item)
						{
							return true;
						}*/
					}
					return false;
				}

				//Removes all elements from the list
 				void Clear()
				{
					if (_size > 0)
					{
						delete _items;
						_items = new T[_actualSize];
						_size = 0;
					}
					_version++;
				}

				// Copies the entire List<> to a compatible one-dimensional array, starting at the beginning of the target array.
				void CopyTo(T* array[])
				{
					Array::Copy(_items, 0, *array, 0, _size);
				}

				// Copies the entire List<> to a compatible one-dimensional array, starting at the specified index of the target array.
				void CopyTo(T* array[], int arrayIndex)
				{
					Array::Copy(_items, 0, *array, arrayIndex, _size);
				}

				// Searches for the specified object and returns the zero-based index of the first occurrence within the entire List<>.
				int IndexOf(T* item)
				{
					return Array::IndexOf(_items, *item, 0, _size);
				}
				
				// Inserts an element into the List<> at the specified index.
				void Insert(int index, T* item)
				{
					if (index > _size)
					{
						//throw ArgumentOutOfRangeException("index", "Index must be within the bounds of the List.");
						return;
					}
					if (_size == Array::Length(_items))
					{
						EnsureCapacity(_size + 1);
					}
					if (index < _size)
					{
						Array::Copy(_items, index, _items, index + 1, _size - index);
					}
					_items[index] = *item;
					_size++;
					_version++;
				}

				// Removes the first occurrence of a specific object from the List<>.
 				bool Remove(T* item)
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
				void RemoveAt(int index)
				{
					Array::Copy(_items, index + 1, _items, index, _size - index);
					_size--;
					_version++;
				}

				T* ToArray()
				{
					T* destinationArray = new T[_size];
					Array::Copy(_items, 0, destinationArray, 0, _size);
					return destinationArray;
				}

				char* ToString()
				{
					return "";
				}

				T* operator[](int index)
				{
				}

				List<T> operator =(const List other)
				{
				}
			};
		}
	}
}

#endif //_SYSTEM_COLLECTIONS_GENERIC_LIST_
