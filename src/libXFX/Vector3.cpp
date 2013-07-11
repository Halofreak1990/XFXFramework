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
#include <Vector3.h>
#include <Vector4.h>
#include <System/Array.h>
#include <System/Math.h>
#include <System/String.h>

#include <sassert.h>

using namespace System;

namespace XFX
{	
	const Vector3 Vector3::Backward = Vector3(0, 0, 1);
	const Vector3 Vector3::Down = Vector3(0, -1, 0);
	const Vector3 Vector3::Forward = Vector3(0, 0, -1);
	const Vector3 Vector3::Left = Vector3(-1, 0, 0);
	const Vector3 Vector3::One = Vector3(1, 1, 1);
	const Vector3 Vector3::Right = Vector3(1, 0, 0);
	const Vector3 Vector3::UnitX = Vector3(1, 0, 0);
	const Vector3 Vector3::UnitY = Vector3(0, 1, 0);
	const Vector3 Vector3::UnitZ = Vector3(0, 0, 1);
	const Vector3 Vector3::Up = Vector3(0, 1, 0);
	const Vector3 Vector3::Zero = Vector3(0, 0, 0);
	
	Vector3::Vector3(float value)
		: X(value), Y(value), Z(value)
	{
	}
	
	Vector3::Vector3(float x, float y, float z)
		: X(x), Y(y), Z(z)
	{
	}
	
	Vector3::Vector3(Vector2 value, float z)
		: X(value.X), Y(value.Y), Z(z)
	{
	}

	Vector3::Vector3(const Vector3 &obj)
		: X(obj.X), Y(obj.Y), Z(obj.Z)
	{
	}

	Vector3::Vector3()
		: X(0), Y(0), Z(0)
	{
	}

	Vector3 Vector3::Add(Vector3 value1, Vector3 value2)
	{
		return Vector3(value1.X + value2.X, value1.Y + value2.Y, value1.Z + value2.Z);
	}

	void Vector3::Add(Vector3 value1, Vector3 value2, out Vector3& result)
	{
		result.X = value1.X + value2.X;
		result.Y = value1.Y + value2.Y;
		result.Z = value1.Z + value2.Z;
	}
	
	Vector3 Vector3::Baricentric(Vector3 value1, Vector3 value2, Vector3 value3, float amount1, float amount2)
	{
		Vector3 result;
		result.X = MathHelper::Baricentric(value1.X, value2.X, value3.X, amount1, amount2);
		result.Z = MathHelper::Baricentric(value1.X, value2.X, value3.X, amount1, amount2);
		result.X = MathHelper::Baricentric(value1.X, value2.X, value3.X, amount1, amount2);
		return result;
	}
	
	void Vector3::Baricentric(Vector3 value1, Vector3 value2, Vector3 value3, float amount1, float amount2, out Vector3& result)
	{
		result.X = MathHelper::Baricentric(value1.X, value2.X, value3.X, amount1, amount2);
		result.Z = MathHelper::Baricentric(value1.X, value2.X, value3.X, amount1, amount2);
		result.X = MathHelper::Baricentric(value1.X, value2.X, value3.X, amount1, amount2);
	}
	
	Vector3 Vector3::CatmullRom(Vector3 value1, Vector3 value2, Vector3 value3, Vector3 value4, float amount)
	{
		Vector3 result;
		result.X = MathHelper::CatmullRom(value1.X, value2.X, value3.X, value4.X, amount);
		result.Y = MathHelper::CatmullRom(value1.Y, value2.Y, value3.Y, value4.Y, amount);
		result.Z = MathHelper::CatmullRom(value1.Z, value2.Z, value3.Z, value4.Z, amount);
		return result;
	}
	
	void Vector3::CatmullRom(Vector3 value1, Vector3 value2, Vector3 value3, Vector3 value4, float amount, out Vector3& result)
	{
		result.X = MathHelper::CatmullRom(value1.X, value2.X, value3.X, value4.X, amount);
		result.Y = MathHelper::CatmullRom(value1.Y, value2.Y, value3.Y, value4.Y, amount);
		result.Z = MathHelper::CatmullRom(value1.Z, value2.Z, value3.Z, value4.Z, amount);
	}
	
