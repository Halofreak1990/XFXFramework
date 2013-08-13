/*****************************************************************************
 *	Vector2.h																 *
 *																			 *
 *	XFX Vector2 definition file 											 *
 *	Copyright (c) XFX Team. All Rights Reserved 							 *
 *****************************************************************************/
#ifndef _XFX_VECTOR2_
#define _XFX_VECTOR2_

#include <System/Interfaces.h>

using namespace System;

namespace XFX
{
	struct Matrix;
	struct Quaternion;
	
	// Defines a vector with two components.
	struct Vector2 : IEquatable<Vector2>, Object
	{
		static const Vector2 One;
		float X, Y;
		static const Vector2 Zero;

		Vector2(const float x, const float y);
		Vector2(const float value);
		Vector2(const Vector2 &obj);
		Vector2();

		static Vector2	Add(const Vector2 value1, const Vector2 value2);
		static void 	Add(const Vector2& value1, const Vector2& value2, out Vector2& result);
		static Vector2	Baricentric(const Vector2 value1, const Vector2 value2, const Vector2 value3, const float amount1, const float amount2);
		static void 	Baricentric(const Vector2& value1, const Vector2& value2, const Vector2& value3, const float amount1, const float amount2, out Vector2& result);
		static Vector2	CatmullRom(const Vector2 value1, const Vector2 value2, const Vector2 value3, const Vector2 value4, const float amount);
		static void 	CatmullRom(const Vector2& value1, const Vector2& value2, const Vector2& value3, const Vector2& value4, const float amount, out Vector2& result);
		static Vector2	Clamp(const Vector2 value, const Vector2 min, const Vector2 max);
		static void 	Clamp(const Vector2& value, const Vector2& min, const Vector2& max, out Vector2& result);
		static float	Distance(const Vector2 value1, const Vector2 value2);
		static void 	Distance(const Vector2& value1, const Vector2& value2, out float& result);
		static float	DistanceSquared(const Vector2 value1, const Vector2 value2);
		static void 	DistanceSquared(const Vector2& value1, const Vector2& value2, out float& result);
		static Vector2	Divide(const Vector2 value1, const float divider);
		static void 	Divide(const Vector2& value1, const float divider, out Vector2& result);
		static Vector2	Divide(const Vector2 value1, const Vector2 value2);
		static void 	Divide(const Vector2& value1, const Vector2& value2, out Vector2& result);
		static float	Dot(const Vector2 value1, const Vector2 value2);
		static void 	Dot(const Vector2& value1, const Vector2& value2, out float& result);
		bool			Equals(Object const * const obj) const;
		bool			Equals(const Vector2 other) const;
		int 			GetHashCode() const;
		static const Type&	GetType();
		static Vector2	Hermite(const Vector2 value1, const Vector2 tangent1, const Vector2 value2, const Vector2 tangent2, const float amount);
		static void 	Hermite(const Vector2& value1, const Vector2& tangent1, const Vector2& value2, const Vector2& tangent2, const float amount, out Vector2& result);
		float			Length() const;
		float			LengthSquared() const;
		static Vector2	Lerp(const Vector2 value1, const Vector2 value2, const float amount);
		static void 	Lerp(const Vector2& value1, const Vector2& value2, const float amount, out Vector2& result);
		static Vector2	Max(const Vector2 value1, const Vector2 value2);
		static void 	Max(const Vector2& value1, const Vector2& value2, out Vector2& result);
		static Vector2	Min(const Vector2 value1, const Vector2 value2);
		static void 	Min(const Vector2& value1, const Vector2& value2, out Vector2& result);
		static Vector2	Multiply(const Vector2 value, const float scaleFactor);
		void			Multiply(const Vector2& value1, const float scaleFactor, out Vector2& result);
		static Vector2	Multiply(const Vector2 value1, const Vector2 value2);
		void			Multiply(const Vector2& value1, const Vector2& value2, out Vector2& result);
		static Vector2	Negate(const Vector2 value);
		static void 	Negate(const Vector2& value, out Vector2& result);
		void			Normalize();
		static Vector2	Normalize(const Vector2 value);
		static void 	Normalize(const Vector2& value, out Vector2& result);
		static Vector2	Reflect(const Vector2 vector, const Vector2 normal);
		static void 	Reflect(const Vector2& vector, const Vector2& normal, out Vector2& result);
		static Vector2	SmoothStep(const Vector2 value1, const Vector2 value2, const float amount);
		static void 	SmoothStep(const Vector2& value1, const Vector2& value2, const float amount, out Vector2& result);
		static Vector2	Subtract(const Vector2 value1, const Vector2 value2);
		static void 	Subtract(const Vector2& value1, const Vector2& value2, out Vector2& result);
		const String	ToString() const;
		static Vector2	Transform(const Vector2 position, const Matrix matrix);
		static void 	Transform(const Vector2& position, const Matrix& matrix, out Vector2& result);
		static Vector2	Transform(const Vector2 position, const Quaternion rotation);
		static void 	Transform(const Vector2& position, const Quaternion& rotation, out Vector2& result);
		static void 	Transform(const Vector2 sourceArray[], const int sourceIndex, const Matrix& matrix, Vector2 destinationArray[], const int destinationIndex, const int length);
		static void 	Transform(const Vector2 sourceArray[], const int sourceIndex, const Quaternion& rotation, Vector2 destinationArray[], const int destinationIndex, const int length);
		static Vector2	TransformNormal(const Vector2 normal, const Matrix matrix);
		static void 	TransformNormal(const Vector2& normal, const Matrix& matrix, out Vector2& result);
		static void 	TransformNormal(const Vector2 sourceArray[], const int sourceIndex, const Matrix& matrix, Vector2 destinationArray[], const int destinationIndex, const int length);

		Vector2 operator -(const Vector2& other) const;
		Vector2 operator -() const;
		Vector2 operator +(const Vector2& other) const;
		Vector2 operator /(const float divider) const;
		Vector2 operator /(const Vector2& other) const;
		bool	operator==(const Vector2& other) const;
		bool	operator!=(const Vector2& other) const;
		Vector2 operator *(const float scaleFactor) const;
		Vector2 operator *(const Vector2& other) const;
	} ALIGNED16;

	Vector2 operator *(const float scaleFactor, const Vector2& vector);
}

#endif //_XFX_VECTOR2_
