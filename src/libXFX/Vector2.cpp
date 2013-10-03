// Copyright (C) XFX Team
// All rights reserved.
// 
// Redistribution and use in source and binary forms, with or without 
// modification, are permitted provided that the following conditions are met:
// 
//     * Redistributions of source code must retain the above copyright 
//       notice, this list of conditions and the following disclaimer.
//     * Redistributions in binary form must reproduce the above copyright 
//       notice, this list of conditions and the following disclaimer in the 
//       documentation and/or other materials provided with the distribution.
//     * Neither the name of the copyright holder nor the names of any 
//       contributors may be used to endorse or promote products derived from 
//       this software without specific prior written permission.
// 
// THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS" 
// AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE 
// IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE 
// ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT OWNER OR CONTRIBUTORS BE 
// LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR 
// CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF 
// SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS 
// INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN 
// CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) 
// ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE 
// POSSIBILITY OF SUCH DAMAGE.

#include <MathHelper.h>
#include <Matrix.h>
#include <Quaternion.h>
#include <Vector2.h>
#include <Vector4.h>
#include <System/FrameworkResources.h>
#include <System/Math.h>
#include <System/String.h>
#include <System/Type.h>

#include <sassert.h>

using namespace System;

namespace XFX
{	
	const Vector2 Vector2::One = Vector2(1, 1);
	const Vector2 Vector2::Zero = Vector2(0, 0);
	const Type Vector2TypeInfo("Vector2", "XFX::Vector2", TypeCode::Object);

	Vector2::Vector2(const float x, const float y)
		: X(x), Y(y)
	{
	}

	Vector2::Vector2(const float value)
		: X(value), Y(value)
	{
	}

	Vector2::Vector2(const Vector2 &obj)
		: X(obj.X), Y(obj.Y)
	{
	}

	Vector2::Vector2()
		: X(0), Y(0)
	{
	}

	Vector2 Vector2::Add(const Vector2 value1, const Vector2 value2)
	{
		return Vector2(value1.X + value2.X, value1.Y + value2.Y);
	}

	void Vector2::Add(const Vector2& value1, const Vector2& value2, out Vector2& result)
	{
		result.X = value1.X + value2.X;
		result.Y = value1.Y + value2.Y;
	}

	Vector2 Vector2::Baricentric(const Vector2 value1, const Vector2 value2, const Vector2 value3, const float amount1, const float amount2)
	{
		return Vector2(MathHelper::Baricentric(value1.X, value2.X, value3.X, amount1, amount2),
			MathHelper::Baricentric(value1.Y, value2.Y, value3.Y, amount1, amount2));
	}

	void Vector2::Baricentric(const Vector2& value1, const Vector2& value2, const Vector2& value3, const float amount1, const float amount2, out Vector2& result)
	{
		result.X = MathHelper::Baricentric(value1.X, value2.X, value3.X, amount1, amount2);
		result.Y = MathHelper::Baricentric(value1.Y, value2.Y, value3.Y, amount1, amount2);
	}

	Vector2 Vector2::CatmullRom(const Vector2 value1, const Vector2 value2, const Vector2 value3, const Vector2 value4, const float amount)
	{
		return Vector2(MathHelper::CatmullRom(value1.X, value2.X, value3.X, value4.X, amount),
			MathHelper::CatmullRom(value1.Y, value2.Y, value3.Y, value4.Y, amount));
	}

	void Vector2::CatmullRom(const Vector2& value1, const Vector2& value2, const Vector2& value3, const Vector2& value4, const float amount, out Vector2& result)
	{
		result.X = MathHelper::CatmullRom(value1.X, value2.X, value3.X, value4.X, amount);
		result.Y = MathHelper::CatmullRom(value1.Y, value2.Y, value3.Y, value4.Y, amount);
	}

	Vector2 Vector2::Clamp(const Vector2 value, const Vector2 min, const Vector2 max)
	{
		return Vector2(MathHelper::Clamp(value.X, min.X, max.X), MathHelper::Clamp(value.Y, min.Y, max.Y));
	}

