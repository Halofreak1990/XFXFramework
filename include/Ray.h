/********************************************************
 *	Ray.h												*
 *														*
 *	XFX Ray definition file								*
 *	Copyright © XFX Team. All Rights Reserved			*
 ********************************************************/
#ifndef _XFX_RAY_
#define _XFX_RAY_

#include <System/Interfaces.h>
#include <System/Object.h>

using namespace System;

namespace XFX
{
	struct BoundingBox;
	struct BoundingSphere;
	struct Plane;
	struct Vector3;
	
	// Defines a ray.
	struct Ray : IEquatable<Ray>, Object
	{
		Vector3 Direction;
		Vector3 Position;

		Ray(const Vector3 direction, const Vector3 position);
		Ray(const Ray &obj);
		Ray();
		
		bool Equals(const Object* obj) const;
		bool Equals(const Ray other) const;
		int GetHashCode() const;
		int GetType() const;
		float Intersects(const BoundingBox boundingbox) const;
		void Intersects(const BoundingBox boundingbox, out float result) const;
		float Intersects(const BoundingSphere sphere) const;
		void Intersects(const BoundingSphere sphere, out float result) const;
		float Intersects(const Plane plane) const;
		void Intersects(const Plane plane, out float result) const;
		const char* ToString() const;
		
		bool operator==(const Ray& right) const;
		bool operator!=(const Ray& right) const;
	};
}

#endif //_XFX_RAY_
