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
#include <Vector3.h>
#include <System/Math.h>

using namespace System;

namespace XFX
{
	const Quaternion Quaternion::Identity = Quaternion(0, 0, 0, 1);

	Quaternion::Quaternion(float x, float y, float z, float w)
		: W(w), X(x), Y(y), Z(z)
	{
	}

	Quaternion::Quaternion(Vector3 vectorPart, float scalarPart)
		: W(scalarPart), X(vectorPart.X), Y(vectorPart.Y), Z(vectorPart.Z)
	{
	}
	
	Quaternion::Quaternion(const Quaternion &obj)
		: W(obj.W), X(obj.X), Y(obj.Y), Z(obj.Z)
	{
	}
	
	Quaternion::Quaternion()
		: W(0), X(0), Y(0), Z(0)
	{
	}

	Quaternion Quaternion::Add(Quaternion quaternion1, Quaternion quaternion2)
	{
		return Quaternion(quaternion1.X + quaternion2.X,
					quaternion1.Y + quaternion2.Y,
					quaternion1.Z + quaternion2.Z,
					quaternion1.W + quaternion2.W);
	}

	void Quaternion::Add(Quaternion quaternion1, Quaternion quaternion2, out Quaternion& result)
	{
		result.X = quaternion1.X + quaternion2.X;
		result.Y = quaternion1.Y + quaternion2.Y;
		result.Z = quaternion1.Z + quaternion2.Z;
		result.W = quaternion1.W + quaternion2.W;
	}
	
	Quaternion Quaternion::Concatenate(Quaternion quaternion1, Quaternion quaternion2)
	{
		Quaternion quaternion; 
        float rx = quaternion2.X; 
        float ry = quaternion2.Y; 
        float rz = quaternion2.Z; 
        float rw = quaternion2.W; 
        float lx = quaternion1.X; 
        float ly = quaternion1.Y; 
        float lz = quaternion1.Z; 
        float lw = quaternion1.W; 
        float yz = (ry * lz) - (rz * ly); 
        float xz = (rz * lx) - (rx * lz); 
        float xy = (rx * ly) - (ry * lx); 
        float lengthSq = ((rx * lx) + (ry * ly)) + (rz * lz); 
  
        quaternion.X = ((rx * lw) + (lx * rw)) + yz; 
        quaternion.Y = ((ry * lw) + (ly * rw)) + xz; 
        quaternion.Z = ((rz * lw) + (lz * rw)) + xy; 
        quaternion.W = (rw * lw) - lengthSq; 
  
        return quaternion; 
    }
	
	void Quaternion::Concatenate(Quaternion quaternion1, Quaternion quaternion2, out Quaternion& result)
	{
		float rx = quaternion2.X; 
        float ry = quaternion2.Y; 
        float rz = quaternion2.Z; 
        float rw = quaternion2.W; 
        float lx = quaternion1.X; 
        float ly = quaternion1.Y; 
        float lz = quaternion1.Z; 
        float lw = quaternion1.W; 
        float yz = (ry * lz) - (rz * ly); 
        float xz = (rz * lx) - (rx * lz); 
        float xy = (rx * ly) - (ry * lx); 
        float lengthSq = ((rx * lx) + (ry * ly)) + (rz * lz);
        
        result.X = ((rx * lw) + (lx * rw)) + yz;
        result.Y = ((ry * lw) + (ly * rw)) + xz;
        result.Z = ((rz * lw) + (lz * rw)) + xy;
        result.W = (rw * lw) - lengthSq;
	}
	
	void Quaternion::Conjugate()
	{
		X = -X;
		Y = -Y;
		Z = -Z;
	}
	
	Quaternion Quaternion::Conjugate(Quaternion value)
	{
		Quaternion result; 
        result.X = -value.X; 
        result.Y = -value.Y; 
        result.Z = -value.Z; 
        result.W = value.W; 
        return result; 
	}
	
	void Quaternion::Conjugate(Quaternion value, out Quaternion& result)
	{
		result.X = -value.X; 
        result.Y = -value.Y; 
        result.Z = -value.Z; 
        result.W = value.W;
	}
	
