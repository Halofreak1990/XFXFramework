/********************************************************
 *	BoundingSphere.h									*
 *														*
 *	XFX BoundingSphere definition file					*
 *	Copyright © XFX Team. All Rights Reserved			*
 ********************************************************/
#ifndef _XFX_BOUNDINGSPHERE_
#define _XFX_BOUNDINGSPHERE_

#include <System/Types.h>
#include "Vector3.h"

namespace XFX
{
	/// <summary>
	/// Defines a sphere.
	/// </summary>
	class BoundingSphere
	{
	public:
		Vector3 Center;
		float Radius;
		
		BoundingSphere(Vector3 center, float radius);
		BoundingSphere(const BoundingSphere &obj);
		BoundingSphere();
		
		int operator==(const BoundingSphere other);
		int operator!=(const BoundingSphere other);
		BoundingSphere operator=(const BoundingSphere other);
	};
}

#endif //_XFX_BOUNDINGSPHERE_
