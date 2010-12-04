/********************************************************
 *	Plane.h												*
 *														*
 *	XFX Plane definition file							*
 *	Copyright © XFX Team. All Rights Reserved			*
 ********************************************************/
#ifndef _XFX_PLANE_
#define _XFX_PLANE_

#include <System/Types.h>
#include "Enums.h"
#include "Vector3.h"

namespace XFX
{
	struct BoundingBox;
	struct BoundingSphere;
	struct Matrix;
	struct Quaternion;
	struct Vector4;
	
	/// <summary>
	/// Defines a plane.
	/// <summary>
	struct Plane
	{
	public:
		float D;
		Vector3 Normal;

		Plane(float a, float b, float c, float d);
		Plane(Vector3 normal, float d);
		Plane(Vector3 point1, Vector3 point2, Vector3 point3);
		Plane(Vector4 value);
		Plane(const Plane &obj);
		Plane();

		float Dot(Vector4 value);
		void Dot(Vector4 value, out float result);
		float DotCoordinate(Vector3 value);
		void DotCoordinate(Vector3 value, out float result);
		float DotNormal(Vector3 value);
		void DotNormal(Vector3 value, out float result);
		bool Equals(const Plane obj);
		int GetHashCode();
		PlaneIntersectionType_t Intersects(BoundingBox boundingbox);
		void Intersects(BoundingBox boundingbox, out PlaneIntersectionType_t result);
		PlaneIntersectionType_t Intersects(BoundingSphere sphere);
		void Intersects(BoundingSphere sphere, out PlaneIntersectionType_t result);
		void Normalize();
		Plane Normalize(Plane plane);
		void Normalize(Plane plane, out Plane result);
		static Plane Transform(Plane plane, Matrix matrix);
		static void Transform(Plane plane, Matrix matrix, out Plane result);
		static Plane Transform(Plane plane, Quaternion quaternion);
		static void Transform(Plane plane, Quaternion quaternion, out Plane result);
		
		
		bool operator==(const Plane other);
		bool operator!=(const Plane other);
		Plane operator=(const Plane other);
	};
}

#endif //_XFX_PLANE_
