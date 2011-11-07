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
#include <Vector4.h>
#include <System/Array.h>
#include <System/Math.h>

#if DEBUG
#include <stdio.h>
#endif

using namespace System;

namespace XFX
{	
	const Vector2 Vector2::One = Vector2(1,1);
	const Vector2 Vector2::Zero = Vector2(0,0);

	Vector2::Vector2(float x, float y)
	{
		X = x;
		Y = y;
	}

	Vector2::Vector2(float value)
	{
		X = value;
		Y = value;
	}
	
	Vector2::Vector2(const Vector2 &obj)
	{
		X = obj.X;
		Y = obj.Y;
	}
	
	Vector2::Vector2()
	{
		X = 0;
		Y = 0;
	}

	Vector2 Vector2::Add(Vector2 value1, Vector2 value2)
	{
		return Vector2(value1.X + value2.X, value1.Y + value2.Y);
	}

	void Vector2::Add(Vector2 value1, Vector2 value2, Vector2 result)
	{
		result.X = value1.X + value2.X;
		result.Y = value1.Y + value2.Y;
	}

	Vector2 Vector2::Baricentric(Vector2 value1, Vector2 value2, Vector2 value3, float amount1, float amount2)
	{
		return Vector2(MathHelper::Baricentric(value1.X, value2.X, value3.X, amount1, amount2),
			MathHelper::Baricentric(value1.Y, value2.Y, value3.Y, amount1, amount2));
	}

	void Vector2::Baricentric(Vector2 value1, Vector2 value2, Vector2 value3, float amount1, float amount2, out Vector2 result)
	{
		result.X = MathHelper::Baricentric(value1.X, value2.X, value3.X, amount1, amount2);
		result.Y = MathHelper::Baricentric(value1.Y, value2.Y, value3.Y, amount1, amount2);
	}

	Vector2 Vector2::CatmullRom(Vector2 value1, Vector2 value2, Vector2 value3, Vector2 value4, float amount)
	{
		return Vector2(MathHelper::CatmullRom(value1.X, value2.X, value3.X, value4.X, amount),
			MathHelper::CatmullRom(value1.Y, value2.Y, value3.Y, value4.Y, amount));
	}

	void Vector2::CatmullRom(Vector2 value1, Vector2 value2, Vector2 value3, Vector2 value4, float amount, out Vector2 result)
	{
		result.X = MathHelper::CatmullRom(value1.X, value2.X, value3.X, value4.X, amount);
		result.Y = MathHelper::CatmullRom(value1.Y, value2.Y, value3.Y, value4.Y, amount);
	}

	Vector2 Vector2::Clamp(Vector2 value, Vector2 min, Vector2 max)
	{
		return Vector2(MathHelper::Clamp(value.X, min.X, max.X), MathHelper::Clamp(value.Y, min.Y, max.Y));
	}

	void Vector2::Clamp(Vector2 value, Vector2 min, Vector2 max, out Vector2 result)
	{
		result.X = MathHelper::Clamp(value.X, min.X, max.X);
		result.Y = MathHelper::Clamp(value.Y, min.Y, max.Y);
	}
	
	float Vector2::Distance(Vector2 value1, Vector2 value2)
	{
		float x = value1.X - value2.X; 
        float y = value1.Y - value2.Y;
        return Math::Sqrt((x * x) + (y * y));
	}
	
	void Vector2::Distance(Vector2 value1, Vector2 value2, out float result)
	{
		float x = value1.X - value2.X; 
        float y = value1.Y - value2.Y;
        result = Math::Sqrt((x * x) + (y * y));
	}
	
	float Vector2::DistanceSquared(Vector2 value1, Vector2 value2)
	{
		float x = value1.X - value2.X; 
        float y = value1.Y - value2.Y;
        return (x * x) + (y * y);
	}
	
	void Vector2::DistanceSquared(Vector2 value1, Vector2 value2, out float result)
	{
		float x = value1.X - value2.X; 
        float y = value1.Y - value2.Y;
        result = (x * x) + (y * y);
	}
	
