#ifndef _ILIST_
#define _ILIST_

#include "../System/Types.h"

using namespace System;

namespace System
{
	namespace Collections
	{
		interface IList : virtual ICollection, virtual IEnumerable
		{
		public:
			virtual int IsFixedSize();
			virtual int IsReadOnly();
		
			virtual void Clear();
			virtual void RemoveAt();
		};
	}
}

#endif //_ILIST_
