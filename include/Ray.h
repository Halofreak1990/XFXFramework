/********************************************************
 *	Ray.h												*
 *														*
 *	XFX Ray definition file								*
 *	Copyright © XFX Team. All Rights Reserved			*
 ********************************************************/
#ifndef _XFX_RAY_
#define _XFX_RAY_

#include <System/Types.h>

namespace XFX
{
	struct BoundingBox;
	struct BoundingSphere;
	struct Plane;
	struct Vector3;
	
	/// <summary>
	/// Defines a ray.
	/// </summary>
	class Ray
	{
	public:
		Vector3 Direction;
		Vector3 Position;

		Ray(Vector3 direction, Vector3 position);
		Ray(const Ray &obj);
		Ray();
		
		bool Equals(Ray obj);
		int GetHashCode();
		float Intersects(BoundingBox boundingbox);
		void Intersects(BoundingBox boundingbox, out float result);
		float Intersects(BoundingSphere sphere);
		void Intersects(BoundingSphere sphere, out float result);
		float Intersects(Plane plane);
		void Intersects(Plane plane, out float result);
		
		bool operator==(const Ray other);
		bool operator!=(const Ray other);
		Ray operator=(const Ray other);
	};
}

#endif //_RAY_
