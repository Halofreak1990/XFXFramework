/*****************************************************************************
 *	Vector3.h																 *
 *																			 *
 *	XFX Vector3 definition file												 *
 *	Copyright (c) XFX Team. All Rights Reserved 							 *
 *****************************************************************************/
#ifndef _XFX_VECTOR3_
#define _XFX_VECTOR3_

#include <System/Interfaces.h>

using namespace System;

namespace XFX
{
	struct Matrix;
	struct Quaternion;
	struct Vector2;
	
	// Defines a vector with three components.
	struct Vector3 : IEquatable<Vector3>, Object
	{
		float X, Y, Z;
		static const Vector3 Backward;
		static const Vector3 Down;
		static const Vector3 Forward;
		static const Vector3 Left;
		static const Vector3 One;
		static const Vector3 Right;
		static const Vector3 UnitX;
		static const Vector3 UnitY;
		static const Vector3 UnitZ;
		static const Vector3 Up;
		static const Vector3 Zero;

		Vector3(const float value);
		Vector3(const float x, const float y, const float z);
		Vector3(const Vector2 value, const float z);
		Vector3(const Vector3 &obj);
		Vector3();

		static Vector3 Add(const Vector3 value1, const Vector3 value2);
		static void Add(const Vector3 value1, const Vector3 value2, out Vector3& result);
		static Vector3 Baricentric(const Vector3 value1, const Vector3 value2, const Vector3 value3, const float amount1, const float amount2);
		static void Baricentric(const Vector3 value1, const Vector3 value2, const Vector3 value3, const float amount1, const float amount2, out Vector3& result);
		static Vector3 CatmullRom(const Vector3 value1, const Vector3 value2, const Vector3 value3, const Vector3 value4, const float amount);
		static void CatmullRom(const Vector3 value1, const Vector3 value2, const Vector3 value3, const Vector3 value4, const float amount, out Vector3& result);
		static Vector3 Clamp(const Vector3 value1, const Vector3 min, const Vector3 max);
		static void Clamp(const Vector3 value1, const Vector3 min, const Vector3 max, out Vector3& result);
		static Vector3 Cross(const Vector3 vector1, const Vector3 vector2);
		static void Cross(const Vector3 vector1, const Vector3 vector2, out Vector3& result);
		static float Distance(const Vector3 value1, const Vector3 value2);
		static void Distance(const Vector3 value1, const Vector3 value2, out float& result);
		static float DistanceSquared(const Vector3 value1, const Vector3 value2);
		static void DistanceSquared(const Vector3 value1, const Vector3 value2, out float& result);
		static Vector3 Divide(const Vector3 value1, const float value2);
		static void Divide(const Vector3 value1, const float value2, out Vector3& result);
		static Vector3 Divide(const Vector3 value1, const Vector3 value2);
		static void Divide(const Vector3 value1, const Vector3 value2, out Vector3& result);
		static float Dot(const Vector3 value1, const Vector3 value2);
		static void Dot(const Vector3 value1, const Vector3 value2, out float& result);
		bool Equals(Object const * const obj) const;
		bool Equals(const Vector3 other) const;
		int GetHashCode() const;
		static int GetType();
		static Vector3 Hermite(const Vector3 value1, const Vector3 tangent1, const Vector3 value2, const Vector3 tangent2, const float amount);
		static void Hermite(const Vector3 value1, const Vector3 tangent1, const Vector3 value2, const Vector3 tangent2, const float amount, out Vector3& result);
		float Length() const;
		float LengthSquared() const;
		static Vector3 Lerp(const Vector3 value1, const Vector3 value2, float amount);
		static void Lerp(const Vector3 value1, const Vector3 value2, const float amount, out Vector3& result);
		static Vector3 Max(const Vector3 value1, const Vector3 value2);
		static void Max(const Vector3 value1, const Vector3 value2, out Vector3& result);
		static Vector3 Min(const Vector3 value1, const Vector3 value2);
		static void Min(const Vector3 value1, const Vector3 value2, out Vector3& result);
		static Vector3 Multiply(const Vector3 value1, const float scaleFactor);
		static void Multiply(const Vector3 value1, const float scaleFactor, out Vector3& result);
		static Vector3 Multiply(const Vector3 value1, const Vector3 value2);
		static void Multiply(const Vector3 value1, const Vector3 value2, out Vector3& result);
		static Vector3 Negate(const Vector3 value);
		static void Negate(const Vector3 value, out Vector3& result);
		void Normalize();
		static Vector3 Normalize(const Vector3 value);
		static void Normalize(const Vector3 value, out Vector3& result);
		static Vector3 Reflect(const Vector3 vector, const Vector3 normal);
		static void Reflect(const Vector3 vector, const Vector3 normal, out Vector3& result);
		static Vector3 SmoothStep(const Vector3 value1, const Vector3 value2, const float amount);
		static void SmoothStep(const Vector3 value1, const Vector3 value2, const float amount, out Vector3& result);
		static Vector3 Subtract(const Vector3 value1, const Vector3 value2);
		static void Subtract(const Vector3 value1, const Vector3 value2, out Vector3& result);
		const String& ToString() const;
		static Vector3 Transform(const Vector3 position, const Matrix matrix);
		static void Transform(const Vector3 position, const Matrix matrix, out Vector3& result);
		static Vector3 Transform(const Vector3 position, const Quaternion rotation);
		static void Transform(const Vector3 position, const Quaternion rotation, out Vector3& result);
		static void Transform(const Vector3 sourceArray[], const int sourceIndex, const Matrix matrix, Vector3 destinationArray[], const int destinationIndex, const int length) NONNULL(1, 4);
		static void Transform(const Vector3 sourceArray[], const int sourceIndex, const Quaternion rotation, Vector3 destinationArray[], const int destinationIndex, const int length) NONNULL(1, 4);
		static void Transform(const Vector3 sourceArray[], const Matrix matrix, Vector3 destinationArray[]) NONNULL(1, 3);
		static void Transform(const Vector3 sourceArray[], const Quaternion rotation, Vector3 destinationArray[]) NONNULL(1, 3);
		static Vector3 TransformNormal(const Vector3 normal, const Matrix matrix);
		static void TransformNormal(const Vector3 normal, const Matrix matrix, out Vector3& result);
		static void TransformNormal(const Vector3 sourceArray[], const int sourceIndex, const Matrix matrix, Vector3 destinationArray[], const int destinationIndex, const int length) NONNULL(1, 4);
		static void TransformNormal(const Vector3 sourceArray[], const Matrix matrix, Vector3 destinationArray[]) NONNULL(1, 3);

		Vector3 operator+(const Vector3& other);
		Vector3 operator/(const float divider);
		Vector3 operator/(const Vector3& other);
		bool operator==(const Vector3& other) const;
		bool operator!=(const Vector3& other) const;
		Vector3 operator*(const float scaleFactor);
		Vector3 operator*(const Vector3& other);
		Vector3 operator-(const Vector3& other);
		Vector3 operator-();
	} ALIGNED16;
}

#endif //_XFX_VECTOR3_
