/*****************************************************************************
 *	BoundingSphere.h														 *
 *																			 *
 *	XFX BoundingSphere definition file										 *
 *	Copyright (c) XFX Team. All Rights Reserved 							 *
 *****************************************************************************/
#ifndef _XFX_BOUNDINGSPHERE_
#define _XFX_BOUNDINGSPHERE_

#include <System/Interfaces.h>
#include "Vector3.h"

using namespace System;

namespace XFX
{
	// Defines a sphere.
	struct BoundingSphere : IEquatable<BoundingSphere>, Object
	{
		Vector3 Center;
		float Radius;
		
		BoundingSphere(const Vector3 center, const float radius);
		BoundingSphere(const BoundingSphere &obj);
		BoundingSphere();

		bool Equals(Object const * const obj) const;
		bool Equals(const BoundingSphere other) const;
		int GetHashCode() const;
		int GetType() const;
		const String& ToString() const;
		
		bool operator==(const BoundingSphere& other) const;
		bool operator!=(const BoundingSphere& other) const;
	};
}

#endif //_XFX_BOUNDINGSPHERE_
