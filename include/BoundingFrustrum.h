/********************************************************
 *	BoundingFrustrum.h									*
 *														*
 *	XFX BoundingFrustrum definition file				*
 *	Copyright © XFX Team. All Rights Reserved			*
 ********************************************************/
#ifndef _XFX_BOUNDINGFRUSTRUM_
#define _XFX_BOUNDINGFRUSTRUM_

#include "Enums.h"
#include "Matrix.h"
#include "Plane.h"
#include <System/Object.h>
#include <System/Types.h>

using namespace System;

namespace XFX
{
	struct BoundingBox;
	struct BoundingSphere;
	struct Ray;
	struct Vector3;

	// Defines a frustum and helps determine whether forms intersect with it.
	class BoundingFrustrum : virtual Object
	{
	private:
		static const int BottomPlaneIndex;
		Vector3 cornerArray[8];
		static const int FarPlaneIndex;
		static const int LeftPlaneIndex;
		Matrix matrix;
		static const int NearPlaneIndex;
		static const int NumPlanes;
		Plane planes[6];
		static const int RightPlaneIndex;
		static const int TopPlaneIndex;

		static Vector3 ComputeIntersection(Plane plane, Ray ray);
		static Ray ComputeIntersectionLine(Plane p1, Plane p2);
		void SetMatrix(Matrix value);
		void SupportMapping(Vector3 v, out Vector3 result);

	public:
		Plane Bottom();
		static const int CornerCount;
		Plane Far();
		Plane Left();
		Matrix Matrix_();
		void Matrix_(Matrix value);
		Plane Near();
		Plane Right();
		Plane Top();

		BoundingFrustrum();
		BoundingFrustrum(Matrix value);
		BoundingFrustrum(const BoundingFrustrum &obj); // copy constructor

		ContainmentType_t Contains(BoundingBox box);
		ContainmentType_t Contains(BoundingFrustrum frustrum);
		ContainmentType_t Contains(BoundingSphere sphere);
		ContainmentType_t Contains(Vector3 point);
		void Contains(BoundingBox box, out ContainmentType_t result);
		void Contains(BoundingSphere sphere, out ContainmentType_t result);
		void Contains(Vector3 point, out ContainmentType_t result);
		bool Equals(BoundingFrustrum other);
		Vector3* GetCorners();
		void GetCorners(Vector3 corners[]);
		int GetHashCode();
		bool Intersects(BoundingBox box);
		bool Intersects(BoundingFrustrum frustrum);
		bool Intersects(BoundingSphere sphere);
		PlaneIntersectionType_t Intersects(Plane plane);
		float Intersects(Ray ray);
		void Intersects(BoundingBox box, out bool result);
		void Intersects(BoundingSphere sphere, out bool result);
		void Intersects(Plane plane, out PlaneIntersectionType_t result);
		void Intersects(Ray ray, out float result);

		bool operator==(BoundingFrustrum other);
		bool operator!=(BoundingFrustrum other);
	};
}

#endif //_XFX_BOUNDINGFRUSTRUM_
