#ifndef _STACK_
#define _STACK_

#include "ICollection.h"
#include "IEnumerable.h"

using namespace System;

namespace System
{
	namespace Collections
	{
		namespace Generic
		{
			template <class T>
			class Stack : virtual IEnumerable<T>, virtual System::Collections::ICollection
			{
				private:
					T internalArray[];
					
				public:
					struct Enumerator;
				
					Stack();
					Stack(IEnumerable<T> collection);
					Stack(int capacity);
					
					int Count();
					
					void Clear();
					int Contains(T item);
					void CopyTo(T array[], int arrayIndex);
					T Peek();
					T Pop();
					void Push(T item);
					T *ToArray();
					void TrimExcess();
			};
		}
	}
}

#endif //_LIST_