	float Vector2::Dot(Vector2 value1, Vector2 value2)
	{
		return (value1.X * value2.X + value1.Y * value2.Y); 
	}
	
	void Vector2::Dot(Vector2 value1, Vector2 value2, out float result)
	{
		result = (value1.X * value2.X + value1.Y * value2.Y);
	}

	bool Vector2::Equals(Vector2 other)
	{
		return ((X == other.X) & (Y == other.Y));
	}
	
	int Vector2::GetHashCode()
	{
		return (int)X ^ (int)Y;
	}
	
	Vector2 Vector2::Hermite(Vector2 value1, Vector2 tangent1, Vector2 value2, Vector2 tangent2, float amount)
	{
		return Vector2(MathHelper::Hermite(value1.X,tangent1.X,value2.X,tangent2.X,amount),MathHelper::Hermite(value1.Y,tangent1.Y,value2.Y,tangent2.Y,amount));
	}
	
	void Vector2::Hermite(Vector2 value1, Vector2 tangent1, Vector2 value2, Vector2 tangent2, float amount, out Vector2 result)
	{
		result.X = MathHelper::Hermite(value1.X,tangent1.X,value2.X,tangent2.X,amount);
		result.Y = MathHelper::Hermite(value1.Y,tangent1.Y,value2.Y,tangent2.Y,amount);
	}
	
	float Vector2::Length()
	{
		return Math::Sqrt((X*X) + (Y*Y));
	}
	
	float Vector2::LengthSquared()
	{
		return (X * X) + (Y * Y);
	}
	
	Vector2 Vector2::Lerp(Vector2 value1, Vector2 value2, float amount)
	{
		return Vector2(MathHelper::Lerp(value1.X, value2.X, amount), MathHelper::Lerp(value1.Y, value2.Y, amount));
	}
	
	void Vector2::Lerp(Vector2 value1, Vector2 value2, float amount, out Vector2 result)
	{
		result.X = MathHelper::Lerp(value1.X, value2.X, amount);
		result.Y = MathHelper::Lerp(value1.Y, value2.Y, amount);
	}
	
	Vector2 Vector2::Max(Vector2 value1, Vector2 value2)
	{
		return Vector2((value1.X > value2.X) ? value1.X : value2.X,(value1.Y > value2.Y) ? value1.Y : value2.Y);
	}
	
	void Vector2::Max(Vector2 value1, Vector2 value2, out Vector2 result)
	{
		result.X = (value1.X > value2.X) ? value1.X : value2.X;
		result.Y = (value1.Y > value2.Y) ? value1.Y : value2.Y;
	}
	
	Vector2 Vector2::Min(Vector2 value1, Vector2 value2)
	{
		return Vector2((value1.X < value2.X) ? value1.X : value2.X, (value1.Y < value2.Y) ? value1.Y : value2.Y);
	}
	
	void Vector2::Min(Vector2 value1, Vector2 value2, out Vector2 result)
	{
		result.X = (value1.X < value2.X) ? value1.X : value2.X;
		result.Y = (value1.Y < value2.Y) ? value1.Y : value2.Y;
	}

	Vector2 Vector2::Multiply(Vector2 value, float scaleFactor)
	{
		return Vector2(value.X * scaleFactor, value.Y * scaleFactor);
	}

	void Vector2::Multiply(Vector2 value, float scaleFactor, out Vector2 result)
	{
		result.X = value.X * scaleFactor;
		result.Y = value.Y * scaleFactor;
	}

	Vector2 Vector2::Multiply(Vector2 value1, Vector2 value2)
	{
		return Vector2(value1.X * value2.X, value1.Y * value2.Y);
	}

	void Vector2::Multiply(Vector2 value1, Vector2 value2, out Vector2 result)
	{
		result.X = value1.X * value2.X;
		result.Y = value1.Y * value2.Y;
	}