	void Vector2::Clamp(const Vector2& value, const Vector2& min, const Vector2& max, out Vector2& result)
	{
		result.X = MathHelper::Clamp(value.X, min.X, max.X);
		result.Y = MathHelper::Clamp(value.Y, min.Y, max.Y);
	}

	float Vector2::Distance(const Vector2 value1, const Vector2 value2)
	{
		float x = value1.X - value2.X;
		float y = value1.Y - value2.Y;
		return Math::Sqrt((x * x) + (y * y));
	}

	void Vector2::Distance(const Vector2& value1, const Vector2& value2, out float& result)
	{
		float x = value1.X - value2.X;
		float y = value1.Y - value2.Y;
		result = Math::Sqrt((x * x) + (y * y));
	}

	float Vector2::DistanceSquared(const Vector2 value1, const Vector2 value2)
	{
		float x = value1.X - value2.X;
		float y = value1.Y - value2.Y;
		return (x * x) + (y * y);
	}

	void Vector2::DistanceSquared(const Vector2& value1, const Vector2& value2, out float& result)
	{
		float x = value1.X - value2.X;
		float y = value1.Y - value2.Y;
		result = (x * x) + (y * y);
	}

	float Vector2::Dot(const Vector2 value1, const Vector2 value2)
	{
		return (value1.X * value2.X + value1.Y * value2.Y);
	}

	void Vector2::Dot(const Vector2& value1, const Vector2& value2, out float& result)
	{
		result = (value1.X * value2.X + value1.Y * value2.Y);
	}

	bool Vector2::Equals(Object const * const obj) const
	{
		return is(this, obj) ? (*this == *(Vector2*)obj) : false;
	}

	bool Vector2::Equals(const Vector2 other) const
	{
		return (*this == other);
	}

	int Vector2::GetHashCode() const
	{
		return (int)X ^ (int)Y;
	}

	const Type& Vector2::GetType()
	{
		return Vector2TypeInfo;
	}

	Vector2 Vector2::Hermite(const Vector2 value1, const Vector2 tangent1, const Vector2 value2, const Vector2 tangent2, const float amount)
	{
		return Vector2(MathHelper::Hermite(value1.X,tangent1.X,value2.X,tangent2.X,amount), MathHelper::Hermite(value1.Y,tangent1.Y,value2.Y,tangent2.Y,amount));
	}

	void Vector2::Hermite(const Vector2& value1, const Vector2& tangent1, const Vector2& value2, const Vector2& tangent2, const float amount, out Vector2& result)
	{
		result.X = MathHelper::Hermite(value1.X,tangent1.X,value2.X,tangent2.X,amount);
		result.Y = MathHelper::Hermite(value1.Y,tangent1.Y,value2.Y,tangent2.Y,amount);
	}

	float Vector2::Length() const
	{
		return Math::Sqrt((X * X) + (Y * Y));
	}

	float Vector2::LengthSquared() const
	{
		return (X * X) + (Y * Y);
	}

	Vector2 Vector2::Lerp(const Vector2 value1, const Vector2 value2, const float amount)
	{
		return Vector2(MathHelper::Lerp(value1.X, value2.X, amount), MathHelper::Lerp(value1.Y, value2.Y, amount));
	}

	void Vector2::Lerp(const Vector2& value1, const Vector2& value2, const float amount, out Vector2& result)
	{
		result.X = MathHelper::Lerp(value1.X, value2.X, amount);
		result.Y = MathHelper::Lerp(value1.Y, value2.Y, amount);
	}

	Vector2 Vector2::Max(const Vector2 value1, const Vector2 value2)
	{
		return Vector2((value1.X > value2.X) ? value1.X : value2.X,(value1.Y > value2.Y) ? value1.Y : value2.Y);
	}

	void Vector2::Max(const Vector2& value1, const Vector2& value2, out Vector2& result)
	{
		result.X = (value1.X > value2.X) ? value1.X : value2.X;
		result.Y = (value1.Y > value2.Y) ? value1.Y : value2.Y;
	}

	Vector2 Vector2::Min(const Vector2 value1, const Vector2 value2)
	{
		return Vector2((value1.X < value2.X) ? value1.X : value2.X, (value1.Y < value2.Y) ? value1.Y : value2.Y);
	}