	Vector3 Vector3::Clamp(Vector3 value1, Vector3 min, Vector3 max)
	{
		Vector3 result;
		result.X = MathHelper::Clamp(value1.X, min.X, max.X);
		result.Y = MathHelper::Clamp(value1.Y, min.Y, max.Y);
		result.Z = MathHelper::Clamp(value1.Z, min.Z, max.Z);
		return result;
	}
	
	void Vector3::Clamp(Vector3 value1, Vector3 min, Vector3 max, out Vector3& result)
	{
		result.X = MathHelper::Clamp(value1.X, min.X, max.X);
		result.Y = MathHelper::Clamp(value1.Y, min.Y, max.Y);
		result.Z = MathHelper::Clamp(value1.Z, min.Z, max.Z);
	}
	
	Vector3 Vector3::Cross(Vector3 vector1, Vector3 vector2)
	{
		Vector3 result;
		result.X = vector1.Y * vector2.Z - vector1.Z * vector2.Y;
		result.Y = vector1.Z * vector2.X - vector1.X * vector2.Z;
		result.Z = vector1.X * vector2.Y - vector1.Y * vector2.X;
		return result;
	}
	
	void Vector3::Cross(Vector3 vector1, Vector3 vector2, out Vector3& result)
	{
		result.X = vector1.Y * vector2.Z - vector1.Z * vector2.Y;
		result.Y = vector1.Z * vector2.X - vector1.X * vector2.Z;
		result.Z = vector1.X * vector2.Y - vector1.Y * vector2.X;
	}
	
	float Vector3::Distance(Vector3 value1, Vector3 value2)
	{
		float x = value1.X - value2.X;
        float y = value1.Y - value2.Y;
        float z = value1.Z - value2.Z;
        
		return Math::Sqrt((x*x) + (y*y) + (z*z));
	}
	
	void Vector3::Distance(Vector3 value1, Vector3 value2, out float& result)
	{
		float x = value1.X - value2.X;
        float y = value1.Y - value2.Y;
        float z = value1.Z - value2.Z;
        
		result = Math::Sqrt((x*x) + (y*y) + (z*z));
	}
	
	float Vector3::DistanceSquared(Vector3 value1, Vector3 value2)
	{
		float x = value1.X - value2.X;
        float y = value1.Y - value2.Y;
        float z = value1.Z - value2.Z;
        
        return (x*x) + (y*y) + (z*z);
	}
	
	void Vector3::DistanceSquared(Vector3 value1, Vector3 value2, out float& result)
	{
		float x = value1.X - value2.X;
        float y = value1.Y - value2.Y;
        float z = value1.Z - value2.Z;
        
		result = (x*x) + (y*y) + (z*z);
	}
	
	Vector3 Vector3::Divide(Vector3 value1, float value2)
	{
		return Vector3(value1.X / value2, value1.Y / value2, value1.Z / value2);
	}
	
	void Vector3::Divide(Vector3 value1, float value2, out Vector3& result)
	{
		result.X = value1.X / value2;
		result.Y = value1.Y / value2;
		result.Z = value1.Z / value2;
	}
	
	Vector3 Vector3::Divide(Vector3 value1, Vector3 value2)
	{
		Vector3 result;
		result.X = value1.X / value2.X;
		result.Y = value1.Y / value2.Y;
		result.Z = value1.Z / value2.Z;
		return result;
	}
	
	void Vector3::Divide(Vector3 value1, Vector3 value2, out Vector3& result)
	{
		result.X = value1.X / value2.X;
		result.Y = value1.Y / value2.Y;
		result.Z = value1.Z / value2.Z;
	}
	
	float Vector3::Dot(Vector3 value1, Vector3 value2)
	{
		return (value1.X * value2.X + value1.Y * value2.Y + value1.Z * value2.Z);
	}
	
	void Vector3::Dot(Vector3 value1, Vector3 value2, out float& result)
	{
		result = (value1.X * value2.X + value1.Y * value2.Y + value1.Z * value2.Z);
	}

	bool Vector3::Equals(Object const * const obj) const
	{
		return is(this, obj) ? *this == *(Vector3*)obj : false;
	}

	bool Vector3::Equals(const Vector3 other) const
	{
		return (*this == other);
	}
	
