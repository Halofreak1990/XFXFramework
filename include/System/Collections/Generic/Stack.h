#ifndef _SYSTEM_COLLECTIONS_GENERIC_STACK_
#define _SYSTEM_COLLECTIONS_GENERIC_STACK_

#include <System/Array.h>
#include <System/Object.h>
#include <System/String.h>
#include <System/Collections/Generic/EqualityComparer.h>

#include <sassert.h>

namespace System
{
	namespace Collections
	{
		namespace Generic
		{
			// Represents a variable size last-in-first-out (LIFO) collection of instances of the same arbitrary type.
			template <class T>
			class Stack : public ICollection<T>, public Object
			{
			private:
				T* _array;
				static const int _defaultCapacity = 4;
				int _actualSize;
				int _size;
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
						// TODO: implement
						//setCapacity(num);
					}
				}

			public:
				int Count()
				{
					return _size;
				}

				bool IsSynchronized()
				{
					return false;
				}

				Stack()
				{
					_array = new T[_defaultCapacity];
					_actualSize = _defaultCapacity;
					_size = 0;
					_version = 0;
				}

				Stack(ICollection<T>* col)
				{
					sassert(col != null, "");

					_array = new T[col->Count()];
					_actualSize = col->Count();

					col->CopyTo(_array, 0);
				}

				Stack(int initialCapacity)
				{
					sassert(initialCapacity >= 0, "");

					if (initialCapacity < _defaultCapacity)
						initialCapacity = _defaultCapacity;

					_bottom = new T[initialCapacity];
					_size = 0;
					_version = 0;
				}

				virtual ~Stack()
				{
					delete[] _array;
				}

				// Removes all objects from the System::Collections::Generic::Stack<T>.
				virtual void Clear()
				{
					Array::Clear(_array, 0, _size);
					_size = 0;
					_version++;
				}

				// Determines whether an element is in the System::Collections::Generic::Stack<T>.
				//	item
				//		The object to locate in the System::Collections::Generic::Stack<T>. The value can be null for reference types.
				//	Returns
				//		true if item is found in the System::Collections::Generic::Stack<T>; otherwise, false.
				virtual bool Contains(const T& item)
				{
					int index = _size;
					EqualityComparer<T> comparer = EqualityComparer<T>::Default();
					while (index-- > 0)
					{
						if (comparer.Equals(_array[index], item))
							return true;
					}
					return false;
				}
				
				virtual void CopyTo(T array[], const int index)
				{
					sassert(array != null, String::Format("array; %s", FrameworkResources::ArgumentNull_Generic));

					Array::Copy(_array, 0, array, index, _size);
					Array::Reverse(_array, index, _size);
				}

				// Returns the object at the top of the System::Collections::Generic::Stack<T> without removing it.
				//	Returns
				//		The object at the top of the System::Collections::Generic::Stack<T>.
				virtual T& Peek();
				{
					sassert(size != 0, "");

					return _array[_size - 1];
				}

				// Removes and returns the object at the top of the System::Collections::Generic::Stack<T>.
				//	Returns
				//		The object removed from the top of the System::Collections::Generic::Stack<T>.
				virtual T& Pop()
				{
					sassert(size != 0, "");

					_version++;
					T local = _array[--_size];
					_array[_size] = NULL;
					
					return local;
				}

				// Inserts an object at the top of the System::Collections::Generic::Stack<T>.
				//	item
				//		The object to push onto the System::Collections::Generic::Stack<T>. The value can be null for reference types.
				virtual void Push(T& obj)
				{
					_array[_size] = obj;
					_size++;
					_version++;
				}

				// Copies the System::Collections::Generic::Stack<T> to a new array.
				//	Returns
				//		A new array containing copies of the elements of the System::Collections::Generic::Stack<T>.
				virtual T* ToArray()
				{
					T[] localArray = new T[_size];

					for (int i = 0; i < _size; i++)
					{
						localArray[i] = _array[(_size - i) - 1];
					}
					return localArray;
				}

				// Sets the capacity to the actual number of elements in the System.Collections.Generic.Stack<T1>, if that number is less than 90 percent of current capacity.
				virtual void TrimExcess()
				{
				}
			};
		}
	}
}

#endif //_SYSTEM_COLLECTIONS_GENERIC_STACK_
