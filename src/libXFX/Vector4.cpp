// Copyright (C) 2010-2012, XFX Team
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

#if DEBUG
#include <stdio.h>
#endif

using namespace System;

namespace XFX
{
	const Vector4 Vector4::One = Vector4(1,1,1,1);
	const Vector4 Vector4::UnitW = Vector4(0,0,0,1);
	const Vector4 Vector4::UnitX = Vector4(1,0,0,0);
	const Vector4 Vector4::UnitY = Vector4(0,1,0,0);
	const Vector4 Vector4::UnitZ = Vector4(0,0,1,0);
	const Vector4 Vector4::Zero = Vector4(0,0,0,0);

	Vector4::Vector4(float value)
	{
		W = value;
		X = value;
		Y = value;
		Z = value;
	}

	Vector4::Vector4(float x, float y, float z, float w)
	{
		W = w;
		X = x;
		Y = y;
		Z = z;
	}

	Vector4::Vector4(Vector2 value, float z, float w)
	{
		W = w;
		X = value.X;
		Y = value.Y;
		Z = z;
	}

	Vector4::Vector4(Vector3 value, float w)
	{
		W = w;
		X = value.X;
		Y = value.Y;
		Z = value.Z;
	}
	
	Vector4::Vector4(const Vector4 &obj)
	{
		W = obj.W;
		X = obj.X;
		Y = obj.Y;
		Z = obj.Z;
	}
	
	Vector4::Vector4()
	{
		W = 0;
		X = 0;
		Y = 0;
		Z = 0;
	}

	Vector4 Vector4::Add(Vector4 vector1, Vector4 vector2)
	{
		return Vector4(vector1.X + vector2.X,
				vector1.Y + vector2.Y,
				vector1.Z + vector2.Z,
				vector1.W + vector2.W);
	}

	void Vector4::Add(Vector4 vector1, Vector4 vector2, out Vector4 result)
	{
		result.W = vector1.W + vector2.W;
		result.X = vector1.X + vector2.X;
		result.Y = vector1.Y + vector2.Y;
		result.Z = vector1.Z + vector2.Z;
	}
	
	Vector4 Vector4::Baricentric(Vector4 value1, Vector4 value2, Vector4 value3, float amount1, float amount2)
	{
		Vector4 result; 
        result.X = MathHelper::Baricentric(value1.X, value2.X, value3.X, amount1, amount2); 
        result.Y = MathHelper::Baricentric(value1.Y, value2.Y, value3.Y, amount1, amount2);
        result.Z = MathHelper::Baricentric(value1.Z, value2.Z, value3.Z, amount1, amount2);
        result.W = MathHelper::Baricentric(value1.W, value2.W, value3.W, amount1, amount2); 
        return result; 
	}
	
	void Vector4::Baricentric(Vector4 value1, Vector4 value2, Vector4 value3, float amount1, float amount2, out Vector4 result)
	{
		result.X = MathHelper::Baricentric(value1.X, value2.X, value3.X, amount1, amount2); 
        result.Y = MathHelper::Baricentric(value1.Y, value2.Y, value3.Y, amount1, amount2);
        result.Z = MathHelper::Baricentric(value1.Z, value2.Z, value3.Z, amount1, amount2);
        result.W = MathHelper::Baricentric(value1.W, value2.W, value3.W, amount1, amount2); 
	}
	
	Vector4 Vector4::CatmullRom(Vector4 value1, Vector4 value2, Vector4 value3, Vector4 value4, float amount)
	{
		Vector4 result;
		result.X = MathHelper::CatmullRom(value1.X, value2.X, value3.X, value4.X, amount);
		result.Y = MathHelper::CatmullRom(value1.Y, value2.Y, value3.Y, value4.Y, amount);
		result.Z = MathHelper::CatmullRom(value1.Z, value2.Z, value3.Z, value4.Z, amount);
		result.W = MathHelper::CatmullRom(value1.W, value2.W, value3.W, value4.W, amount);
		return result;
	}
	