	Quaternion Quaternion::CreateFromAxisAngle(Vector3 axis, float angle)
	{
		Quaternion result;
		
		Vector3::Normalize(axis, axis);
		
		float half = angle * 0.5f; 
        float Sin = Math::Sin(half); 
        float Cos = Math::Cos(half); 
  
        result.X = axis.X * Sin; 
        result.Y = axis.Y * Sin; 
        result.Z = axis.Z * Sin; 
        result.W = Cos;
  
        return result; 
	}
	
	void Quaternion::CreateFromAxisAngle(Vector3 axis, float angle, out Quaternion& result)
	{
		Vector3::Normalize(axis, axis);
		
		float half = angle * 0.5f; 
        float Sin = Math::Sin(half); 
        float Cos = Math::Cos(half); 
  
        result.X = axis.X * Sin; 
        result.Y = axis.Y * Sin; 
        result.Z = axis.Z * Sin; 
        result.W = Cos;
	}
	
	Quaternion Quaternion::CreateFromRotationMatrix(Matrix matrix)
	{
		Quaternion result;
		float scale = matrix.M11 + matrix.M22 + matrix.M33;
		
		if(scale > 0.0f)
		{
			float Sqrt = Math::Sqrt(scale + 1.0f);
			
			result.W = Sqrt + 0.5f;
			Sqrt = 0.5f / Sqrt;
			
			result.X = (matrix.M23 - matrix.M32) * Sqrt;
			result.Y = (matrix.M31 - matrix.M13) * Sqrt;
			result.Z = (matrix.M12 - matrix.M21) * Sqrt;
			
			return result;
		}
		
		if((matrix.M11 >= matrix.M22) && (matrix.M11 >= matrix.M33))
		{
			float Sqrt = Math::Sqrt(1.0f + matrix.M11 - matrix.M22 - matrix.M33);
			float half = 0.f / Sqrt;
			
			result.X = 0.5f * Sqrt;
			result.Y = (matrix.M12 + matrix.M21) * half;
			result.Z = (matrix.M13 + matrix.M31) * half;
			result.W = (matrix.M23 - matrix.M32) * half;
			
			return result;
		}
		
		if(matrix.M22 > matrix.M33)
		{
			float Sqrt = Math::Sqrt(1.0f + matrix.M22 - matrix.M11 - matrix.M33);
			float half = 0.5f / Sqrt;
			
			result.X = (matrix.M21 + matrix.M12) * half;
			result.Y = 0.5f * Sqrt;
			result.Z = (matrix.M32 + matrix.M23) * half;
			result.W = (matrix.M31 - matrix.M21) * half;
			
			return result;
		}
		
		float Sqrt = Math::Sqrt(1.0f + matrix.M33 - matrix.M11 - matrix.M22);
		float half = 0.5f / Sqrt;
		
		result.X = (matrix.M31 + matrix.M13) * half;
		result.Y = (matrix.M32 + matrix.M23) * half;
		result.Z = 0.5f * Sqrt;
		result.W = (matrix.M12 - matrix.M21) * half;
		
		return result;
	}
	
	void Quaternion::CreateFromRotationMatrix(Matrix matrix, out Quaternion& result)
	{
		float scale = matrix.M11 + matrix.M22 + matrix.M33;
		
		if(scale >0.0f)
		{
			float Sqrt = Math::Sqrt(scale + 1.0f);
			
			result.W = Sqrt + 0.5f;
			Sqrt = 0.5f / Sqrt;
			
			result.X = (matrix.M23 - matrix.M32) * Sqrt;
			result.Y = (matrix.M31 - matrix.M13) * Sqrt;
			result.Z = (matrix.M12 - matrix.M21) * Sqrt;
			return;
		}
		
		if((matrix.M11 >= matrix.M22) && (matrix.M11 >= matrix.M33))
		{
			float Sqrt = Math::Sqrt(1.0f + matrix.M11 - matrix.M22 - matrix.M33);
			float half = 0.f / Sqrt;
			
			result.X = 0.5f * Sqrt;
			result.Y = (matrix.M12 + matrix.M21) * half;
			result.Z = (matrix.M13 + matrix.M31) * half;
			result.W = (matrix.M23 - matrix.M32) * half;
			return;
		}
		
		if(matrix.M22 > matrix.M33)
		{
			float Sqrt = Math::Sqrt(1.0f + matrix.M22 - matrix.M11 - matrix.M33);
			float half = 0.5f / Sqrt;
			
			result.X = (matrix.M21 + matrix.M12) * half;
			result.Y = 0.5f * Sqrt;
			result.Z = (matrix.M32 + matrix.M23) * half;
			result.W = (matrix.M31 - matrix.M21) * half;
			return;
		}
		
		float Sqrt = Math::Sqrt(1.0f + matrix.M33 - matrix.M11 - matrix.M22);
		float half = 0.5f / Sqrt;
		
		result.X = (matrix.M31 + matrix.M13) * half;
		result.Y = (matrix.M32 + matrix.M23) * half;
		result.Z = 0.5f * Sqrt;
		result.W = (matrix.M12 - matrix.M21) * half;
	}
	