	Vector2 Vector2::Negate(Vector2 value)
	{
		return Vector2(-value.X, -value.Y);
	}

	void Vector2::Negate(Vector2 value, out Vector2 result)
	{
		result.X = -value.X;
		result.Y = -value.Y;
	}
	
	void Vector2::Normalize()
	{
		float length = Length();
        	if( length == 0 ) 
            	return; 
        float num = 1 / length; 
        X *= num; 
        Y *= num; 
	}
	
	Vector2 Vector2::Normalize(Vector2 value)
	{
		float length = value.Length(); 
    	if(length == 0) 
        	return Vector2::Zero; 
        float num = 1 / length;
        return Vector2((value.X *= num), (value.Y *= num));
	}
	
	void Vector2::Normalize(Vector2 value, out Vector2 result)
	{
		float length = value.Length(); 
    	if(length == 0) 
        	return; 
        float num = 1 / length;
        result.X *= num;
        result.Y *= num;
	}
	
	Vector2 Vector2::Reflect(Vector2 vector, Vector2 normal)
	{
		float dp = Dot(vector, normal);	
		return Vector2(vector.X - normal.X * dp, vector.Y - normal.Y * dp);
	}
	
	void Vector2::Reflect(Vector2 vector, Vector2 normal, out Vector2 result)
	{
		float dp = Dot(vector, normal);
		result.X = vector.X - normal.X * dp;
		result.Y = vector.Y - normal.Y * dp;
	}
	
	Vector2 Vector2::SmoothStep(Vector2 value1, Vector2 value2, float amount)
	{
		return Vector2(
			MathHelper::SmoothStep(value1.X, value2.X, amount),
			MathHelper::SmoothStep(value1.Y, value2.Y, amount));
	}
	
	void Vector2::SmoothStep(Vector2 value1, Vector2 value2, float amount, out Vector2 result)
	{
		result.X = MathHelper::SmoothStep(value1.X, value2.X, amount);
		result.Y = MathHelper::SmoothStep(value1.Y, value2.Y, amount);
	}

	Vector2 Vector2::Subtract(Vector2 value1, Vector2 value2)
	{
		return Vector2(value1.X - value2.X, value1.Y - value2.Y);
	}
	
	void Vector2::Subtract(Vector2 value1, Vector2 value2, out Vector2 result)
	{
		result.X = value1.X - value2.X;
		result.Y = value1.Y - value2.Y;
	}
	
	Vector2 Vector2::Transform(Vector2 position, Matrix matrix)
	{
		Vector2 result; 
		Transform(position, matrix, result);
		return result; 
	}
	
	void Vector2::Transform(Vector2 position, Matrix matrix, out Vector2 result)
	{
		Vector4 vector; 
  
        vector.X = (vector.X * matrix.M11) + (vector.Y * matrix.M21) + matrix.M41; 
        vector.Y = (vector.X * matrix.M12) + (vector.Y * matrix.M22) + matrix.M42; 
        vector.Z = (vector.X * matrix.M13) + (vector.Y * matrix.M23) + matrix.M43; 
        vector.W = 1 / ((vector.X * matrix.M14) + (vector.Y * matrix.M24) + matrix.M44);
        
        result.X = vector.X * vector.W;
        result.Y = vector.Y * vector.W;
	}
	
	Vector2 Vector2::Transform(Vector2 position, Quaternion rotation)
	{
		Vector2 result;
		Transform(position, rotation, result);
		return result;
	}
	
	void Vector2::Transform(Vector2 position, Quaternion rotation, out Vector2 result)
	{
		Quaternion quat = Quaternion(position.X, position.Y, 0, 0), i, t;
		Quaternion::Inverse(rotation, i);
		Quaternion::Multiply(rotation, quat, t);
		Quaternion::Multiply(t, i, quat);
		
		result.X = quat.X;
		result.Y = quat.Y;
	}
	
