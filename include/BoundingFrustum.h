/********************************************************
 *	BoundingFrustum.h									*
 *														*
 *	XFX BoundingFrustum definition file				*
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
	class BoundingFrustum : public IEquatable<BoundingFrustum>, public Object
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
		Matrix getMatrix();
		void setMatrix(Matrix value);
		Plane Near();
		Plane Right();
		Plane Top();

		BoundingFrustum();
		BoundingFrustum(Matrix value);
		BoundingFrustum(const BoundingFrustum &obj); // copy constructor

		ContainmentType_t Contains(BoundingBox box);
		ContainmentType_t Contains(BoundingFrustum frustrum);
		ContainmentType_t Contains(BoundingSphere sphere);
		ContainmentType_t Contains(Vector3 point);
		void Contains(BoundingBox box, out ContainmentType_t result);
		void Contains(BoundingSphere sphere, out ContainmentType_t result);
		void Contains(Vector3 point, out ContainmentType_t result);
		bool Equals(Object const * const obj) const;
		bool Equals(const BoundingFrustum other) const;
		Vector3* GetCorners();
		void GetCorners(Vector3 corners[]);
		int GetHashCode() const;
		int GetType() const;
		bool Intersects(BoundingBox box);
		bool Intersects(BoundingFrustum frustrum);
		bool Intersects(BoundingSphere sphere);
		PlaneIntersectionType_t Intersects(Plane plane);
		float Intersects(Ray ray);
		void Intersects(BoundingBox box, out bool result);
		void Intersects(BoundingSphere sphere, out bool result);
		void Intersects(Plane plane, out PlaneIntersectionType_t result);
		void Intersects(Ray ray, out float result);
		const char* ToString() const;

		bool operator==(const BoundingFrustum& other) const;
		bool operator!=(const BoundingFrustum& other) const;
	};
}

#endif //_XFX_BOUNDINGFRUSTRUM_
