/********************************************************
 *	Vector2.h											*
 *														*
 *	XFX Vector2 definition file							*
 *	Copyright © XFX Team. All Rights Reserved			*
 ********************************************************/
#ifndef _XFX_VECTOR2_
#define _XFX_VECTOR2_

#include <System/Interfaces.h>
#include <System/Object.h>

using namespace System;

namespace XFX
{
	struct Matrix;
	struct Quaternion;
	
	// Defines a vector with two components.
	struct Vector2 : public IEquatable<Vector2>, virtual Object
	{
		float X, Y;
		static const Vector2 One;
		static const Vector2 Zero;

		Vector2(float x, float y);
		Vector2(float value);
		Vector2(const Vector2 &obj);
		Vector2();

		static Vector2 Add(Vector2 value1, Vector2 value2);
		static void Add(Vector2 value1, Vector2 value2, out Vector2 result);
		static Vector2 Baricentric(Vector2 value1, Vector2 value2, Vector2 value3, float amount1, float amount2);
		static void Baricentric(Vector2 value1, Vector2 value2, Vector2 value3, float amount1, float amount2, out Vector2 result);
		static Vector2 CatmullRom(Vector2 value1, Vector2 value2, Vector2 value3, Vector2 value4, float amount);
		static void CatmullRom(Vector2 value1, Vector2 value2, Vector2 value3, Vector2 value4, float amount, out Vector2 result);
		static Vector2 Clamp(Vector2 value, Vector2 min, Vector2 max);
		static void Clamp(Vector2 value, Vector2 min, Vector2 max, out Vector2 result);
		static float Distance(Vector2 value1, Vector2 value2);
		static void Distance(Vector2 value1, Vector2 value2, out  float result);
		static float DistanceSquared(Vector2 value1, Vector2 value2);
		static void DistanceSquared(Vector2 value1, Vector2 value2, out float result);
		static Vector2 Divide(Vector2 value1, float divider);
		static void Divide(Vector2 value1, float divider, out Vector2 result);
		static Vector2 Divide(Vector2 value1, Vector2 value2);
		static void Divide(Vector2 value1, Vector2 value2, out Vector2 result);
		static float Dot(Vector2 value1, Vector2 value2);
		static void Dot(Vector2 value1, Vector2 value2, out float result);
		bool Equals(Vector2 other);
		int GetHashCode();
		static Vector2 Hermite(Vector2 value1, Vector2 tangent1, Vector2 value2, Vector2 tangent2, float amount);
		static void Hermite(Vector2 value1, Vector2 tangent1, Vector2 value2, Vector2 tangent2, float amount, out Vector2 result);
		float Length();
		float LengthSquared();
		static Vector2 Lerp(Vector2 value1, Vector2 value2, float amount);
		static void Lerp(Vector2 value1, Vector2 value2, float amount, out Vector2 result);
		static Vector2 Max(Vector2 value1, Vector2 value2);
		static void Max(Vector2 value1, Vector2 value2, out Vector2 result);
		static Vector2 Min(Vector2 value1, Vector2 value2);
		static void Min(Vector2 value1, Vector2 value2, out Vector2 result);
		static Vector2 Multiply(Vector2 value, float scaleFactor);
		void Multiply(Vector2 value1, float scaleFactor, out Vector2 result);
		static Vector2 Multiply(Vector2 value1, Vector2 value2);
		void Multiply(Vector2 value1, Vector2 value2, out Vector2 result);
		static Vector2 Negate(Vector2 value);
		static void Negate(Vector2 value, out Vector2 result);
		void Normalize();
		static Vector2 Normalize(Vector2 value);
		static void Normalize(Vector2 value, out Vector2 result);
		static Vector2 Reflect(Vector2 vector, Vector2 normal);
		static void Reflect(Vector2 vector, Vector2 normal, out Vector2 result);
		static Vector2 SmoothStep(Vector2 value1, Vector2 value2, float amount);
		static void SmoothStep(Vector2 value1, Vector2 value2, float amount, out Vector2 result);
		static Vector2 Subtract(Vector2 value1, Vector2 value2);
		static void Subtract(Vector2 value1, Vector2 value2, out Vector2 result);
		static Vector2 Transform(Vector2 position, Matrix matrix);
		static void Transform(Vector2 position, Matrix matrix, out Vector2 result);
		static Vector2 Transform(Vector2 position, Quaternion rotation);
		static void Transform(Vector2 position, Quaternion rotation, out Vector2 result);
		static void Transform(Vector2 sourceArray[], int sourceIndex, Matrix matrix, Vector2 destinationArray[], int destinationIndex, int length);
		static void Transform(Vector2 sourceArray[], int sourceIndex, Quaternion rotation, Vector2 destinationArray[], int destinationIndex, int length);
		static void Transform(Vector2 sourceArray[], Matrix matrix, Vector2 destinationArray[]);
		static void Transform(Vector2 sourceArray[], Quaternion rotation, Vector2 destinationArray[]);
		static Vector2 TransformNormal(Vector2 normal, Matrix matrix);
		static void TransformNormal(Vector2 normal, Matrix matrix, out Vector2 result);
		static void TransformNormal(Vector2 sourceArray[], int sourceIndex, Matrix matrix, Vector2 destinationArray[], int destinationIndex, int length);
		static void TransformNormal(Vector2 sourceArray[], Matrix matrix, Vector2 destinationArray[]);

		Vector2 operator-(const Vector2 other);
		Vector2 operator-();
		Vector2 operator+(const Vector2 other);
		Vector2 operator/(float divider);
		Vector2 operator/(const Vector2 other);
		bool operator==(const Vector2 other);
		bool operator!=(const Vector2 other);
		Vector2 operator*(const float scaleFactor);
		Vector2 operator*(const Vector2 other);
		Vector2 operator=(const Vector2 other);
	} ALIGNED16;
}

#endif //_XFX_VECTOR2_