	void Vector2::Transform(Vector2 sourceArray[], int sourceIndex, Matrix matrix, Vector2 destinationArray[], int destinationIndex, int length)
	{
		if (!sourceArray)
		{
#if DEBUG
			printf("ARGUMENT_NULL in function %s, at line %i in file %s, argument \"%s\"\n", __FUNCTION__, __LINE__, __FILE__, "sourceArray");
#endif
			return;
		}

		if (!destinationArray)
		{
#if DEBUG
			printf("ARGUMENT_NULL in function %s, at line %i in file %s, argument \"%s\"\n", __FUNCTION__, __LINE__, __FILE__, "destinationArray");
#endif
			return;
		}
		
		for(int i = sourceIndex, j = destinationIndex; i < (sourceIndex + length); i++, j++)
		{
			TransformNormal(sourceArray[i], matrix, destinationArray[j]);
		}
	}
	
	void Vector2::Transform(Vector2 sourceArray[], int sourceIndex, Quaternion rotation, Vector2 destinationArray[], int destinationIndex, int length)
	{
		if (!sourceArray)
		{
#if DEBUG
			printf("ARGUMENT_NULL in function %s, at line %i in file %s, argument \"%s\"\n", __FUNCTION__, __LINE__, __FILE__, "sourceArray");
#endif
			return;
		}

		if (!destinationArray)
		{
#if DEBUG
			printf("ARGUMENT_NULL in function %s, at line %i in file %s, argument \"%s\"\n", __FUNCTION__, __LINE__, __FILE__, "destinationArray");
#endif
			return;
		}
		
		for(int i = sourceIndex, j = destinationIndex; i < (sourceIndex + length); i++, j++)
		{
			Transform(sourceArray[i], rotation, destinationArray[j]);
		}
	}
	
	void Vector2::Transform(Vector2 sourceArray[], Matrix matrix, Vector2 destinationArray[])
	{
		if (!sourceArray)
		{
#if DEBUG
			printf("ARGUMENT_NULL in function %s, at line %i in file %s, argument \"%s\"\n", __FUNCTION__, __LINE__, __FILE__, "sourceArray");
#endif
			return;
		}

		if (!destinationArray)
		{
#if DEBUG
			printf("ARGUMENT_NULL in function %s, at line %i in file %s, argument \"%s\"\n", __FUNCTION__, __LINE__, __FILE__, "destinationArray");
#endif
			return;
		}
			
		if(Array::Length(destinationArray) < Array::Length(sourceArray))
		{
#if DEBUG
			printf("ARGUMENT in function %s, at line %i in file %s: %s\n", __FUNCTION__, __LINE__, __FILE__, "destinationArray too small.");
#endif
			return;
		}
			
		for(int i = 0; i < Array::Length(sourceArray); i++)
		{
			Transform(sourceArray[i], matrix, destinationArray[i]);
		}
	}
	
	void Vector2::Transform(Vector2 sourceArray[], Quaternion rotation, Vector2 destinationArray[])
	{
		if (!sourceArray)
		{
#if DEBUG
			printf("ARGUMENT_NULL in function %s, at line %i in file %s, argument \"%s\"\n", __FUNCTION__, __LINE__, __FILE__, "sourceArray");
#endif
			return;
		}

		if (!destinationArray)
		{
#if DEBUG
			printf("ARGUMENT_NULL in function %s, at line %i in file %s, argument \"%s\"\n", __FUNCTION__, __LINE__, __FILE__, "destinationArray");
#endif
			return;
		}
			
		if(Array::Length(destinationArray) < Array::Length(sourceArray))
		{
#if DEBUG
			printf("ARGUMENT in function %s, at line %i in file %s: %s\n", __FUNCTION__, __LINE__, __FILE__, "destinationArray too small.");
#endif
			return;
		}
			
		for(int i = 0; i < Array::Length(sourceArray); i++)
		{
			Transform(sourceArray[i], rotation, destinationArray[i]);
		}
	}
	