	void Vector4::CatmullRom(Vector4 value1, Vector4 value2, Vector4 value3, Vector4 value4, float amount, out Vector4 result)
	{
		result.X = MathHelper::CatmullRom(value1.X, value2.X, value3.X, value4.X, amount);
		result.Y = MathHelper::CatmullRom(value1.Y, value2.Y, value3.Y, value4.Y, amount);
		result.Z = MathHelper::CatmullRom(value1.Z, value2.Z, value3.Z, value4.Z, amount);
		result.W = MathHelper::CatmullRom(value1.W, value2.W, value3.W, value4.W, amount);
	}
	
	Vector4 Vector4::Clamp(Vector4 value1, Vector4 min, Vector4 max)
	{
		Vector4 result;
		Clamp(value1, min, max, result); 
		return result;
	}
	
	void Vector4::Clamp(Vector4 value1, Vector4 min, Vector4 max, out Vector4 result)
	{
		result = Vector4( 
            MathHelper::Clamp(value1.X, min.X, max.X), 
            MathHelper::Clamp(value1.Y, min.Y, max.Y), 
            MathHelper::Clamp(value1.Z, min.Z, max.Z), 
            MathHelper::Clamp(value1.W, min.W, max.W)); 
    }
	
	float Vector4::Distance(Vector4 value1, Vector4 value2) 
    { 
        return Math::Sqrt(DistanceSquared(value1, value2)); 
    }
    
    void Vector4::Distance(Vector4 value1, Vector4 value2, out float result) 
    { 
        result = Math::Sqrt(DistanceSquared(value1, value2)); 
    }  
	
	float Vector4::DistanceSquared(Vector4 value1, Vector4 value2) 
    { 
        float result = (value1.W - value2.W) * (value1.W - value2.W) + 
            (value1.X - value2.X) * (value1.X - value2.X) + 
            (value1.Y - value2.Y) * (value1.Y - value2.Y) + 
            (value1.Z - value2.Z) * (value1.Z - value2.Z);
        return result; 
    } 
	
	void Vector4::DistanceSquared(Vector4 value1, Vector4 value2, out float result) 
    { 
        result = (value1.W - value2.W) * (value1.W - value2.W) + 
            (value1.X - value2.X) * (value1.X - value2.X) + 
            (value1.Y - value2.Y) * (value1.Y - value2.Y) + 
            (value1.Z - value2.Z) * (value1.Z - value2.Z); 
    } 

	Vector4 Vector4::Divide(Vector4 value, float scale)
	{
		return Vector4(value.X / scale, value.Y / scale, value.Z / scale, value.W / scale);
	}

	void Vector4::Divide(Vector4 value, float scale, out Vector4 result)
	{
		result.W = value.W / scale;
		result.X = value.X / scale;
		result.Y = value.Y / scale;
		result.Z = value.Z / scale;
	}

	Vector4 Vector4::Divide(Vector4 vector1, Vector4 vector2)
	{
		return Vector4(vector1.X / vector2.X, vector1.Y / vector2.Y, vector1.Z / vector2.Z, vector1.W / vector2.W);
	}

	void Vector4::Divide(Vector4 vector1, Vector4 vector2, out Vector4 result)
	{
		result.W = vector1.W / vector2.W;
		result.X = vector1.X / vector2.X;
		result.Y = vector1.Y / vector2.Y;
		result.Z = vector1.Z / vector2.Z;
	}

	bool Vector4::Equals(Vector4 other)
	{
		return ((W == other.W) && (X == other.X) && (Y == other.Y) && (Z == other.Z));
	}
	
	int Vector4::GetHashCode()
	{
		return ((int)X ^ (int)Y ^ (int)Z ^ (int)W);
	}
	
	Vector4 Vector4::Hermite(Vector4 value1, Vector4 tangent1, Vector4 value2, Vector4 tangent2, float amount) 
    { 
        Vector4 result; 
        Hermite(value1, tangent1, value2, tangent2, amount, result); 
        return result; 
    }
    
