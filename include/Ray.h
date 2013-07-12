/*****************************************************************************
 *	Ray.h																	 *
 *																			 *
 *	XFX::Ray definition file												 *
 *	Copyright (c) XFX Team. All Rights Reserved 							 *
 *****************************************************************************/
#ifndef _XFX_RAY_
#define _XFX_RAY_

#include <System/Interfaces.h>

using namespace System;

namespace XFX
{
	struct BoundingBox;
	struct BoundingSphere;
	struct Plane;
	struct Vector3;
	
	/**
	 * Defines a ray.
	 */
	struct Ray : IEquatable<Ray>, Object
	{
		Vector3 Direction;
		Vector3 Position;

		Ray(const Vector3 direction, const Vector3 position);
		Ray(const Ray &obj);
		Ray();
		
		bool Equals(Object const * const obj) const;
		bool Equals(const Ray other) const;
		int GetHashCode() const;
		static const Type& GetType();
		float Intersects(BoundingBox boundingbox) const;
		void Intersects(BoundingBox boundingbox, out float& result) const;
		float Intersects(BoundingSphere sphere) const;
		void Intersects(BoundingSphere sphere, out float& result) const;
		float Intersects(Plane plane) const;
		void Intersects(Plane plane, out float& result) const;
		const String ToString() const;
		
		bool operator==(const Ray& right) const;
		bool operator!=(const Ray& right) const;
	};
}

#endif //_XFX_RAY_