	Vector2 Vector2::TransformNormal(Vector2 normal, Matrix matrix)
	{
		Vector2 result; 
        result.X = (normal.X * matrix.M11) + (normal.Y * matrix.M21); 
        result.Y = (normal.X * matrix.M12) + (normal.Y * matrix.M22); 
  
        return result;  
	}
	
	void Vector2::TransformNormal(Vector2 normal, Matrix matrix, out Vector2 result)
	{
		result.X = (normal.X * matrix.M11) + (normal.Y * matrix.M21); 
        result.Y = (normal.X * matrix.M12) + (normal.Y * matrix.M22);
	}
	
	void Vector2::TransformNormal(Vector2 sourceArray[], int sourceIndex, Matrix matrix, Vector2 destinationArray[], int destinationIndex, int length)
	{
		if (!sourceArray)
		{
#if DEBUG
			printf("ARGUMENT_NULL in function %s, at line %i in file %s, argument \"%s\"\n", __FUNCTION__, __LINE__, __FILE__, "sourceArray");
#endif
			return;
		}

		if (!destinationArray)
		{
#if DEBUG
			printf("ARGUMENT_NULL in function %s, at line %i in file %s, argument \"%s\"\n", __FUNCTION__, __LINE__, __FILE__, "destinationArray");
#endif
			return;
		}
		
		for(int i = sourceIndex, j = destinationIndex; i < (sourceIndex + length); i++, j++)
		{
			TransformNormal(sourceArray[i], matrix, destinationArray[j]);
		}
	}
	
	void Vector2::TransformNormal(Vector2 sourceArray[], Matrix matrix, Vector2 destinationArray[])
	{
		if (!sourceArray)
		{
#if DEBUG
			printf("ARGUMENT_NULL in function %s, at line %i in file %s, argument \"%s\"\n", __FUNCTION__, __LINE__, __FILE__, "sourceArray");
#endif
			return;
		}

		if (!destinationArray)
		{
#if DEBUG
			printf("ARGUMENT_NULL in function %s, at line %i in file %s, argument \"%s\"\n", __FUNCTION__, __LINE__, __FILE__, "destinationArray");
#endif
			return;
		}
			
		if(Array::Length(destinationArray) < Array::Length(sourceArray))
		{
#if DEBUG
			printf("ARGUMENT in function %s, at line %i in file %s: %s\n", __FUNCTION__, __LINE__, __FILE__, "destinationArray too small.");
#endif
			return;
		}
			
		for(int i = 0; i < Array::Length(sourceArray); i++)
		{
			TransformNormal(sourceArray[i], matrix, destinationArray[i]);
		}
	}

	Vector2 Vector2::operator+(const Vector2 other)
	{
    	X += other.X;
    	Y += other.Y;
    	return *this;
	}
	
	Vector2 Vector2::operator/(float divider)
	{
		X /= divider;
		Y /= divider;
		return *this;
	}
	
	Vector2 Vector2::operator/(const Vector2 other)
	{
		X /= other.X;
		Y /= other.Y;
		return *this;
	}
	
	bool Vector2::operator==(const Vector2 other)
	{
		return Equals(other);
	}

	bool Vector2::operator!=(const Vector2 other)
	{
		return !Equals(other);
	}

	Vector2 Vector2::operator*(const float scaleFactor)
	{
		X *= scaleFactor;
		Y *= scaleFactor;
		return *this;
	}
	
	Vector2 Vector2::operator*(const Vector2 other)
	{
		X *= other.X;
		Y *= other.Y;
		return *this;
	}

	Vector2 Vector2::operator-(const Vector2 other)
	{
		X -= other.X;
		Y -= other.Y;
		return *this;
	}
	
	Vector2 Vector2::operator-()
	{
		X = -X;
		Y = -Y;
		return *this;
	}
	
	Vector2 Vector2::operator=(const Vector2 other)
	{
		X = other.X;
		Y = other.Y;
		return *this;
	}
}
