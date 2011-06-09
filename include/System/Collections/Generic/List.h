/********************************************************
 *	List.h												*
 *														*
 *	XFX Generic List definition file					*
 *	Copyright © XFX Team. All Rights Reserved			*
 ********************************************************/
#ifndef _SYSTEM_COLLECTIONS_GENERIC_LIST_
#define _SYSTEM_COLLECTIONS_GENERIC_LIST_

#include <System/Array.h>
#include <System/Exception.h>
#include <System/Types.h>
#include "Interfaces.h"

#include <stdlib.h>
#include <string.h>

namespace System
{
	namespace Collections
	{
		namespace Generic
		{
			/// <summary>
			/// Represents a strongly typed list of objects that can be accessed by index. Provides methods to search, sort, and
			/// manipulate lists.
			/// </summary>
			template <class T>
			class List : public IList<T>
			{
			private:
				static const int _defaultCapacity = 4;
				static T* _emptyArray;
				T* _items;
				int _size;
				int _actualSize;
				int _version;

				void EnsureCapacity(int capacity);

			public:	
				int Count(); // Gets the number of elements actually contained in the List<>.
				int getCapacity(); // Gets the total number of elements the internal data structure can hold without resizing.
				void setCapacity(int value); // Sets the total number of elements the internal data structure can hold without resizing.

 				List(); // Initializes a new instance of the List<> class that is empty and has the default initial capacity.
				List(int capacity); // Initializes a new instance of the List<> class that is empty and has the specified initial capacity.
				List(const List &obj); // Copy constructor
				~List(); // Destructor

 				void Add(T &item); // Adds an element to the end of the list
 				void Clear(); //Removes all elements from the list
				bool Contains(T &item) // Determines whether an element is in the List<>.
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

				void CopyTo(T array[]) // Copies the entire List<> to a compatible one-dimensional array, starting at the beginning of the target array.
				{
					Array::Copy(_items, 0, array, 0, _size);
				}

				void CopyTo(T array[], int arrayIndex) // Copies the entire List<> to a compatible one-dimensional array, starting at the specified index of the target array.
				{
					Array::Copy(_items, 0, array, arrayIndex, _size);
				}

				int IndexOf(T &item) // Searches for the specified object and returns the zero-based index of the first occurrence within the entire List<>.
				{
					return Array::IndexOf(_items, item, 0, _size);
				}
				