    void Vector4::Hermite(Vector4 value1, Vector4 tangent1, Vector4 value2, Vector4 tangent2, float amount, out Vector4 result) 
    { 
        result.W = MathHelper::Hermite(value1.W, tangent1.W, value2.W, tangent2.W, amount); 
        result.X = MathHelper::Hermite(value1.X, tangent1.X, value2.X, tangent2.X, amount); 
        result.Y = MathHelper::Hermite(value1.Y, tangent1.Y, value2.Y, tangent2.Y, amount); 
        result.Z = MathHelper::Hermite(value1.Z, tangent1.Z, value2.Z, tangent2.Z, amount); 
    } 
    
    float Vector4::Length() 
    { 
        return Math::Sqrt((X * X) + (Y * Y) + (Z * Z) + (W * W)); 
    } 
  
    float Vector4::LengthSquared() 
    { 
    	return (X * X) + (Y * Y) + (Z * Z) + (W * W); 
    } 
    
    Vector4 Vector4::Lerp(Vector4 value1, Vector4 value2, float amount)
    {
	    Vector4 result;
	    Lerp(value1, value2, amount, result);
	    return result;
    }
    
    void Vector4::Lerp(Vector4 value1, Vector4 value2, float amount, out Vector4 result) 
    { 
        result = Vector4( 
            MathHelper::Lerp(value1.X, value2.X, amount), 
            MathHelper::Lerp(value1.Y, value2.Y, amount), 
            MathHelper::Lerp(value1.Z, value2.Z, amount), 
            MathHelper::Lerp(value1.W, value2.W, amount)); 
    }
    
    Vector4 Vector4::Max(Vector4 value1, Vector4 value2)
    {
	    Vector4 result;
	    Max(value1, value2, result);
	    return result;
    }
    
    void Vector4::Max(Vector4 value1, Vector4 value2, out Vector4 result) 
    { 
        result = Vector4( 
            MathHelper::Max(value1.X, value2.X), 
            MathHelper::Max(value1.Y, value2.Y), 
            MathHelper::Max(value1.Z, value2.Z), 
            MathHelper::Max(value1.W, value2.W)); 
    }
    
    Vector4 Vector4::Min(Vector4 value1, Vector4 value2)
    {
	    Vector4 result;
	    Min(value1, value2, result);
	    return result;
    }
    
    void Vector4::Min(Vector4 value1, Vector4 value2, out Vector4 result) 
    { 
        result = Vector4( 
            MathHelper::Min(value1.X, value2.X), 
            MathHelper::Min(value1.Y, value2.Y), 
            MathHelper::Min(value1.Z, value2.Z), 
            MathHelper::Min(value1.W, value2.W)); 
    }
    
    Vector4 Vector4::Multiply(Vector4 value1, float scaleFactor)
    {
	    Vector4 result;
	    Multiply(value1, scaleFactor, result);
	    return result;
    }
    
    void Vector4::Multiply(Vector4 value1, float scaleFactor, out Vector4 result)
    {
		result.X = value1.X * scaleFactor;
	    result.Y = value1.Y * scaleFactor;
	    result.Z = value1.Z * scaleFactor;
	    result.W = value1.W * scaleFactor;
    }
    
    Vector4 Vector4::Multiply(Vector4 value1, Vector4 value2)
    {
	    Vector4 result;
	    Multiply(value1, value2, result);
	    return result;
    }
    
    void Vector4::Multiply(Vector4 value1, Vector4 value2, out Vector4 result) 
    { 
		result.W = value1.W * value2.W; 
        result.X = value1.X * value2.X; 
        result.Y = value1.Y * value2.Y; 
        result.Z = value1.Z * value2.Z;
    }
    
    Vector4 Vector4::Negate(Vector4 value)
    {
	    Vector4 result;
		Negate(value, result);
		return result;
    }
    