	int Vector3::GetHashCode() const
	{
		return ((int)X ^ (int)Y ^ (int)Z);
	}

	int Vector3::GetType()
	{
		// TODO: implement
	}
	
	Vector3 Vector3::Hermite(Vector3 value1, Vector3 tangent1, Vector3 value2, Vector3 tangent2, float amount)
	{
		Vector3 result;
		Hermite(value1, tangent1, value2, tangent2, amount, result);
		return result;
	}
	
	void Vector3::Hermite(Vector3 value1, Vector3 tangent1, Vector3 value2, Vector3 tangent2, float amount, out Vector3& result)
	{
		result.X = MathHelper::Hermite(value1.X, tangent1.X, value2.X, tangent2.X, amount);
		result.Y = MathHelper::Hermite(value1.Y, tangent1.Y, value2.Y, tangent2.Y, amount);
		result.Z = MathHelper::Hermite(value1.Z, tangent1.Z, value2.Z, tangent2.Z, amount);
	}
	
	float Vector3::Length() const
	{
		return Math::Sqrt((X * X) + (Y * Y) + (Z * Z));
	}
	
	float Vector3::LengthSquared() const
	{
		return (X * X) + (Y * Y) + (Z * Z);
	}
	
	Vector3 Vector3::Lerp(Vector3 value1, Vector3 value2, float amount)
	{
		Vector3 result;
		Lerp(value1, value2, amount, result);
		return result;
	}
	
	void Vector3::Lerp(Vector3 value1, Vector3 value2, float amount, out Vector3& result)
	{
		result.X = MathHelper::Lerp(value1.X, value2.X, amount);
		result.Y = MathHelper::Lerp(value1.Y, value2.Y, amount);
		result.Z = MathHelper::Lerp(value1.Z, value2.Z, amount);
	}
	
	Vector3 Vector3::Max(Vector3 value1, Vector3 value2)
	{
		Vector3 result;
		Max(value1, value2, result);
		return result;
	}
	
	void Vector3::Max(Vector3 value1, Vector3 value2, out Vector3& result)
	{
		result.X = (value1.X > value2.X) ? value1.X : value2.X;
		result.Y = (value1.Y > value2.Y) ? value1.Y : value2.Y;
		result.Z = (value1.Z > value2.Z) ? value1.Z : value2.Z;
	}
	
	Vector3 Vector3::Min(Vector3 value1, Vector3 value2)
	{
		Vector3 result;
		Min(value1, value2, result);
		return result;
	}
	
	void Vector3::Min(Vector3 value1, Vector3 value2, out Vector3& result)
	{
		result.X = (value1.X < value2.X) ? value1.X : value2.X;
		result.Y = (value1.Y < value2.Y) ? value1.Y : value2.Y;
		result.Z = (value1.Z < value2.Z) ? value1.Z : value2.Z;
	}
	
	Vector3 Vector3::Multiply(Vector3 value1, float scaleFactor)
	{
		Vector3 result;
		Multiply(value1, scaleFactor, result);
		return result;
	}
	
	void Vector3::Multiply(Vector3 value1, float scaleFactor, out Vector3& result)
	{
		result.X = value1.X * scaleFactor;
		result.Y = value1.Y * scaleFactor;
		result.Z = value1.Z * scaleFactor;
	}
	
	Vector3 Vector3::Multiply(Vector3 value1, Vector3 value2)
	{
		Vector3 result;
		Multiply(value1, value2, result);
		return result;
	}
	
	void Vector3::Multiply(Vector3 value1, Vector3 value2, out Vector3& result)
	{
		result.X = value1.X * value2.X;
		result.Y = value1.Y * value2.Y;
		result.Z = value1.Z * value2.Z;
	}
	
	Vector3 Vector3::Negate(Vector3 value)
	{
		Vector3 result;
		Negate(value, result);
		return result;
	}
	
	void Vector3::Negate(Vector3 value, out Vector3& result)
	{
		result.X = -value.X;
		result.Y = -value.Y;
		result.Z = -value.Z;
	}
	
	void Vector3::Normalize()
	{
		float length = Length(); 
        if(length == 0) 
            return; 
        float num = 1 / length; 
        X *= num; 
        Y *= num; 
        Z *= num; 
	}
	
