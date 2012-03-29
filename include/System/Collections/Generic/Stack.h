#ifndef _SYSTEM_COLLECTIONS_GENERIC_STACK_
#define _SYSTEM_COLLECTIONS_GENERIC_STACK_

#include <System/Array.h>
#include <System/Object.h>
#include <System/Collections/Generic/EqualityComparer.h>

#include <sassert.h>

namespace System
{
	namespace Collections
	{
		namespace Generic
		{
			template <class T>
			class Stack : public ICollection<T>, virtual Object
			{
			private:
				T* _array;
				static const int _defaultCapacity = 4;
				int _actualSize;
				int _size;
				int _version;

				void EnsureCapacity(int capacity)
				{
					// TODO: implement
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
					_bottom = new T[_defaultCapacity];
					_actualSize = _defaultCapacity;
					_size = 0;
					_version = 0;
				}

				Stack(ICollection<T>* col)
				{
					sassert(col != null, "");

					_array = new T[col->Count()];
					_actualSize = col->Count();

					for (int i = 0; i < col->Count(); i++)
					{
						this->Push(col[i]);
					}
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

				virtual void Clear()
				{
					Array::Clear(_array, 0, _size);
					_size = 0;
					_version++;
				}

				virtual bool Contains(T item)
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

				virtual void CopyTo(T array[], int index)
				{
					sassert(array != null, "");

					/*if ((arrayIndex < 0) || (arrayIndex > Array::Length(_array)))
						throw;*/

					Array::Copy(_array, 0, array, index, _size);
					Array::Reverse(_array, index, _size);
				}

				virtual T& Peek();
				{
					sassert(size != 0, "");

					return _array[_size - 1];
				}

				virtual T& Pop()
				{
					sassert(size != 0, "");

					_version++;
					T local = _array[--_size];
					_array[_size] = NULL;
					
					return local;
				}

				virtual void Push(T& obj)
				{
					_version++;
				}

				virtual T* ToArray()
				{
					T[] localArray = new T[_size];

					for (int i = 0; i < _size; i++)
					{
						localArray[i] = _array[(_size - i) - 1];
					}
					return localArray;
				}
			};
		}
	}
}

#endif //_SYSTEM_COLLECTIONS_GENERIC_STACK_