    void Vector4::Negate(Vector4 value, out Vector4 result)
    {
	    result = Vector4(-value.X, -value.Y, -value.Z, -value.W);
    }
    
    void Vector4::Normalize()
    {
	    float length = Length(); 
        if( length == 0 ) 
            return; 
        float num = 1 / length; 
        X *= num; 
        Y *= num; 
        Z *= num; 
        W *= num; 
    }
    
    Vector4 Vector4::Normalize(Vector4 value)
    {
	    Normalize(value, value);
	    return value;
    }
    
    void Vector4::Normalize(Vector4 value, out Vector4 result)
    {
	    float factor; 
        float length = value.Length();
        factor = 1.0f / length;
  
        result.W = value.W * factor; 
        result.X = value.X * factor; 
        result.Y = value.Y * factor; 
        result.Z = value.Z * factor; 
    }

	Vector4 Vector4::SmoothStep(Vector4 value1, Vector4 value2, float amount)
	{
		return Vector4(
			MathHelper::SmoothStep(value1.X, value2.X, amount),
			MathHelper::SmoothStep(value1.Y, value2.Y, amount),
			MathHelper::SmoothStep(value1.Z, value2.Z, amount),
			MathHelper::SmoothStep(value1.W, value2.W, amount)); 
	}

	void Vector4::SmoothStep(Vector4 value1, Vector4 value2, float amount, out Vector4 result)
	{
		result = Vector4(
			MathHelper::SmoothStep(value1.X, value2.X, amount),
			MathHelper::SmoothStep(value1.Y, value2.Y, amount),
			MathHelper::SmoothStep(value1.Z, value2.Z, amount),
			MathHelper::SmoothStep(value1.W, value2.W, amount)); 
	}

	Vector4 Vector4::Subtract(Vector4 vector1, Vector4 vector2)
	{
		vector1.X -= vector2.X;
		vector1.Y -= vector2.Y;
		vector1.Z -= vector2.Z;
		vector1.W -= vector2.W;
		return vector1;
	}

	void Vector4::Subtract(Vector4 vector1, Vector4 vector2, out Vector4 result)
	{
		result.X = vector1.X - vector2.X;
		result.Y = vector1.Y - vector2.Y;
		result.Z = vector1.Z - vector2.Z;
		result.W = vector1.W - vector2.W;
	}

	void Vector4::Transform(Vector4 sourceArray[], Quaternion rotation, Vector4 destinationArray[])
	{
		if (Array::Length(destinationArray) < Array::Length(sourceArray))
		{
#if DEBUG
			printf("ARGUMENT in function %s, at line %i in file %s: %s\n", __FUNCTION__, __LINE__, __FILE__, "destinationArray too small");
#endif
			return;
		}

		for(int i = 0; i < Array::Length(sourceArray)-1; i++)
		{
			Transform(sourceArray[i], rotation, destinationArray[i]);
		}
	}

	void Vector4::Transform(Vector4 sourceArray[], int sourceIndex, Quaternion rotation, Vector4 destinationArray[], int destinationIndex, int length)
	{
		for(int i = sourceIndex, j = destinationIndex; i < (sourceIndex + length); i++, j++)
		{
			Transform(sourceArray[i], rotation, destinationArray[j]);
		}
	}

	void Vector4::Transform(Vector4 sourceArray[], Matrix matrix, Vector4 destinationArray[])
	{
		if (Array::Length(destinationArray) < Array::Length(sourceArray))
		{
#if DEBUG
			printf("ARGUMENT in function %s, at line %i in file %s: %s\n", __FUNCTION__, __LINE__, __FILE__, "destinationArray too small");
#endif
			return;
		}

		for(int i = 0; i < Array::Length(sourceArray)-1; i++)
		{
			Transform(sourceArray[i], matrix, destinationArray[i]);
		}
	}

