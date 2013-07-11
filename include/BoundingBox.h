/*****************************************************************************
 *	BoundingBox.h															 *
 *																			 *
 *	XFX BoundingBox definition file											 *
 *	Copyright (c) XFX Team. All Rights Reserved 							 *
 *****************************************************************************/
#ifndef _XFX_BOUNDINGBOX_
#define _XFX_BOUNDINGBOX_

#include <System/Types.h>
#include "Enums.h"
#include "Vector3.h"

namespace XFX
{
	struct BoundingSphere;
	struct Plane;
	struct Ray;

	// Defines an axis-aligned box-shaped 3D volume.
	struct BoundingBox : IEquatable<BoundingBox>, Object
	{
	public:
		Vector3 Max;
		Vector3 Min;
		static const int CornerCount;
		
		BoundingBox(const Vector3 min, const Vector3 max);
		BoundingBox(const BoundingBox &obj);
		BoundingBox();

		ContainmentType_t Contains(BoundingBox box) const;
		void Contains(BoundingBox box, out ContainmentType_t& result) const;
		ContainmentType_t Contains(BoundingSphere sphere) const;
		void Contains(BoundingSphere sphere, out ContainmentType_t& result) const;
		ContainmentType_t Contains(Vector3 vector) const;
		void Contains(Vector3 vector, out ContainmentType_t& result) const;
		static BoundingBox CreateFromPoints(Vector3 points[], int startIndex, int length);
		static BoundingBox CreateFromSphere(BoundingSphere sphere);
		static void CreateFromSphere(BoundingSphere sphere, out BoundingBox& result);
		static BoundingBox CreateMerged(BoundingBox box1, BoundingBox box2);
		static void CreateMerged(BoundingBox box1, BoundingBox box2, out BoundingBox& result);
		bool Equals(Object const * const obj) const;
		bool Equals(const BoundingBox obj) const;
		int GetHashCode() const;
		static int GetType();
		bool Intersects(BoundingBox box) const;
		void Intersects(BoundingBox box, out bool& result) const;
		bool Intersects(BoundingSphere sphere) const;
		void Intersects(BoundingSphere sphere, out bool& result) const;
		PlaneIntersectionType_t Intersects(Plane plane) const;
		void Intersects(Plane plane, out PlaneIntersectionType_t& result) const;
		float Intersects(Ray ray) const;
		void Intersects(Ray ray, out float& distance) const;
		const String ToString() const;
		
		bool operator!=(const BoundingBox& other) const;
		bool operator==(const BoundingBox& other) const;
	};
}

#endif //_XFX_BOUNDINGBOX_
