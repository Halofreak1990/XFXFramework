#ifndef _IPACKEDVECTOR_
#define _IPACKEDVECTOR_

#include <System.h>
#include "TPacked.h"
#include "Vector4.h"

using namespace XFX;

namespace XFX
{
	namespace Graphics
	{
		namespace PackedVector
		{
			interface IPackedVector
			{
				public:
					void PackFromVector4(Vector4 &vector); 
         			Vector4 ToVector4(); 
			};
			
			template <class T>
			interface IPackedVector<T> : IPackedVector
			{
				public:
					TPacked PackedValue;
			};
		}
	}
}

#endif //_IPACKEDVECTOR_