	Vector3 Vector3::Normalize(Vector3 value)
	{
		Vector3 result;
		float length = value.Length(); 
        if(length == 0) 
            return Vector3::Zero; 
        float num = 1 / length; 
        result.X *= num; 
        result.Y *= num; 
        result.Z *= num;
        return result;
	}
	
	void Vector3::Normalize(Vector3 value, out Vector3& result)
	{
		float length = value.Length(); 
        if(length == 0) 
            return; 
        float num = 1 / length; 
        result.X *= num; 
        result.Y *= num; 
        result.Z *= num;
	}
	
	Vector3 Vector3::Reflect(Vector3 vector, Vector3 normal)
	{
		Vector3 result; 
        Reflect(vector, normal, result);
        return result; 
	}
	
	void Vector3::Reflect(Vector3 vector, Vector3 normal, out Vector3& result)
	{
		float dot = ((vector.X * normal.X) + (vector.Y * normal.Y)) + (vector.Z * normal.Z); 
  
        result.X = vector.X - ((2.0f * dot) * normal.X); 
        result.Y = vector.Y - ((2.0f * dot) * normal.Y); 
        result.Z = vector.Z - ((2.0f * dot) * normal.Z); 
    }
    
    Vector3 Vector3::SmoothStep(Vector3 value1, Vector3 value2, float amount)
    {
	    Vector3 result;
	    SmoothStep(value1, value2, amount, result);
	    return result;
    }
    
    void Vector3::SmoothStep(Vector3 value1, Vector3 value2, float amount, out Vector3& result)
    {
	    result.X = MathHelper::SmoothStep(value1.X, value2.X, amount);
	    result.Y = MathHelper::SmoothStep(value1.Y, value2.Y, amount);
	    result.Z = MathHelper::SmoothStep(value1.Z, value2.Z, amount);
    }
    
    Vector3 Vector3::Subtract(Vector3 value1, Vector3 value2)
    {
	    Vector3 result;
	    Subtract(value1, value2, result);
	    return result;
    }
    
    void Vector3::Subtract(Vector3 value1, Vector3 value2, out Vector3& result)
	{
		result.X = value1.X - value2.X;
	    result.Y = value1.Y - value2.Y;
	    result.Z = value1.Z - value2.Z;
	}

	const String& Vector3::ToString() const
	{
		return String::Format("{X:%f Y:%f Z:%f}", X, Y, Z);
	}
	
	Vector3 Vector3::Transform(Vector3 position, Matrix matrix)
	{
		Vector3 result;
		Transform(position, matrix, result);
		return result;
	}
	
	void Vector3::Transform(Vector3 position, Matrix matrix, out Vector3& result)
	{
		Vector4 vector; 
  
        vector.X = (((vector.X * matrix.M11) + (vector.Y * matrix.M21)) + (vector.Z * matrix.M31)) + matrix.M41; 
        vector.Y = (((vector.X * matrix.M12) + (vector.Y * matrix.M22)) + (vector.Z * matrix.M32)) + matrix.M42; 
        vector.Z = (((vector.X * matrix.M13) + (vector.Y * matrix.M23)) + (vector.Z * matrix.M33)) + matrix.M43; 
        vector.W = 1 / ((((vector.X * matrix.M14) + (vector.Y * matrix.M24)) + (vector.Z * matrix.M34)) + matrix.M44);
        
        result.X = vector.X * vector.W;
        result.Y = vector.Y * vector.W;
        result.Z = vector.Z * vector.W;
	}
	
	Vector3 Vector3::Transform(Vector3 position, Quaternion rotation)
	{
		Vector3 result;
		Transform(position, rotation, result);
		return result;
	}
	
	void Vector3::Transform(Vector3 position, Quaternion rotation, out Vector3& result)
	{
		Vector3 xyz = Vector3(rotation.X,rotation.Y, rotation.Z), temp, temp2;
		Cross(xyz, position, temp);
		Multiply(position, rotation.W, temp2);
		Add(temp, temp2, temp);
		Cross(xyz, temp, temp);
		Multiply(temp, 2, temp);
		Add(position, temp, result);
	}
	