	void Vector4::Transform(Vector4 sourceArray[], int sourceIndex, Matrix matrix, Vector4 destinationArray[], int destinationIndex, int length)
	{
		for(int i = sourceIndex, j = destinationIndex; i < (sourceIndex + length); i++, j++)
		{
			Transform(sourceArray[i], matrix, destinationArray[i]);
		}
	}

	Vector4 Vector4::Transform(Vector4 vector, Quaternion rotation)
	{
		Vector4 result;
		Transform(vector, rotation, result);
		return result;
	}

	void Vector4::Transform(Vector4 vector, Quaternion rotation, out Vector4 result)
	{
		float x = rotation.X + rotation.X;
		float y = rotation.Y + rotation.Y;
		float z = rotation.Z + rotation.Z;
		float wx = rotation.W * x;
		float wy = rotation.W * y;
		float wz = rotation.W * z;
		float xx = rotation.X * x;
		float xy = rotation.X * y;
		float xz = rotation.X * z;
		float yy = rotation.Y * y;
		float yz = rotation.Y * z;
		float zz = rotation.Z * z;
		result.X = ((vector.X * ((1.0f - yy) - zz)) + (vector.Y * (xy - wz))) + (vector.Z * (xz + wy));
		result.Y = ((vector.X * (xy + wz)) + (vector.Y * ((1.0f - xx) - zz))) + (vector.Z * (yz - wx));
		result.Z = ((vector.X * (xz - wy)) + (vector.Y * (yz + wx))) + (vector.Z * ((1.0f - xx) - yy));
		result.W = vector.W;
	}

	Vector4 Vector4::Transform(Vector3 vector, Quaternion rotation)
	{
		Vector4 result;
		Transform(vector, rotation, result);
		return result;
	}

	void Vector4::Transform(Vector3 vector, Quaternion rotation, out Vector4 result)
	{
		float x = rotation.X + rotation.X;
		float y = rotation.Y + rotation.Y;
		float z = rotation.Z + rotation.Z;
		float wx = rotation.W * x;
		float wy = rotation.W * y;
		float wz = rotation.W * z;
		float xx = rotation.X * x;
		float xy = rotation.X * y;
		float xz = rotation.X * z;
		float yy = rotation.Y * y;
		float yz = rotation.Y * z;
		float zz = rotation.Z * z;
		result.X = ((vector.X * ((1.0f - yy) - zz)) + (vector.Y * (xy - wz))) + (vector.Z * (xz + wy));
		result.Y = ((vector.X * (xy + wz)) + (vector.Y * ((1.0f - xx) - zz))) + (vector.Z * (yz - wx));
		result.Z = ((vector.X * (xz - wy)) + (vector.Y * (yz + wx))) + (vector.Z * ((1.0f - xx) - yy));
		result.W = 1.0f;  
	}

	Vector4 Vector4::Transform(Vector2 vector, Quaternion rotation)
	{
		Vector4 result;
		Transform(vector, rotation, result);
		return result;
	}

	void Vector4::Transform(Vector2 vector, Quaternion rotation, out Vector4 result)
	{
		float x = rotation.X + rotation.X;
		float y = rotation.Y + rotation.Y;
		float z = rotation.Z + rotation.Z;
		float wx = rotation.W * x;
		float wy = rotation.W * y;
		float wz = rotation.W * z;
		float xx = rotation.X * x;
		float xy = rotation.X * y;
		float xz = rotation.X * z;
		float yy = rotation.Y * y;
		float yz = rotation.Y * z;
		float zz = rotation.Z * z;
		result.X = ((vector.X * ((1.0f - yy) - zz)) + (vector.Y * (xy - wz)));
		result.Y = ((vector.X * (xy + wz)) + (vector.Y * ((1.0f - xx) - zz)));
		result.Z = ((vector.X * (xz - wy)) + (vector.Y * (yz + wx)));
		result.W = 1.0f;
	}

	Vector4 Vector4::Transform(Vector4 vector, Matrix matrix)
	{
		Transform(vector, matrix, vector);
		return vector;
	}

