/********************************************************
 *	BoundingBox.h										*
 *														*
 *	XFX BoundingBox definition file						*
 *	Copyright © XFX Team. All Rights Reserved			*
 ********************************************************/
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

		ContainmentType_t Contains(const BoundingBox box) const;
		void Contains(const BoundingBox& box, out ContainmentType_t& result) const;
		ContainmentType_t Contains(const BoundingSphere sphere) const;
		void Contains(const BoundingSphere& sphere, out ContainmentType_t& result) const;
		ContainmentType_t Contains(const Vector3 vector) const;
		void Contains(const Vector3& vector, out ContainmentType_t& result) const;
		static BoundingBox CreateFromPoints(const Vector3 points[], const int startIndex, const int length);
		static BoundingBox CreateFromSphere(const BoundingSphere sphere);
		static void CreateFromSphere(const BoundingSphere& sphere, out BoundingBox& result);
		static BoundingBox CreateMerged(const BoundingBox box1, const BoundingBox box2);
		static void CreateMerged(const BoundingBox& box1, const BoundingBox& box2, out BoundingBox& result);
		bool Equals(const Object* obj) const;
		bool Equals(const BoundingBox obj) const;
		int GetHashCode() const;
		int GetType() const;
		bool Intersects(const BoundingBox box) const;
		void Intersects(const BoundingBox& box, out bool& result) const;
		bool Intersects(const BoundingSphere sphere) const;
		void Intersects(const BoundingSphere& sphere, out bool& result) const;
		PlaneIntersectionType_t Intersects(const Plane plane) const;
		void Intersects(const Plane& plane, out PlaneIntersectionType_t& result) const;
		float Intersects(const Ray ray) const;
		void Intersects(const Ray& ray, out float& distance) const;
		const char* ToString() const;
		
		bool operator!=(const BoundingBox& other) const;
		bool operator==(const BoundingBox& other) const;
	};
}

#endif //_XFX_BOUNDINGBOX_
