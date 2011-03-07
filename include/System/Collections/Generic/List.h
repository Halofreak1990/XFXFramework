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
				int _version;

				void EnsureCapacity(int min)
				{
					if(Array::Length(_items) < min)
					{
						int num = (Array::Length(_items) == 0) ? _defaultCapacity : (Array::Length(_items) * 2);
						if(num < min)
						{
							num = min;
						}
						Capacity(num);
					}
				}

			public:	
				int Count() // Gets the number of elements actually contained in the List<>.
				{
					return _size;
				}

				int Capacity() // Gets the total number of elements the internal data structure can hold without resizing.
				{
					return Array::Length(_items);
				}

				void Capacity(int value) // Sets the total number of elements the internal data structure can hold without resizing.
				{
					if (value != Array::Length(_items))
					{
						if (value < _size)
						{
							throw ArgumentOutOfRangeException("value", "New capacity too small.");
						}
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
					}
				}

 				List() // Initializes a new instance of the List<> class that is empty and has the default initial capacity.
				{
					_emptyArray = new T[0];
					_items = _emptyArray;
				}

				List(int capacity) // Initializes a new instance of the List<> class that is empty and has the specified initial capacity.
				{
					if(capacity < 0)
						throw ArgumentOutOfRangeException("capacity", "Non-negative number required.");

					_items = new T[capacity];
				}

				~List()
				{
					if(_items)
						delete[] _items;
				}

 				void Add(T item) //Adds an element to the end of the list
				{
					if(_size == Array::Length(_items))
					{
						EnsureCapacity(_size + 1);
					}
					_items[_size++] = item;
					_version++;
				}

				int BinarySearch(T item)
				{
					return BinarySearch(0, Count(), item, null);
				}
				int BinarySearch(T item, IComparer<T>* comparer)
				{
					return BinarySearch(0, Count(), item, comparer);
				}
				int BinarySearch(int index, int count, T item, IComparer<T>* comparer)
				{
					if ((index < 0) || (count < 0))
					{
						throw ArgumentOutOfRangeException((index < 0) ? "index" : "count", "Non-negative number required.");
					}
					if ((_size - index) < count)
					{
						throw ArgumentException("Invalid Offset.");
					}
					return Array::BinarySearch<T>(_items, index, count, item, comparer);
				}

 				void Clear() //Removes all elements from the list
				{
					if(_size)
					{
						delete[] _items;
						_items = _emptyArray;
						_size = 0;
					}
					_version++;
				}

				bool Contains(T item) // Determines whether an element is in the List<>.
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

				int IndexOf(T item) // Searches for the specified object and returns the zero-based index of the first occurrence within the entire List<>.
				{
					return Array::IndexOf(_items, item, 0, _size);
				}
				
				void Insert(int index, T item) // Inserts an element into the List<> at the specified index.
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

 				bool Remove(T item) // Removes the first occurrence of a specific object from the List<>.
				{
					int index = IndexOf(item);
					if (index >= 0)
					{
						RemoveAt(index);
						return true;
					}
					return false;
				}

				void RemoveAt(int index) // Removes the element at the specified index of the List<>.
				{
					if(index < 0 || index >= _size)
						throw ArgumentOutOfRangeException("index", "Index was out of range. Must be non-negative and less than the size of the collection.");

					_size--;
					if(index < _size)
					{
						Array::Copy(_items, index +1, _items, index, _size - index);
					}
					_items[_size] = new T();
					_version++;
				}

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

				T *ToArray()
				{
					return _items;
				}

				void TrimExcess()
				{
					int num = (int)(Array::Length(_items) * 0.9);
					if(_size < num)
					{
						Capacity(_size);
					}
				}

				T operator[](int index)
				{
					if(index >= _size)
						throw ArgumentOutOfRangeException("index");

					return _items[index];
				}
			};

			/// <summary>
			/// Represents a strongly typed list of objects that can be accessed by index. Provides methods to search, sort, and
			/// manipulate lists.
			/// </summary>
			template <class T>
			class List<T *> : public IList<T *>
			{
			private:
				static const int _defaultCapacity = 4;
				static T** _emptyArray;
				T** _items;
				int _size;
				int _version;

				void EnsureCapacity(int min)
				{
					if(Array::Length(_items) < min)
					{
						int num = (Array::Length(_items) == 0) ? _defaultCapacity : (Array::Length(_items) * 2);
						if(num < min)
						{
							num = min;
						}
						Capacity(num);
					}
				}

			public:	
				int Count() // Gets the number of elements actually contained in the List<>.
				{
					return _size;
				}

				int Capacity() // Gets the total number of elements the internal data structure can hold without resizing.
				{
					return Array::Length(_items);
				}

				void Capacity(int value) // Sets the total number of elements the internal data structure can hold without resizing.
				{
					if (value != Array::Length(_items))
					{
						if (value < _size)
						{
							throw ArgumentOutOfRangeException("value", "New capacity too small.");
						}
						if (value > 0)
						{
							T** destinationArray = new T*[value];
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
							_items = new T*[0];
						}
					}
				}

 				List() // Initializes a new instance of the List<> class that is empty and has the default initial capacity.
				{
					_emptyArray = new T*[0];
					_items = _emptyArray;
				}

				List(int capacity) // Initializes a new instance of the List<> class that is empty and has the specified initial capacity.
				{
					if(capacity < 0)
						throw ArgumentOutOfRangeException("capacity", "Non-negative number required.");

					_items = new T*[capacity];
				}

				~List()
				{
					if(_items)
						delete[] _items;
				}

 				void Add(T* item) //Adds an element to the end of the list
				{
					if(_size == Array::Length(_items))
					{
						EnsureCapacity(_size + 1);
					}
					_items[_size++] = item;
					_version++;
				}

				int BinarySearch(T* item)
				{
					return BinarySearch(0, Count(), item, null);
				}
				int BinarySearch(T* item, IComparer<T>* comparer)
				{
					return BinarySearch(0, Count(), item, comparer);
				}
				int BinarySearch(int index, int count, T* item, IComparer<T>* comparer)
				{
					if ((index < 0) || (count < 0))
					{
						throw ArgumentOutOfRangeException((index < 0) ? "index" : "count", "Non-negative number required.");
					}
					if ((_size - index) < count)
					{
						throw ArgumentException("Invalid Offset.");
					}
					return Array::BinarySearch<T>(_items, index, count, item, comparer);
				}

 				void Clear() //Removes all elements from the list
				{
					if(_size)
					{
						delete[] _items;
						_items = _emptyArray;
						_size = 0;
					}
					_version++;
				}

				bool Contains(T* item) // Determines whether an element is in the List<>.
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

				void CopyTo(T* array[]) // Copies the entire List<> to a compatible one-dimensional array, starting at the beginning of the target array.
				{
					Array::Copy(_items, 0, array, 0, _size);
				}

				void CopyTo(T* array[], int arrayIndex) // Copies the entire List<> to a compatible one-dimensional array, starting at the specified index of the target array.
				{
					Array::Copy(_items, 0, array, arrayIndex, _size);
				}

				int IndexOf(T* item) // Searches for the specified object and returns the zero-based index of the first occurrence within the entire List<>.
				{
					return Array::IndexOf(_items, item, 0, _size);
				}
				
				void Insert(int index, T* item) // Inserts an element into the List<> at the specified index.
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

 				bool Remove(T* item) // Removes the first occurrence of a specific object from the List<>.
				{
					int index = IndexOf(item);
					if (index >= 0)
					{
						RemoveAt(index);
						return true;
					}
					return false;
				}

				void RemoveAt(int index) // Removes the element at the specified index of the List<>.
				{
					if(index < 0 || index >= _size)
						throw ArgumentOutOfRangeException("index", "Index was out of range. Must be non-negative and less than the size of the collection.");

					_size--;
					if(index < _size)
					{
						Array::Copy(_items, index +1, _items, index, _size - index);
					}
					_items[_size] = new T();
					_version++;
				}

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

				T** ToArray()
				{
					return _items;
				}

				void TrimExcess()
				{
					int num = (int)(Array::Length(_items) * 0.9);
					if(_size < num)
					{
						Capacity(_size);
					}
				}

				T* operator[](int index)
				{
					if(index >= _size)
						throw ArgumentOutOfRangeException("index");

					return _items[index];
				}
			};
		}
	}
}

#endif //_SYSTEM_COLLECTIONS_GENERIC_LIST_