	void Vector4::Transform(Vector4 vector, Matrix matrix, Vector4 result)
	{
		result = Vector4((vector.X * matrix.M11) + (vector.Y * matrix.M21) + (vector.Z * matrix.M31) + (vector.W * matrix.M41),
						 (vector.X * matrix.M12) + (vector.Y * matrix.M22) + (vector.Z * matrix.M32) + (vector.W * matrix.M42),
						 (vector.X * matrix.M13) + (vector.Y * matrix.M23) + (vector.Z * matrix.M33) + (vector.W * matrix.M43),
						 (vector.X * matrix.M14) + (vector.Y * matrix.M24) + (vector.Z * matrix.M34) + (vector.W * matrix.M44));
	}

	Vector4 Vector4::Transform(Vector3 vector, Matrix matrix)
	{
		Vector4 result;
		Transform(vector, matrix, result);
		return result;
	}

	void Vector4::Transform(Vector3 vector, Matrix matrix, out Vector4 result)
	{
		result = Vector4((vector.X * matrix.M11) + (vector.Y * matrix.M21) + (vector.Z * matrix.M31) + matrix.M41,
						 (vector.X * matrix.M12) + (vector.Y * matrix.M22) + (vector.Z * matrix.M32) + matrix.M42,
						 (vector.X * matrix.M13) + (vector.Y * matrix.M23) + (vector.Z * matrix.M33) + matrix.M43,
						 (vector.X * matrix.M14) + (vector.Y * matrix.M24) + (vector.Z * matrix.M34) + matrix.M44); 
	}

	Vector4 Vector4::Transform(Vector2 vector, Matrix matrix)
	{
		Vector4 result;
		Transform(vector, matrix, result);
		return result;
	}

	void Vector4::Transform(Vector2 vector, Matrix matrix, out Vector4 result)
	{
		result = Vector4((vector.X * matrix.M11) + (vector.Y * matrix.M21) + matrix.M41,
						 (vector.X * matrix.M12) + (vector.Y * matrix.M22) + matrix.M42,
						 (vector.X * matrix.M13) + (vector.Y * matrix.M23) + matrix.M43,
						 (vector.X * matrix.M14) + (vector.Y * matrix.M24) + matrix.M44);  
	}
	//
	// Operators
	//
	const Vector4 Vector4::operator-(const Vector4 other)
	{
		X -= other.X;
		Y -= other.Y;
		Z -= other.Z;
		W -= other.W;
		return *this;
	}
	
	const Vector4 Vector4::operator-()
	{
		return Vector4(-X, -Y, -Z, -W);
	}

	bool Vector4::operator!=(const Vector4 other)
	{
		return !Equals(other);
	}

	const Vector4 Vector4::operator*(const float scaleFactor)
	{
		W *= scaleFactor;
		X *= scaleFactor;
		Y *= scaleFactor;
		Z *= scaleFactor;
		return *this;
	}

	const Vector4 Vector4::operator*(const Vector4 other)
	{
		W *= other.W;
		X *= other.X;
		Y *= other.Y;
		Z *= other.Z;  
		return *this;
	}

	const Vector4 Vector4::operator/(const float scaleFactor)
	{
		W /= scaleFactor;
		X /= scaleFactor;
		Y /= scaleFactor;
		X /= scaleFactor;
		return *this;
	}

	const Vector4 Vector4::operator/(const Vector4 other)
	{
		W /= other.W;
		X /= other.X;
		Y /= other.Y;
		Z /= other.Z;
		return *this;
	}

	const Vector4 Vector4::operator+(const Vector4 other)
	{
		X += other.X;
		Y += other.Y;
		Z += other.Z;
		W += other.W;
		return *this;
	}

	bool Vector4::operator==(const Vector4 other)
	{
		return Equals(other);
	}
	
	Vector4 Vector4::operator=(const Vector4 other)
	{
		X = other.X;
		Y = other.Y;
		Z = other.Z;
		W = other.W;
		return *this;
	}
}