	Quaternion Quaternion::CreateFromYawPitchRoll(float yaw, float pitch, float roll)
	{
		Quaternion result;
		
		float halfRoll = roll * 0.5f;
		float sinRoll = Math::Sin(halfRoll);
		float cosRoll = Math::Cos(halfRoll);
		float halfPitch = pitch * 0.5f;
		float sinPitch = Math::Sin(halfPitch);
		float cosPitch = Math::Cos(halfPitch);
		float halfYaw = yaw * 0.5f;
		float sinYaw = Math::Sin(halfYaw);
		float cosYaw = Math::Cos(halfYaw);
		
		result.X = (cosYaw * sinPitch * cosRoll) + (sinYaw * cosPitch * sinRoll);
		result.Y = (sinYaw * cosPitch * cosRoll) + (cosYaw * sinPitch * sinRoll);
		result.Z = (cosYaw * cosPitch * sinRoll) + (sinYaw * sinPitch * cosRoll);
		result.W = (cosYaw * cosPitch * cosRoll) + (sinYaw * sinPitch * sinRoll);
		
		return result;
	}
	
	void Quaternion::CreateFromYawPitchRoll(float yaw, float pitch, float roll, out Quaternion& result)
	{
		float halfRoll = roll * 0.5f;
		float sinRoll = Math::Sin(halfRoll);
		float cosRoll = Math::Cos(halfRoll);
		float halfPitch = pitch * 0.5f;
		float sinPitch = Math::Sin(halfPitch);
		float cosPitch = Math::Cos(halfPitch);
		float halfYaw = yaw * 0.5f;
		float sinYaw = Math::Sin(halfYaw);
		float cosYaw = Math::Cos(halfYaw);
		
		result.X = (cosYaw * sinPitch * cosRoll) + (sinYaw * cosPitch * sinRoll);
		result.Y = (sinYaw * cosPitch * cosRoll) + (cosYaw * sinPitch * sinRoll);
		result.Z = (cosYaw * cosPitch * sinRoll) + (sinYaw * sinPitch * cosRoll);
		result.W = (cosYaw * cosPitch * cosRoll) + (sinYaw * sinPitch * sinRoll);
	}
	
	Quaternion Quaternion::Divide(Quaternion quaternion1, Quaternion quaternion2)
	{
		Quaternion result;
		result.X = quaternion1.X / quaternion2.X;
		result.Y = quaternion1.Y / quaternion2.Y;
		result.Z = quaternion1.Z / quaternion2.Z;
		result.W = quaternion1.W / quaternion2.W;
		return result;
	}
	
	void Quaternion::Divide(Quaternion quaternion1, Quaternion quaternion2, out Quaternion& result)
	{
		result.X = quaternion1.X / quaternion2.X;
		result.Y = quaternion1.Y / quaternion2.Y;
		result.Z = quaternion1.Z / quaternion2.Z;
		result.W = quaternion1.W / quaternion2.W;
	}
	
	float Quaternion::Dot(Quaternion quaternion1, Quaternion quaternion2)
	{
		return (quaternion1.X * quaternion2.X) + (quaternion1.Y * quaternion2.Y) + (quaternion1.Z * quaternion2.Z) + (quaternion1.W * quaternion2.W);
	}
	