	void Vector2::Min(const Vector2& value1, const Vector2& value2, out Vector2& result)
	{
		result.X = (value1.X < value2.X) ? value1.X : value2.X;
		result.Y = (value1.Y < value2.Y) ? value1.Y : value2.Y;
	}

	Vector2 Vector2::Multiply(const Vector2 value, const float scaleFactor)
	{
		return Vector2(value.X * scaleFactor, value.Y * scaleFactor);
	}

	void Vector2::Multiply(const Vector2& value, const float scaleFactor, out Vector2& result)
	{
		result.X = value.X * scaleFactor;
		result.Y = value.Y * scaleFactor;
	}

	Vector2 Vector2::Multiply(const Vector2 value1, const Vector2 value2)
	{
		return Vector2(value1.X * value2.X, value1.Y * value2.Y);
	}

	void Vector2::Multiply(const Vector2& value1, const Vector2& value2, out Vector2& result)
	{
		result.X = value1.X * value2.X;
		result.Y = value1.Y * value2.Y;
	}

	Vector2 Vector2::Negate(const Vector2 value)
	{
		return Vector2(-value.X, -value.Y);
	}

	void Vector2::Negate(const Vector2& value, out Vector2& result)
	{
		result.X = -value.X;
		result.Y = -value.Y;
	}

	void Vector2::Normalize()
	{
		float length = Length();

		if(length == 0)
		{
			return;
		}

		float num = 1 / length;
		X *= num;
		Y *= num;
	}

	Vector2 Vector2::Normalize(const Vector2 value)
	{
		Vector2 result;
		Normalize(value, result);
		return result;
	}

	void Vector2::Normalize(const Vector2& value, out Vector2& result)
	{
		float length = value.Length();

		if (length == 0)
		{
			return;
		}

		float num = 1 / length;
		result.X = value.X * num;
		result.Y = value.Y * num;
	}

	Vector2 Vector2::Reflect(const Vector2 vector, const Vector2 normal)
	{
		Vector2 result;
		Reflect(vector, normal, result);
		return result;
	}
	
	void Vector2::Reflect(const Vector2& vector, const Vector2& normal, out Vector2& result)
	{
		float dp = Dot(vector, normal);
		result.X = vector.X - normal.X * dp;
		result.Y = vector.Y - normal.Y * dp;
	}

	Vector2 Vector2::SmoothStep(const Vector2 value1, const Vector2 value2, const float amount)
	{
		Vector2 result;
		SmoothStep(value1, value2, amount, result);
		return result;
	}

	void Vector2::SmoothStep(const Vector2& value1, const Vector2& value2, const float amount, out Vector2& result)
	{
		result.X = MathHelper::SmoothStep(value1.X, value2.X, amount);
		result.Y = MathHelper::SmoothStep(value1.Y, value2.Y, amount);
	}

	Vector2 Vector2::Subtract(const Vector2 value1, const Vector2 value2)
	{
		Vector2 result;
		Subtract(value1, value2, result);
		return result;
	}

	void Vector2::Subtract(const Vector2& value1, const Vector2& value2, out Vector2& result)
	{
		result.X = value1.X - value2.X;
		result.Y = value1.Y - value2.Y;
	}

	const String Vector2::ToString() const
	{
		return String::Format("{X:%f Y:%f}", X, Y);
	}

	Vector2 Vector2::Transform(const Vector2 position, const Matrix matrix)
	{
		Vector2 result;
		Transform(position, matrix, result);
		return result;
	}

	void Vector2::Transform(const Vector2& position, const Matrix& matrix, out Vector2& result)
	{
		Vector4 vector;

		vector.X = (vector.X * matrix.M11) + (vector.Y * matrix.M21) + matrix.M41;
		vector.Y = (vector.X * matrix.M12) + (vector.Y * matrix.M22) + matrix.M42;
		vector.Z = (vector.X * matrix.M13) + (vector.Y * matrix.M23) + matrix.M43;
		vector.W = 1 / ((vector.X * matrix.M14) + (vector.Y * matrix.M24) + matrix.M44);

		result.X = vector.X * vector.W;
		result.Y = vector.Y * vector.W;
	}

	Vector2 Vector2::Transform(const Vector2 position, const Quaternion rotation)
	{
		Vector2 result;
		Transform(position, rotation, result);
		return result;
	}

