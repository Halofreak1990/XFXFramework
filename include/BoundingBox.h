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
	struct BoundingBox
	{
	public:
		Vector3 Max;
		Vector3 Min;
		static const int CornerCount;
		
		BoundingBox(Vector3 min, Vector3 max);
		BoundingBox(const BoundingBox &obj);
		BoundingBox();

		ContainmentType_t Contains(BoundingBox box);
		void Contains(BoundingBox box, out ContainmentType_t result);
		ContainmentType_t Contains(BoundingSphere sphere);
		void Contains(BoundingSphere sphere, out ContainmentType_t result);
		ContainmentType_t Contains(Vector3 vector);
		void Contains(Vector3 vector, out ContainmentType_t result);
		static BoundingBox CreateFromPoints(Vector3 points[]);
		static BoundingBox CreateFromSphere(BoundingSphere sphere);
		static void CreateFromSphere(BoundingSphere sphere, out BoundingBox result);
		static BoundingBox CreateMerged(BoundingBox box1, BoundingBox box2);
		static void CreateMerged(BoundingBox box1, BoundingBox box2, out BoundingBox result);
		bool Equals(BoundingBox obj);
		int Intersects(BoundingBox box);
		void Intersects(BoundingBox box, out int result);
		int Intersects(BoundingSphere sphere);
		void Intersects(BoundingSphere sphere, out int result);
		PlaneIntersectionType_t Intersects(Plane plane);
		void Intersects(Plane plane, out PlaneIntersectionType_t result);
		float Intersects(Ray ray);
		void Intersects(Ray ray, out float distance);
		
		bool operator!=(const BoundingBox other);
		bool operator==(const BoundingBox other);
		BoundingBox operator=(const BoundingBox other);
	};
}

#endif //_XFX_BOUNDINGBOX_
