/********************************************************
 *	IPackedVector.h										*
 *														*
 *	XFX IPackedVector definition file					*
 *	Copyright © XFX Team. All Rights Reserved			*
 ********************************************************/
#ifndef _XFX_GRAPHICS_PACKEDVECTOR_IPACKEDVECTOR_
#define _XFX_GRAPHICS_PACKEDVECTOR_IPACKEDVECTOR_

#include <System/Types.h>

namespace XFX
{
	struct Vector4;
	
	namespace Graphics
	{
		namespace PackedVector
		{
			interface IPackedVector_
			{
			public:
				virtual void PackFromVector4(Vector4 &vector) = 0;
				virtual Vector4 ToVector4() = 0;
			};
			
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

#endif //_XFX_GRAPHICS_PACKEDVECTOR_IPACKEDVECTOR_
