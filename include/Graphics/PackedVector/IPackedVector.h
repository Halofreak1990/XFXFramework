/********************************************************
 *	IPackedVector.h										*
 *														*
 *	XFX IPackedVector definition file					*
 *	Copyright © XFX Team. All Rights Reserved			*
 ********************************************************/
#ifndef _IPACKEDVECTOR_
#define _IPACKEDVECTOR_

#include "../../System.h"

namespace XFX
{
	class Vector4;
	
	namespace Graphics
	{
		namespace PackedVector
		{
			/// <summary>
			/// 
			/// </summary>
			interface IPackedVector_
			{
				public:
					virtual void PackFromVector4(Vector4 &vector) = 0;
					virtual Vector4 ToVector4() = 0;
			};
			
			/// <summary>
			/// 
			/// </summary>
			template<class TPacked>
			interface IPackedVector : virtual public IPackedVector_
			{
				public:
					virtual TPacked PackedValue() = 0;
					virtual void PackedValue(TPacked value) = 0;
			};
		}
	}
}

#endif //_IPACKEDVECTOR_