	void Vector3::Transform(const Vector3 sourceArray[], const int sourceIndex, const Matrix matrix, Vector3 destinationArray[], const int destinationIndex, const int length)
	{
		sassert(sourceArray != null, String::Format("sourceArray; %s", FrameworkResources::ArgumentNull_Generic));

		sassert(destinationArray != null, String::Format("destinationArray; %s", FrameworkResources::ArgumentNull_Generic));

		for (int i = sourceIndex, j = destinationIndex; i < (sourceIndex + length); i++, j++)
		{
			Transform(sourceArray[i], matrix, destinationArray[j]);
		}
	}
	
	void Vector3::Transform(const Vector3 sourceArray[], const int sourceIndex, const Quaternion rotation, Vector3 destinationArray[], const int destinationIndex, const int length)
	{
		sassert(sourceArray != null, String::Format("sourceArray; %s", FrameworkResources::ArgumentNull_Generic));

		sassert(destinationArray != null, String::Format("destinationArray; %s", FrameworkResources::ArgumentNull_Generic));

		for (int i = sourceIndex, j = destinationIndex; i < (sourceIndex + length); i++, j++)
		{
			Transform(sourceArray[i], rotation, destinationArray[j]);
		}
	}
	
	Vector3 Vector3::TransformNormal(Vector3 normal, Matrix matrix)
	{
		Vector3 result; 
		TransformNormal(normal, matrix, result);
        return result; 
	}
	
	void Vector3::TransformNormal(Vector3 normal, Matrix matrix, out Vector3& result)
	{
		result.X = ((normal.X * matrix.M11) + (normal.Y * matrix.M21)) + (normal.Z * matrix.M31); 
        result.Y = ((normal.X * matrix.M12) + (normal.Y * matrix.M22)) + (normal.Z * matrix.M32); 
        result.Z = ((normal.X * matrix.M13) + (normal.Y * matrix.M23)) + (normal.Z * matrix.M33); 
	}
	
	void Vector3::TransformNormal(const Vector3 sourceArray[], const int sourceIndex, const Matrix matrix, Vector3 destinationArray[], const int destinationIndex, const int length)
	{
		sassert(sourceArray != null, String::Format("sourceArray; %s", FrameworkResources::ArgumentNull_Generic));

		sassert(destinationArray != null, String::Format("destinationArray; %s", FrameworkResources::ArgumentNull_Generic));

		for(int i = sourceIndex, j = destinationIndex; i < (sourceIndex + length); i++, j++)
		{
			TransformNormal(sourceArray[i], matrix, destinationArray[j]);
		}
	}
	
	Vector3 Vector3::operator+(const Vector3& other)
	{
		Vector3 result;
		result.X = X + other.X;
		result.Y = Y + other.Y;
		result.Z = Z + other.Z;
		return result;
	}
	
	Vector3 Vector3::operator/(const float divider)
	{
		Vector3 result;
		result.X = X / divider;
		result.Y = Y / divider;
		result.Z = Z / divider;
		return result;
	}
	
	Vector3 Vector3::operator/(const Vector3& other)
	{
		Vector3 result;
		result.X = X / other.X;
		result.Y = Y / other.Y;
		result.Z = Z / other.Z;
		return result;
	}
	
	bool Vector3::operator==(const Vector3& other) const
	{
		return Equals(other);
	}
	
	bool Vector3::operator!=(const Vector3& other) const
	{
		return !Equals(other);
	}
	
	Vector3 Vector3::operator*(const float scaleFactor)
	{
		Vector3 result;
		result.X = X * scaleFactor;
		result.Y = Y * scaleFactor;
		result.Z = Z * scaleFactor;
		return result;
	}
	
	Vector3 Vector3::operator*(const Vector3& other)
	{
		Vector3 result;
		result.X = X * other.X;
		result.Y = Y * other.Y;
		result.Z = Z * other.Z;
		return result;
	}
	
	Vector3 Vector3::operator-(const Vector3& other)
	{
		return Vector3(X -= other.X, Y -= other.Y, Z -= other.Z);
	}
	
	Vector3 Vector3::operator-()
	{
		return Vector3(-X, -Y, -Z);
	}
}
