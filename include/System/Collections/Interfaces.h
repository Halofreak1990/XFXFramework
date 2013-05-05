#ifndef _SYSTEM_COLLECTIONS_INTERFACES_
#define _SYSTEM_COLLECTIONS_INTERFACES_

#include <System/Object.h>
#include <System/Types.h>

namespace System
{
	namespace Collections
	{
		interface ICollection
		{
		public:
			virtual void CopyTo(Object** array, int index)=0;

			virtual int Count()=0;
			virtual bool IsSynchronized()=0;
		};
	}
}

#endif //_SYSTEM_COLLECTIONS_INTERFACES_