	void Quaternion::Dot(Quaternion quaternion1, Quaternion quaternion2, out float& result)
	{
		result = (quaternion1.X * quaternion2.X) + (quaternion1.Y * quaternion2.Y) + (quaternion1.Z * quaternion2.Z) + (quaternion1.W * quaternion2.W);
	}

	bool Quaternion::Equals(Object const * const obj) const
	{
		return is(this, obj) ? *this == *(Quaternion *)obj : false;
	}
	
	bool Quaternion::Equals(const Quaternion obj) const
	{
		return (*this == obj);
	}

	int Quaternion::GetHashCode() const
	{
		return ((((int)X + (int)Y) + (int)Z) + (int)W);
	}

	int Quaternion::GetType() const
	{
		// TODO: implement
	}
	
	Quaternion Quaternion::Inverse(Quaternion quaternion)
	{
		Quaternion result;
		float lengthSq = 1.0f / ( (quaternion.X * quaternion.X) + (quaternion.Y * quaternion.Y) + (quaternion.Z * quaternion.Z) + (quaternion.W * quaternion.W) ); 
        result.X = -quaternion.X * lengthSq; 
        result.Y = -quaternion.Y * lengthSq; 
        result.Z = -quaternion.Z * lengthSq; 
        result.W = quaternion.W * lengthSq; 
        return result;
 	}
 	
 	void Quaternion::Inverse(Quaternion quaternion, out Quaternion& result)
	{
		float lengthSq = 1.0f / ( (quaternion.X * quaternion.X) + (quaternion.Y * quaternion.Y) + (quaternion.Z * quaternion.Z) + (quaternion.W * quaternion.W) ); 
        result.X = -quaternion.X * lengthSq; 
        result.Y = -quaternion.Y * lengthSq; 
        result.Z = -quaternion.Z * lengthSq; 
        result.W = quaternion.W * lengthSq;
	}
 	
 	float Quaternion::Length()
 	{
	 	return Math::Sqrt((X * X) + (Y * Y) + (Z * Z) + (W * W));
 	}
 	
 	float Quaternion::LengthSquared()
 	{
	 	return (X * X) + (Y * Y) + (Z * Z) + (W * W);
 	}
 	
 	Quaternion Quaternion::Lerp(Quaternion quaternion1, Quaternion quaternion2, float amount)
 	{
	 	Quaternion result;
	 	result.X = MathHelper::Lerp(quaternion1.X, quaternion2.X, amount);
	 	result.Y = MathHelper::Lerp(quaternion1.Y, quaternion2.Y, amount);
	 	result.Z = MathHelper::Lerp(quaternion1.Z, quaternion2.Z, amount);
	 	result.W = MathHelper::Lerp(quaternion1.W, quaternion2.W, amount);
	 	return result;
 	}
 	
 	void Quaternion::Lerp(Quaternion quaternion1, Quaternion quaternion2, float amount, out Quaternion& result)
	{
		result.X = MathHelper::Lerp(quaternion1.X, quaternion2.X, amount);
	 	result.Y = MathHelper::Lerp(quaternion1.Y, quaternion2.Y, amount);
	 	result.Z = MathHelper::Lerp(quaternion1.Z, quaternion2.Z, amount);
	 	result.W = MathHelper::Lerp(quaternion1.W, quaternion2.W, amount);
	}
 	
	Quaternion Quaternion::Multiply(Quaternion quaternion1, Quaternion quaternion2)
	{
		Quaternion result; 
       	float rx = quaternion2.X; 
        float ry = quaternion2.Y; 
        float rz = quaternion2.Z; 
        float rw = quaternion2.W; 
        float lx = quaternion1.X; 
        float ly = quaternion1.Y; 
        float lz = quaternion1.Z; 
        float lw = quaternion1.W; 
        float yz = (ry * lz) - (rz * ly); 
        float xz = (rz * lx) - (rx * lz); 
        float xy = (rx * ly) - (ry * lx); 
        float lengthSq = ((rx * lx) + (ry * ly)) + (rz * lz); 
  
        result.X = ((rx * lw) + (lx * rw)) + yz; 
        result.Y = ((ry * lw) + (ly * rw)) + xz; 
        result.Z = ((rz * lw) + (lz * rw)) + xy; 
        result.W = (rw * lw) - lengthSq; 
  
        return result; 
	}
	
