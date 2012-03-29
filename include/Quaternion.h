/********************************************************
 *	Quaternion.h										*
 *														*
 *	XFX Quaternion definition file						*
 *	Copyright © XFX Team. All Rights Reserved			*
 ********************************************************/
#ifndef _XFX_QUATERNION_
#define _XFX_QUATERNION_

#include <System/Types.h>

namespace XFX
{
	struct Matrix;
	struct Vector3;
	
	struct Quaternion : public IEquatable<Quaternion>, virtual Object
	{
		float W, X, Y, Z;
		static const Quaternion Identity;
		
		Quaternion(float x, float y, float z, float w);
		Quaternion(Vector3 vectorPart, float scalarPart);
		Quaternion(const Quaternion &obj);
		Quaternion();
		
		static Quaternion Add(Quaternion quaternion1, Quaternion quaternion2);
		static void Add(Quaternion quaternion1, Quaternion quaternion2, out Quaternion result);
		static Quaternion Concatenate(Quaternion quaternion1, Quaternion quaternion2);
		static void Concatenate(Quaternion quaternion1, Quaternion quaternion2, out Quaternion result);
		void Conjugate();
		static Quaternion Conjugate(Quaternion value);
		static void Conjugate(Quaternion value, out Quaternion result);
		static Quaternion CreateFromAxisAngle(Vector3 axis, float angle);
		static void CreateFromAxisAngle(Vector3 axis, float angle, out Quaternion result);
		static Quaternion CreateFromRotationMatrix(Matrix matrix);
		static void CreateFromRotationMatrix(Matrix matrix, out Quaternion result);
		static Quaternion CreateFromYawPitchRoll(float yaw, float pitch, float roll);
		static void CreateFromYawPitchRoll(float yaw, float pitch, float roll, out Quaternion result);
		static Quaternion Divide(Quaternion quaternion1, Quaternion quaternion2);
		static void Divide(Quaternion quaternion1, Quaternion quaternion2, out Quaternion result);
		static float Dot(Quaternion quaternion1, Quaternion quaternion2);
		static void Dot(Quaternion quaternion1, Quaternion quaternion2, out float result);
		bool Equals(const Quaternion obj) const;
		static Quaternion Inverse(Quaternion quaternion);
		static void Inverse(Quaternion quaternion, out Quaternion result);
		float Length();
		float LengthSquared();
		static Quaternion Lerp(Quaternion quaternion1, Quaternion quaternion2, float amount);
		static void Lerp(Quaternion quaternion1, Quaternion quaternion2, float amount, out Quaternion result);
		static Quaternion Multiply(Quaternion quaternion1, Quaternion quaternion2);
		static void Multiply(Quaternion quaternion1, Quaternion quaternion2, out Quaternion result);
		static Quaternion Multiply(Quaternion quaternion, float scaleFactor);
		static void Multiply(Quaternion quaternion, float scaleFactor, out Quaternion result);
		static Quaternion Negate(Quaternion quaternion);
		static void Negate(Quaternion quaternion, out Quaternion result);
		void Normalize();
		static Quaternion Slerp(Quaternion quaternion1, Quaternion quaternion2, float amount);
		static void Slerp(Quaternion quaternion1, Quaternion quaternion2, float amount, out Quaternion result);
		static Quaternion Subtract(Quaternion quaternion1, Quaternion quaternion2);
		static void Subtract(Quaternion quaternion1, Quaternion quaternion2, out Quaternion result);
		char* ToString();
		
		const Quaternion operator+(const Quaternion other);
		const Quaternion operator/(const Quaternion other);
		bool operator==(const Quaternion other) const;
		bool operator!=(const Quaternion other) const;
		const Quaternion operator*(const Quaternion other);
		const Quaternion operator*(const float scaleFactor);
		const Quaternion operator-(const Quaternion other);
		const Quaternion operator-();
	} ALIGNED16;
}

#endif //_XFX_QUATERNION_
