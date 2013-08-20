#ifndef _SYSTEM_COLLECTIONS_GENERIC_QUEUE_
#define _SYSTEM_COLLECTIONS_GENERIC_QUEUE_

#include "Interfaces.h"

#include <sassert.h>

namespace System
{
	namespace Collections
	{
		namespace Generic
		{
			/**
			 * Represents a first-in, first-out collection of objects.
			 */
			template <typename T>
			class Queue : public ICollection<T>, public IEnumerable<T>, public Object
			{
			private:
				T* _array;
				int _actualSize;
				static const int _defaultCapacity = 4;
				static const int _growFactor = 200;
				int _head;
				static const int _minimumGrow = 4;
				static const int _shrinkThreshold = 0x20;
				int _size;
				int _tail;
				int _version;

				void Add(const T& item) { }
				bool Remove(const T& item) { return false; }

			public:
				int Count() const;
				bool IsReadOnly() const;

				Queue();
				Queue(IEnumerable<T> * const collection);
				Queue(const int capacity);

				void Clear();
				bool Contains(const T& item) const;
				void CopyTo(T array[], const int index) const;
				T& Dequeue();
				void Enqueue(const T& item);
				IEnumerator<T>* GetEnumerator();
				int GetType() const;
				T& Peek();
				T* ToArray() const;
				void TrimExcess();

			private:
				class QueueEnumerator : public IEnumerator<T>
				{
				private:
					int position;
					Queue<T>* _parent;
					int version;

				public:
					QueueEnumerator(Queue<T> * const queue);

					T& Current() const;
					bool MoveNext();
					void Reset();
				};
			};

			////////////////////////////////////////////////////////////////////////////

			template <typename T>
			int Queue<T>::Count() const
			{
				return _size;
			}

			template <typename T>
			bool Queue<T>::IsReadOnly() const
			{
				return false;
			}

			template <typename T>
			Queue<T>::Queue()
				: _array(new T[_defaultCapacity]), _size(0), _version(0)
			{
			}

			template <typename T>
			Queue<T>::Queue(IEnumerable<T> * const collection)
				: _array(new T[_defaultCapacity]), _size(0), _version(0)
			{
				sassert(collection != null, "");

				IEnumerator<T>* enumerator = collection->GetEnumerator();
				enumerator->Reset();

				while(enumerator->MoveNext())
				{
					this->Enqueue(enumerator->Current());
				}

				delete enumerator;
			}

			template <typename T>
			Queue<T>::Queue(const int capacity)
				: _array(new T[capacity]), _size(0), _version(0)
			{
			}

			template <typename T>
			void Queue<T>::Clear()
			{
				if (this->_head < this->_tail)
				{
					for (int i = this->_head; i < this->_size; i++)
					{
						this->_array = null;
					}
				}
				else
				{
					for (int i = this->_head; i < (this->_actualSize - this->_head))
					{
						this->_array[i] = null;
					}

					for (int i = 0; i < this->_tail; i++)
					{
						this->_array[i] = null;
					}
				}
				this->_head = 0;
				this->_tail = 0;
				this->_size = 0;
				this->_version++;
			}

			template <typename T>
			bool Queue<T>::Contains(const T& item) const
			{
				int index = this->_head;
				int num2 = this->_size;

				while(num2-- > 0)
				{
					if (item == null)
					{
						if (this->_array[index] == null)
						{
							return true;
						}
					}
					else if ((this->_array[index]
				}
			}

			template <typename T>
			void Queue<T>::CopyTo(T array[], const int index) const
			{

			}

			template <typename T>
			IEnumerator<T>* Queue<T>::GetEnumerator() const
			{
				return new QueueEnumerator(this);
			}

			template <typename T>
			Queue<T>::QueueEnumerator::QueueEnumerator(Queue<T> * const queue)
				: position(0), _parent(queue), version(queue->_version)
			{
			}

			template <typename T>
			void Queue<T>::Enqueue(const T& item)
			{

			}

			template <typename T>
			T& Queue<T>::QueueEnumerator::Current() const
			{
				sassert(version == _parent->_version, "");

				return _parent->_array[position];
			}

			template <typename T>
			bool Queue<T>::QueueEnumerator::MoveNext()
			{
				sassert(version == _parent->_version, "");

				if (position < _parent->_size)
				{
					position++;
					return true;
				}
				return false;
			}

			template <typename T>
			void Queue<T>::QueueEnumerator::Reset()
			{
				sassert(version == _parent->_version, "");

				position = -1;
			}
		}
	}
}

#endif //_SYSTEM_COLLECTIONS_GENERIC_QUEUE_