				void Insert(int index, T &item) // Inserts an element into the List<> at the specified index.
				{
					if (index > _size)
					{
						throw ArgumentOutOfRangeException("index", "Index must be within the bounds of the List.");
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

 				bool Remove(T &item) // Removes the first occurrence of a specific object from the List<>.
				{
					int index = IndexOf(item);
					if (index >= 0)
					{
						RemoveAt(index);
						return true;
					}
					return false;
				}

				void RemoveAt(int index); // Removes the element at the specified index of the List<>.
 				void RemoveRange(int index, int count) // Removes a range of elements from the List<>.
				{
					if ((index < 0) || (count < 0))
					{
						throw ArgumentOutOfRangeException((index < 0) ? "index" : "count", "Non-negative number required.");
					}
					if ((_size - index) < count)
					{
						throw ArgumentException("Offset and length were out of bounds for the array or count is greater than the number of elements from index to the end of the source collection.");
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
					Reverse(0, Count());
				}

				void Reverse(int index, int count)
				{
					if ((index < 0) || (count < 0))
					{
						throw ArgumentOutOfRangeException((index < 0) ? "index" : "count", "Non-negative number required.");
					}
					if ((_size - index) < count)
					{
						throw ArgumentException("Offset and length were out of bounds for the array or count is greater than the number of elements from index to the end of the source collection.");
					}
					Array::Reverse(_items, index, count);
					_version++;
				}

				T* ToArray()
				{
					return _items;
				}

				void TrimExcess()
				{
					int num = (int)(Array::Length(_items) * 0.9);
					if(_size < num)
					{
						setCapacity(_size);
					}
				}

				T& operator[](int index);
				List<T>& operator =(const List &other);
			};

			//////////////////////////////////////////////////////////////////////

			template <class T>
			List<T>::List()
			{
				{
					_actualSize = _defaultCapacity;

					_size = 0;
					_items = (T *)malloc(_actualSize * sizeof(T));

					if (_items == null)
						throw OutOfMemoryException();
				}
			}

			template <class T>
			List<T>::List(int capacity)
			{
				if(capacity < 0)
					throw ArgumentOutOfRangeException("capacity", "Non-negative number required.");

				_actualSize = capacity;

				_size = 0;
				_items = (T)malloc(_actualSize * sizeof(T));

				if (_items == null)
					throw OutOfMemoryException();
			}

			template <class T>
			List<T>::List(const List<T> &obj)
			{
				_items = (T *)malloc(sizeof(T) * obj._actualSize);

				if (_items == null)
					throw OutOfMemoryException();

				memcpy(_items, obj._items, sizeof(T) * obj._actualSize);
				_actualSize = obj._actualSize;
				_size = obj._size;
			}

			template <class T>
			List<T>::~List()
			{
				if(_items)
				{
					free(_items);
					_items = null;
				}
			}

			template <class T>
			int List<T>::getCapacity()
			{
				return _actualSize;
			}

			template <class T>
			void List<T>::setCapacity(int value)
			{
				_size = value;

				if (_size != 0) 
				{ 
					// change array memory size  
					// if new size is larger than current  
					// or new size is less then half of the current  
					if ((_size > _actualSize) || (_size < _actualSize/2)) 
					{ 
	    				_actualSize = _size;
	    				_items = (T *)realloc(_items, sizeof(T) * _size);
			 
						if (_items == null) 
							throw OutOfMemoryException();
					} 
				} 
				else 
					Clear();
			}

			template <class T>
			int List<T>::Count()
			{
				return _size;
			}

			template <class T>
			void List<T>::Add(T &item)
			{
				_size++;
 
				if (_size > _actualSize) 
				{ 
					_actualSize *= 2;
			 
					_items = (T *)realloc(_items, sizeof(T) * _actualSize);
			 
					if (_items == null) 
						throw OutOfMemoryException();
				} 
			 
				_items[_size-1] = item;
			}

			template <class T>
			void List<T>::Clear()
			{
				_size = 0; 
				_items = (T *)realloc(_items, sizeof(T) * _defaultCapacity); 
				// set initial memory size again  
				_actualSize = _defaultCapacity;
			}

			template <class T>
			void List<T>::EnsureCapacity(int min)
			{
				if (_size < min)
				{
					int num = (_size == 0) ? 4 : (_size * 2);
					if (num < min)
					{
						num = min;
					}
					setCapacity(num);
				}
			}

			template <class T>
			void List<T>::RemoveAt(int index)
			{
				if(index < 0 || index >= _size)
					throw ArgumentOutOfRangeException("index", "Index was out of range. Must be non-negative and less than the size of the collection.");

				if (_size == 1)
					Clear();
				else
				{
					// otherwise, shift array elements  
					for(int i=index; i < _size - 1; i++) 
						_items[i] = _items[i+1];
			 
					// decrease array size 
					_size--;
				}
			}

			template <class T>
			T& List<T>::operator [](int index)
			{
				if(index >= _size)
					throw ArgumentOutOfRangeException("index");

				return _items[index];
			}

			template <class T>
			List<T>& List<T>::operator =(const List<T> &other)
			{ 
				if (this == &other) // in case somebody tries assign array to itself  
					return *this;
			 
				if (other._size == 0) // is other array is empty -- clear this array  
					Clear();
			 
				setCapacity(other._size); // set size  
			 
				memcpy(_items, other._items, sizeof(T) * other._size);
			 
				return *this;
			}
		}
	}
}

#endif //_SYSTEM_COLLECTIONS_GENERIC_LIST_
