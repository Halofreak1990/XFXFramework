/*****************************************************************************
 *	Plane.h 																 *
 *																			 *
 *	XFX::Plane structure definition file									 *
 *	Copyright (c) XFX Team. All Rights Reserved 							 *
 *****************************************************************************/
#ifndef _XFX_PLANE_
#define _XFX_PLANE_

#include <System/Types.h>
#include "Enums.h"
#include "Vector3.h"

using namespace System;

namespace XFX
{
	struct BoundingBox;
	struct BoundingSphere;
	struct Matrix;
	struct Quaternion;
	struct Vector4;
	
	/**
	 * Defines a plane.
	 */
	struct Plane : IEquatable<Plane>, Object
	{
		float D;
		Vector3 Normal;

		Plane(const float a, const float b, const float c, const float d);
		Plane(const Vector3 normal, const float d);
		Plane(const Vector3 point1, const Vector3 point2, const Vector3 point3);
		Plane(const Vector4 value);
		Plane(const Plane &obj);
		Plane();

		float	Dot(const Vector4 value) const;
		void	Dot(const Vector4 value, out float& result) const;
		float	DotCoordinate(const Vector3 value) const;
		void	DotCoordinate(const Vector3 value, out float& result) const;
		float	DotNormal(const Vector3 value) const;
		void	DotNormal(const Vector3 value, out float& result) const;
		bool	Equals(Object const * const obj) const;
		bool	Equals(const Plane obj) const;
		int 	GetHashCode() const;
		static const Type& GetType();
		PlaneIntersectionType_t Intersects(const BoundingBox boundingbox) const;
		void	Intersects(const BoundingBox boundingbox, out PlaneIntersectionType_t& result) const;
		PlaneIntersectionType_t Intersects(const BoundingSphere sphere) const;
		void	Intersects(const BoundingSphere sphere, out PlaneIntersectionType_t& result) const;
		void	Normalize();
		static Plane Normalize(const Plane plane);
		static void Normalize(const Plane plane, out Plane& result);
		const String ToString() const;
		static Plane Transform(const Plane plane, const Matrix matrix);
		static void Transform(const Plane plane, const Matrix matrix, out Plane& result);
		static Plane Transform(const Plane plane, const Quaternion quaternion);
		static void Transform(const Plane plane, const Quaternion quaternion, out Plane& result);
		
		bool operator==(const Plane& other) const;
		bool operator!=(const Plane& other) const;
	};
}

#endif //_XFX_PLANE_