	void Quaternion::Multiply(Quaternion quaternion1, Quaternion quaternion2, out Quaternion& result)
	{
       	float rx = quaternion2.X; 
        float ry = quaternion2.Y; 
        float rz = quaternion2.Z; 
        float rw = quaternion2.W; 
        float lx = quaternion1.X; 
        float ly = quaternion1.Y; 
        float lz = quaternion1.Z; 
        float lw = quaternion1.W; 
        float yz = (ry * lz) - (rz * ly); 
        float xz = (rz * lx) - (rx * lz); 
        float xy = (rx * ly) - (ry * lx); 
        float lengthSq = ((rx * lx) + (ry * ly)) + (rz * lz); 
  
        result.X = ((rx * lw) + (lx * rw)) + yz; 
        result.Y = ((ry * lw) + (ly * rw)) + xz; 
        result.Z = ((rz * lw) + (lz * rw)) + xy; 
        result.W = (rw * lw) - lengthSq; 
	}
	
	Quaternion Quaternion::Multiply(Quaternion quaternion, float scaleFactor)
	{
		Quaternion result;
		result.X = quaternion.X * scaleFactor;
		result.Y = quaternion.Y * scaleFactor;
		result.Z = quaternion.Z * scaleFactor;
		result.W = quaternion.W * scaleFactor;
		return result;
	}
	
	void Quaternion::Multiply(Quaternion quaternion, float scaleFactor, out Quaternion& result)
	{
		result.X = quaternion.X * scaleFactor;
		result.Y = quaternion.Y * scaleFactor;
		result.Z = quaternion.Z * scaleFactor;
		result.W = quaternion.W * scaleFactor;
	}
	
	Quaternion Quaternion::Negate(Quaternion quaternion)
	{
		Quaternion result;
		result.X = -quaternion.X;
		result.Y = -quaternion.Y;
		result.Z = -quaternion.Z;
		result.W = -quaternion.W;
		return result;
	}
	
	void Quaternion::Negate(Quaternion quaternion, out Quaternion& result)
	{
		result.X = -quaternion.X;
		result.Y = -quaternion.Y;
		result.Z = -quaternion.Z;
		result.W = -quaternion.W;
	}
	
 	void Quaternion::Normalize() 
    { 
        float length = 1.0f / Length(); 
        X *= length; 
        Y *= length; 
        Z *= length; 
        W *= length; 
    }
    
    Quaternion Quaternion::Slerp(Quaternion quaternion1, Quaternion quaternion2, float amount)
    {
	    Quaternion result; 
  
        float opposite; 
        float inverse; 
        float dot = (quaternion1.X * quaternion2.X) + (quaternion1.Y * quaternion2.Y) + (quaternion1.Z * quaternion2.Z) + (quaternion1.W * quaternion2.W); 
        int flag = false; 
  
        if( dot < 0.0f ) 
        { 
            flag = true; 
            dot = -dot; 
        } 
  
        if( dot > 0.999999f ) 
        { 
        	inverse = 1.0f - amount; 
        	opposite = flag ? -amount : amount; 
        } 
        else 
        { 
        	float Acos = Math::Acos(dot); 
        	float invSin = (1.0f / Math::Sin(Acos)); 
  
        	inverse = (Math::Sin((1.0f - amount) * Acos)* invSin); 
        	opposite = flag ? ( -Math::Sin(amount * Acos ) * invSin) : (Math::Sin(amount * Acos) * invSin); 
        } 
  
        result.X = (inverse * quaternion1.X) + (opposite * quaternion2.X); 
        result.Y = (inverse * quaternion1.Y) + (opposite * quaternion2.Y); 
        result.Z = (inverse * quaternion1.Z) + (opposite * quaternion2.Z); 
        result.W = (inverse * quaternion1.W) + (opposite * quaternion2.W); 
  
        return result; 
    } 
    
