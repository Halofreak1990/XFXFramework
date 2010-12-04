/********************************************************
 *	List.h												*
 *														*
 *	XFX Generic List definition file					*
 *	Copyright © XFX Team. All Rights Reserved			*
 ********************************************************/
#ifndef _SYSTEM_COLLECTIONS_GENERIC_LIST_
#define _SYSTEM_COLLECTIONS_GENERIC_LIST_

#include <System/Types.h>
#include "Interfaces.h"

namespace System
{
	namespace Collections
	{
		namespace Generic
		{
			/// <summary>
			/// Represents a strongly typed list of objects that can be accessed by index. Provides methods to search, sort, and manipulate lists.
			/// </summary>
			template <class T>
			class List : public IList<T>
			{
			private:
				static const int _defaultCapacity = 4;
				static T _emptyArray[];
				T _items[];
				int _size;
				int _version;

				void EnsureCapacity(int min);

			public:	
				int Count();
				int Capacity(); // get
				void Capacity(int newCap); // set

 				List();
				List(int capacity);
				~List();

 				void Add(T item);						//Adds an element to the end of the list
				int BinarySearch(T item);
				int BinarySearch(T item, IComparer<T> comparer);
				int BinarySearch(int index, int count, T item, IComparer<T> comparer);
 				void Clear();							//Removes all elements from the list
				bool Contains(T item);
				void CopyTo(T array[], int arrayIndex);
				int First();                 			//Goes to the first element in the list
 				int First(out T item);   				//Goes to the first element returns the value
 				void ForEach(char* action);				//Executes the specified action on each element in the list
				int IndexOf(T item);
				void Insert(int index, T item);
 				int Next();          					//Goes to next element in the list
				int Next(out T item);   				//Goes to next element and writes the element in parameter
 				int Change(const T newElem);   			//changes the current element
 				bool Remove(T item);  					//Removes current element
				void RemoveAt(int index);
 				void RemoveRange(int index, int count);
				void Reverse();
				void Reverse(int index, int count);
				T *ToArray();
				void TrimExcess();

				T operator[](int index);
			};
		}
	}
}

#endif //_SYSTEM_COLLECTIONS_GENERIC_LIST_
