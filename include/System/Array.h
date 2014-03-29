/*****************************************************************************
 *	Array.h 																 *
 *																			 *
 *	XFX generic Array class definition file 								 *
 *	Contains array helper methods											 *
 *	Copyright (c) XFX Team. All Rights Reserved 							 *
 *****************************************************************************/
#ifndef _SYSTEM_ARRAY_
#define _SYSTEM_ARRAY_

#include "FrameworkResources.h"
#include <System/Collections/Generic/Interfaces.h>
#include <System/String.h>
#include <string.h>

#include <sassert.h>

using namespace System::Collections::Generic;

namespace System
{
	/**
	 * 
	 */
	template <typename T>
	class Array : public ICollection<T>, public IEnumerable<T>
	{
	private:
		T* _array;
		int _version;

		inline void swap(T& a, T&b)
		{
			T temp = a;
			a = b;
			b = temp;
		}

	public:
		const int Length;

		Array(const int size) : _array(new T[size]), _version(0), Length(size) { }
		Array(const Array<T> &obj)
			: _array(new T[obj.Length]), _version(obj._version), Length(obj.Length)
		{
			memcpy(_array, obj._array, sizeof(T) * Length);
		}

		~Array() { delete[] _array; }

		template <typename U>
		inline static void Clear(U array[], int startIndex, int count)
		{
			memset(&array[startIndex], 0, sizeof(U) * count);
		}

		inline void Clear()
		{
			Clear(_array, 0, Length);
		}

		inline bool Contains(const T item) const
		{
			return (IndexOf(item) != -1);
		}

		void CopyTo(T array[], const int index) const
		{
			sassert(array != null, String::Format("array; %s", FrameworkResources::ArgumentNull_Generic));

			for(int i = 0, j = index; i < Length; i++)
			{
				array[j] = _array[i];
			}
		}

		inline IEnumerator<T>* GetEnumerator() const
		{
			return new ArrayEnumerator(this);
		}

		int IndexOf(const T item) const
		{
			for (int i = 0; i < Length; i++)
			{
				if (i == item)
				{
					return i;
				}
			}

			return -1;
		}

		inline void Reverse()
		{
			Reverse(0, Length);
		}

		void Reverse(const int startIndex, const int count)
		{
			sassert((startIndex + count) < Length, "");

			int num = startIndex;
			int num2 = (startIndex + count) - 1;

			while (num < num2)
			{
				swap(_array[num], _array[num2]);
				num++;
				num2--;
			}

			_version++;
		}

		inline T& operator[](const int index)
		{
			return _array[index];
		}

	private:
		class ArrayEnumerator : public IEnumerator<T>
		{
		private:
			Array<T>* _array;
			int _position;
			int _version;

		public:
			ArrayEnumerator(Array<T> * const parent) : _array(parent), _position(0), _version(_array->_version) { }
			~ArrayEnumerator() { }

			T& Current() const
			{
				sassert(_version == _array->_version, "");

				return _array[_position];
			}

			bool MoveNext()
			{
				sassert(_version == _array->_version, "");

				return _position++ < _array->Length;
			}

			void Reset()
			{
				sassert(_version == _array->_version, "");

				_position = -1;
			}
		};
	};

	//////////////////////////////////////////////////////////////////////////////

	template <typename T>
	class Array<T *> : public ICollection<T *>, public IEnumerable<T *>
	{
	private:
		T** _array;
		int _version;

		inline void swap(T * a, T * b)
		{
			T* temp = a;
			a = b;
			b = temp;
		}

	public:
		const int Length;

		Array(const int size) : _array(new T*[size]), _version(0), Length(size) { }
		Array(const Array<T *> &obj)
			: _array(new T*[obj.Length]), _version(obj._version), Length(obj.Length)
		{
			for (int i = 0; i < Length; i++)
			{
				_array[i] = obj._array[i];
			}
		}

		~Array() { delete _array; }

		inline void Clear()
		{
			memset(_array, 0, sizeof(T *) * Length);
		}

		inline bool Contains(const T* item) const
		{
			return (IndexOf(item) != -1);
		}

		void CopyTo(T* array[], const int index) const
		{
			sassert(array != null, String::Format("array; %s", FrameworkResources::ArgumentNull_Generic));

			for(int i = 0, j = index; i < Length; i++)
			{
				array[j] = _array[i];
			}
		}

		inline IEnumerator<T *>* GetEnumerator() const
		{
			return new ArrayEnumerator(this);
		}

		int IndexOf(const T* item) const
		{
			for(int i = 0; i < Length; i++)
			{
				if (_array[i] == item)
				{
					return i;
				}
			}

			return -1;
		}

		inline void Reverse()
		{
			Reverse(0, Length);
		}

		void Reverse(const int startIndex, const int count)
		{
			sassert((startIndex + count) < Length, "");

			int num = startIndex;
			int num2 = (startIndex + count) - 1;
			while (num < num2)
			{
				swap(_array[num], _array[num2]);
				num++;
				num2--;
			}

			_version++;
		}

		inline T* operator[](const int index)
		{
			return _array[index];
		}

	private:
		class ArrayEnumerator : public IEnumerator<T *>
		{
		private:
			Array<T *>* _array;
			int _position;
			int _version;

		public:
			ArrayEnumerator(Array<T> * const parent) : _array(parent), _position(0), _version(parent->_version) { }
			~ArrayEnumerator() { }

			T& Current() const
			{
				sassert(_version == _array->_version, "");

				return *_array[_position];
			}

			bool MoveNext()
			{
				sassert(_version == _array->_version, "");

				return _position++ < _array->Length;
			}

			void Reset()
			{
				sassert(_version == _array->_version, "");

				_position = -1;
			}
		};
	};

	/*template <typename T>
	void Array::Reverse(T array[], const int index, const int length)
	{
		sassert(array != null, String::Format("array; %s", FrameworkResources::ArgumentNull_Generic));

		int num = index;
		int num2 = (index + length) - 1;
		while (num < num2)
		{
			T obj2 = array[num];
			array[num] = array[num2];
			array[num2] = obj2;
			num++;
			num2--;
		}
	}*/
}

#endif //_SYSTEM_ARRAY_