    void Quaternion::Slerp(Quaternion quaternion1, Quaternion quaternion2, float amount, out Quaternion& result)
    {
	    float opposite; 
        float inverse; 
        float dot = (quaternion1.X * quaternion2.X) + (quaternion1.Y * quaternion2.Y) + (quaternion1.Z * quaternion2.Z) + (quaternion1.W * quaternion2.W); 
        int flag = false; 
  
        if( dot < 0.0f ) 
        { 
            flag = true; 
            dot = -dot; 
        } 
  
        if( dot > 0.999999f ) 
        { 
        	inverse = 1.0f - amount; 
        	opposite = flag ? -amount : amount; 
        } 
        else 
        { 
        	float Acos = Math::Acos(dot); 
        	float invSin = (1.0f / Math::Sin(Acos)); 
  
        	inverse = (Math::Sin((1.0f - amount) * Acos)* invSin); 
        	opposite = flag ? ( -Math::Sin(amount * Acos ) * invSin) : (Math::Sin(amount * Acos) * invSin); 
        } 
  
        result.X = (inverse * quaternion1.X) + (opposite * quaternion2.X); 
        result.Y = (inverse * quaternion1.Y) + (opposite * quaternion2.Y); 
        result.Z = (inverse * quaternion1.Z) + (opposite * quaternion2.Z); 
        result.W = (inverse * quaternion1.W) + (opposite * quaternion2.W); 
    }

	Quaternion Quaternion::Subtract(Quaternion quaternion1, Quaternion quaternion2)
	{
		return Quaternion(quaternion1.X - quaternion2.X, quaternion1.Y - quaternion2.Y, quaternion1.Z - quaternion2.Z, quaternion1.W - quaternion2.W);
	}

	void Quaternion::Subtract(Quaternion quaternion1, Quaternion quaternion2, out Quaternion& result)
	{
		result.X = quaternion1.X - quaternion2.X;
		result.Y = quaternion1.Y - quaternion2.Y;
		result.Z = quaternion1.Z - quaternion2.Z;
		result.W = quaternion1.W - quaternion2.W;
	}
	
	Quaternion Quaternion::operator +(const Quaternion& other)
	{
		return Quaternion(X + other.X, Y + other.Y, Z + other.Z, W + other.W);
	}
	
	Quaternion Quaternion::operator /(const Quaternion& other)
	{
		return Quaternion(X / other.X, Y / other.Y, Z / other.Z, W / other.W);
	}
	
	bool Quaternion::operator==(const Quaternion& other) const
	{
		return ((X == other.X) && (Y == other.Y) && (Z == other.Z) && (W == other.W));
	}

	bool Quaternion::operator!=(const Quaternion& other) const
	{
		return ((X != other.X) || (Y != other.Y) || (Z != other.Z) || (W != other.W));
	}
	
	Quaternion Quaternion::operator*(const Quaternion& other)
	{
		Quaternion result; 
       	float rx = other.X; 
        float ry = other.Y; 
        float rz = other.Z; 
        float rw = other.W; 
        float lx = X; 
        float ly = Y; 
        float lz = Z; 
        float lw = W; 
        float yz = (ry * lz) - (rz * ly); 
        float xz = (rz * lx) - (rx * lz); 
        float xy = (rx * ly) - (ry * lx); 
        float lengthSq = ((rx * lx) + (ry * ly)) + (rz * lz); 
  
        result.X = ((rx * lw) + (lx * rw)) + yz; 
        result.Y = ((ry * lw) + (ly * rw)) + xz; 
        result.Z = ((rz * lw) + (lz * rw)) + xy; 
        result.W = (rw * lw) - lengthSq; 
  
        return result; 
	}
	
	Quaternion Quaternion::operator*(const float scaleFactor)
	{
		return Quaternion(X * scaleFactor, Y * scaleFactor, Z * scaleFactor, W * scaleFactor);
	}
	
	Quaternion Quaternion::operator-(const Quaternion& other)
	{
		return Quaternion(X - other.X, Y - other.Y, Z - other.Z, W - other.W);
	}
	
	Quaternion Quaternion::operator-()
	{
		return Quaternion(-X, -Y, -Z, -W);
	}
}
