#ifndef _SYSTEM_COLLECTIONS_STACK_
#define _SYSTEM_COLLECTIONS_STACK_

#include <System/Object.h>
#include <System/Collections/Interfaces.h>

namespace System
{
	namespace Collections
	{
		class Stack : public ICollection, virtual Object
		{
		private:
			Object** _bottom;
			Object** _top;
			static const int _defaultCapacity;
			int _size;
			int _version;

		public:
			int Count();
			bool IsSynchronized();

			Stack();
			Stack(ICollection* col);
			Stack(int initialCapacity);
			virtual ~Stack();

			virtual void Clear();
			virtual bool Contains(Object* obj);
			virtual void CopyTo(Object* array[], int index);
			virtual Object* Peek();
			virtual Object* Pop();
			virtual void Push(Object* obj);
			virtual Object** ToArray();
		};
	}
}

#endif //_SYSTEM_COLLECTIONS_STACK_