	void Vector2::Transform(const Vector2& position, const Quaternion& rotation, out Vector2& result)
	{
		Quaternion quat = Quaternion(position.X, position.Y, 0, 0), i, t;
		Quaternion::Inverse(rotation, i);
		Quaternion::Multiply(rotation, quat, t);
		Quaternion::Multiply(t, i, quat);

		result.X = quat.X;
		result.Y = quat.Y;
	}

	void Vector2::Transform(const Vector2 sourceArray[], const int sourceIndex, const Matrix& matrix, Vector2 destinationArray[], const int destinationIndex, const int length)
	{
		sassert(sourceArray != null, "sourceArray cannot be null.");

		sassert(destinationArray != null, "destinationArray cannot be null.");

		for(int i = sourceIndex, j = destinationIndex; i < (sourceIndex + length); i++, j++)
		{
			TransformNormal(sourceArray[i], matrix, destinationArray[j]);
		}
	}

	void Vector2::Transform(const Vector2 sourceArray[], const int sourceIndex, const Quaternion& rotation, Vector2 destinationArray[], const int destinationIndex, const int length)
	{
		sassert(sourceArray != null, String::Format("sourceArray; %s", FrameworkResources::ArgumentNull_Generic));

		sassert(destinationArray != null, String::Format("destinationArray; %s", FrameworkResources::ArgumentNull_Generic));

		for(int i = sourceIndex, j = destinationIndex; i < (sourceIndex + length); i++, j++)
		{
			Transform(sourceArray[i], rotation, destinationArray[j]);
		}
	}

	Vector2 Vector2::TransformNormal(const Vector2 normal, const Matrix matrix)
	{
		Vector2 result;
		result.X = (normal.X * matrix.M11) + (normal.Y * matrix.M21);
		result.Y = (normal.X * matrix.M12) + (normal.Y * matrix.M22);

		return result;
	}

	void Vector2::TransformNormal(const Vector2& normal, const Matrix& matrix, out Vector2& result)
	{
		result.X = (normal.X * matrix.M11) + (normal.Y * matrix.M21);
		result.Y = (normal.X * matrix.M12) + (normal.Y * matrix.M22);
	}

	void Vector2::TransformNormal(const Vector2 sourceArray[], const int sourceIndex, const Matrix& matrix, Vector2 destinationArray[], const int destinationIndex, const int length)
	{
		sassert(sourceArray != null, String::Format("sourceArray; %s", FrameworkResources::ArgumentNull_Generic));

		sassert(destinationArray != null, String::Format("destinationArray; %s", FrameworkResources::ArgumentNull_Generic));

		for(int i = sourceIndex, j = destinationIndex; i < (sourceIndex + length); i++, j++)
		{
			TransformNormal(sourceArray[i], matrix, destinationArray[j]);
		}
	}

	Vector2 Vector2::operator+(const Vector2& other) const
	{
		return Vector2(X + other.X, Y + other.Y);
	}

	Vector2 Vector2::operator/(const float divider) const
	{
		return Vector2(X / divider, Y / divider);
	}

	Vector2 Vector2::operator/(const Vector2& other) const
	{
		return Vector2(X / other.X, Y / other.Y);
	}

	bool Vector2::operator==(const Vector2& other) const
	{
		return ((X == other.X) && (Y == other.Y));
	}

	bool Vector2::operator!=(const Vector2& other) const
	{
		return ((X != other.X) || (Y != other.Y));
	}

	Vector2 Vector2::operator*(const float scaleFactor) const
	{
		return Vector2(X * scaleFactor, Y * scaleFactor);
	}

	Vector2 Vector2::operator*(const Vector2& other) const
	{
		return Vector2(X * other.X, Y * other.Y);
	}

	Vector2 Vector2::operator-(const Vector2& other) const
	{
		return Vector2(X - other.X, Y - other.Y);
	}

	Vector2 Vector2::operator-() const
	{
		return Vector2(-X, -Y);
	}

	Vector2 operator *(const float scaleFactor, const Vector2& vector)
	{
		return Vector2(vector.X * scaleFactor, vector.Y * scaleFactor);
	}
}
