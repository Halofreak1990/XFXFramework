/********************************************************
 *	Vector3.h											*
 *														*
 *	XFX Vector3 definition file							*
 *	Copyright © XFX Team. All Rights Reserved			*
 ********************************************************/
#ifndef _XFX_VECTOR3_
#define _XFX_VECTOR3_

#include <System/Interfaces.h>
#include <System/Object.h>

using namespace System;

namespace XFX
{
	struct Matrix;
	struct Quaternion;
	struct Vector2;
	
	// Defines a vector with three components.
	struct Vector3 : public IEquatable<Vector3>, virtual Object
	{
	public:
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

		Vector3(float value);
		Vector3(float x, float y, float z);
		Vector3(Vector2 value, float z);
		Vector3(const Vector3 &obj);
		Vector3();

		static Vector3 Add(Vector3 value1, Vector3 value2);
		static void Add(Vector3 value1, Vector3 value2, out Vector3 result);
		static Vector3 Baricentric(Vector3 value1, Vector3 value2, Vector3 value3, float amount1, float amount2);
		static void Baricentric(Vector3 value1, Vector3 value2, Vector3 value3, float amount1, float amount2, out Vector3 result);
		static Vector3 CatmullRom(Vector3 value1, Vector3 value2, Vector3 value3, Vector3 value4, float amount);
		static void CatmullRom(Vector3 value1, Vector3 value2, Vector3 value3, Vector3 value4, float amount, out Vector3 result);
		static Vector3 Clamp(Vector3 value1, Vector3 min, Vector3 max);
		static void Clamp(Vector3 value1, Vector3 min, Vector3 max, out Vector3 result);
		static Vector3 Cross(Vector3 vector1, Vector3 vector2);
		static void Cross(Vector3 vector1, Vector3 vector2, out Vector3 result);
		static float Distance(Vector3 value1, Vector3 value2);
		static void Distance(Vector3 value1, Vector3 value2, out float result);
		static float DistanceSquared(Vector3 value1, Vector3 value2);
		static void DistanceSquared(Vector3 value1, Vector3 value2, out float result);
		static Vector3 Divide(Vector3 value1, float value2);
		static void Divide(Vector3 value1, float value2, out Vector3 result);
		static Vector3 Divide(Vector3 value1, Vector3 value2);
		static void Divide(Vector3 value1, Vector3 value2, out Vector3 result);
		static float Dot(Vector3 value1, Vector3 value2);
		static void Dot(Vector3 value1, Vector3 value2, out float result);
		bool Equals(Vector3 other);
		int GetHashCode();
		static Vector3 Hermite(Vector3 value1, Vector3 tangent1, Vector3 value2, Vector3 tangent2, float amount);
		static void Hermite(Vector3 value1, Vector3 tangent1, Vector3 value2, Vector3 tangent2, float amount, out Vector3 result);
		float Length();
		float LengthSquared();
		static Vector3 Lerp(Vector3 value1, Vector3 value2, float amount);
		static void Lerp(Vector3 value1, Vector3 value2, float amount, out Vector3 result);
		static Vector3 Max(Vector3 value1, Vector3 value2);
		static void Max(Vector3 value1, Vector3 value2, out Vector3 result);
		static Vector3 Min(Vector3 value1, Vector3 value2);
		static void Min(Vector3 value1, Vector3 value2, out Vector3 result);
		static Vector3 Multiply(Vector3 value1, float scaleFactor);
		static void Multiply(Vector3 value1, float scaleFactor, out Vector3 result);
		static Vector3 Multiply(Vector3 value1, Vector3 value2);
		static void Multiply(Vector3 value1, Vector3 value2, out Vector3 result);
		static Vector3 Negate(Vector3 value);
		static void Negate(Vector3 value, out Vector3 result);
		void Normalize();
		static Vector3 Normalize(Vector3 value);
		static void Normalize(Vector3 value, out Vector3 result);
		static Vector3 Reflect(Vector3 vector, Vector3 normal);
		static void Reflect(Vector3 vector, Vector3 normal, out Vector3 result);
		static Vector3 SmoothStep(Vector3 value1, Vector3 value2, float amount);
		static void SmoothStep(Vector3 value1, Vector3 value2, float amount, out Vector3 result);
		static Vector3 Subtract(Vector3 value1, Vector3 value2);
		static void Subtract(Vector3 value1, Vector3 value2, out Vector3 result);
		static Vector3 Transform(Vector3 position, Matrix matrix);
		static void Transform(Vector3 position, Matrix matrix, out Vector3 result);
		static Vector3 Transform(Vector3 position, Quaternion rotation);
		static void Transform(Vector3 position, Quaternion rotation, out Vector3 result);
		static void Transform(Vector3 sourceArray[], int sourceIndex, Matrix matrix, Vector3 destinationArray[], int destinationIndex, int length);
		static void Transform(Vector3 sourceArray[], int sourceIndex, Quaternion rotation, Vector3 destinationArray[], int destinationIndex, int length);
		static void Transform(Vector3 sourceArray[], Matrix matrix, Vector3 destinationArray[]);
		static void Transform(Vector3 sourceArray[], Quaternion rotation, Vector3 destinationArray[]);
		static Vector3 TransformNormal(Vector3 normal, Matrix matrix);
		static void TransformNormal(Vector3 normal, Matrix matrix, out Vector3 result);
		static void TransformNormal(Vector3 sourceArray[], int sourceIndex, Matrix matrix, Vector3 destinationArray[], int destinationIndex, int length);
		static void TransformNormal(Vector3 sourceArray[], Matrix matrix, Vector3 destinationArray[]);

		Vector3 operator+(Vector3 other);
		Vector3 operator/(float divider);
		Vector3 operator/(Vector3 other);
		bool operator==(const Vector3 other);
		bool operator!=(const Vector3 other);
		Vector3 operator*(float scaleFactor);
		Vector3 operator*(Vector3 other);
		Vector3 operator-(Vector3 other);
		Vector3 operator-();
		Vector3 operator=(const Vector3 other);
	} ALIGNED16;
}

#endif //_XFX_VECTOR3_
