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

#include <BoundingBox.h>
#include <BoundingSphere.h>
#include <Plane.h>
#include <Matrix.h>
#include <Quaternion.h>
#include <Vector3.h>
#include <Vector4.h>
#include <System/Math.h>
#include <System/String.h>

using namespace System;

namespace XFX
{
	Plane::Plane(const float a, const float b, const float c, const float d)
		: D(d), Normal(a, b, c)
	{
	}
	
	Plane::Plane(const Vector3 normal, const float d)
		: D(d), Normal(normal)
	{
	}
	
	Plane::Plane(const Vector3 point1, const Vector3 point2, const Vector3 point3)
	{
		float x1 = point2.X - point1.X; 
        float y1 = point2.Y - point1.Y; 
        float z1 = point2.Z - point1.Z; 
        float x2 = point3.X - point1.X; 
        float y2 = point3.Y - point1.Y; 
        float z2 = point3.Z - point1.Z; 
        float yz = (y1 * z2) - (z1 * y2); 
        float xz = (z1 * x2) - (x1 * z2); 
        float xy = (x1 * y2) - (y1 * x2); 
        float invPyth = 1.0f / Math::Sqrt((yz * yz) + (xz * xz) + (xy * xy)); 
  
        Normal.X = yz * invPyth; 
        Normal.Y = xz * invPyth; 
        Normal.Z = xy * invPyth; 
        D = -((Normal.X * point1.X) + (Normal.Y * point1.Y) + (Normal.Z * point1.Z)); 
	}
	
	Plane::Plane(const Vector4 value)
		: D(value.W), Normal(value.X, value.Y, value.Z)
	{
	}
	
	Plane::Plane(const Plane &obj)
		: D(obj.D), Normal(obj.Normal)
	{
	}
	
	Plane::Plane()
		: D(0), Normal(Vector3::Zero)
	{
	}
	
	float Plane::Dot(const Vector4 value) const
	{
		return (Normal.X * value.X) + (Normal.Y * value.Y) + (Normal.Z * value.Z) + (D * value.W);
	}
	
	void Plane::Dot(const Vector4 value, out float result) const
	{
		result = (Normal.X * value.X) + (Normal.Y * value.Y) + (Normal.Z * value.Z) + (D * value.W);
	}
	
	float Plane::DotCoordinate(const Vector3 value) const
	{
		return (Normal.X * value.X) + (Normal.Y * value.Y) + (Normal.Z * value.Z) + D;
	}
	
	void Plane::DotCoordinate(const Vector3 value, out float result) const
	{
		result = (Normal.X * value.X) + (Normal.Y * value.Y) + (Normal.Z * value.Z) + D;
	}
	
	float Plane::DotNormal(const Vector3 value) const
	{
		return (Normal.X * value.X) + (Normal.Y * value.Y) + (Normal.Z * value.Z); 
	}
	
	void Plane::DotNormal(const Vector3 value, out float result) const
	{
		result = (Normal.X * value.X) + (Normal.Y * value.Y) + (Normal.Z * value.Z); 
	}

	bool Plane::Equals(const Object* obj) const
	{
		return is(this, obj) ? this->Equals((*(Plane*)obj)) : false;
	}
	
	bool Plane::Equals(const Plane obj) const
	{
		return (*this == obj);
	}
	
	int Plane::GetHashCode() const
	{
		return Normal.GetHashCode() ^ (int)D;
	}

	int Plane::GetType() const
	{
		// TODO: implement
	}
	
	PlaneIntersectionType_t Plane::Intersects(const BoundingBox boundingbox) const
	{
		Vector3 min; 
        Vector3 max; 
        max.X = (Normal.X >= 0.0f) ? boundingbox.Min.X : boundingbox.Max.X; 
        max.Y = (Normal.Y >= 0.0f) ? boundingbox.Min.Y : boundingbox.Max.Y; 
        max.Z = (Normal.Z >= 0.0f) ? boundingbox.Min.Z : boundingbox.Max.Z; 
        min.X = (Normal.X >= 0.0f) ? boundingbox.Max.X : boundingbox.Min.X; 
        min.Y = (Normal.Y >= 0.0f) ? boundingbox.Max.Y : boundingbox.Min.Y; 
        min.Z = (Normal.Z >= 0.0f) ? boundingbox.Max.Z : boundingbox.Min.Z; 
  
        float dot = (Normal.X * max.X) + (Normal.Y * max.Y) + (Normal.Z * max.Z); 
  
        if(dot + D > 0.0f) 
   			return PlaneIntersectionType::Front; 
  
        dot = (Normal.X * min.X) + (Normal.Y * min.Y) + (Normal.Z * min.Z); 
  
        if(dot + D < 0.0f) 
   			return PlaneIntersectionType::Back; 
  
        return PlaneIntersectionType::Intersecting; 
	}
	
	void Plane::Intersects(const BoundingBox boundingbox, out PlaneIntersectionType_t result) const
	{
		Vector3 min; 
        Vector3 max; 
        max.X = (Normal.X >= 0.0f) ? boundingbox.Min.X : boundingbox.Max.X; 
        max.Y = (Normal.Y >= 0.0f) ? boundingbox.Min.Y : boundingbox.Max.Y; 
        max.Z = (Normal.Z >= 0.0f) ? boundingbox.Min.Z : boundingbox.Max.Z; 
        min.X = (Normal.X >= 0.0f) ? boundingbox.Max.X : boundingbox.Min.X; 
        min.Y = (Normal.Y >= 0.0f) ? boundingbox.Max.Y : boundingbox.Min.Y; 
        min.Z = (Normal.Z >= 0.0f) ? boundingbox.Max.Z : boundingbox.Min.Z; 
  
        float dot = (Normal.X * max.X) + (Normal.Y * max.Y) + (Normal.Z * max.Z); 
  
        if(dot + D > 0.0f) 
   			result = PlaneIntersectionType::Front; 
  
        dot = (Normal.X * min.X) + (Normal.Y * min.Y) + (Normal.Z * min.Z); 
  
        if(dot + D < 0.0f) 
   			result = PlaneIntersectionType::Back; 
  
        result = PlaneIntersectionType::Intersecting;
	}
	
	PlaneIntersectionType_t Plane::Intersects(const BoundingSphere sphere) const
	{
		float dot = (sphere.Center.X * Normal.X) + (sphere.Center.Y * Normal.Y) + (sphere.Center.Z * Normal.Z) + D; 

        if(dot > sphere.Radius) 
   			return PlaneIntersectionType::Front; 
  
        if(dot < -sphere.Radius) 
   			return PlaneIntersectionType::Back; 
  
        return PlaneIntersectionType::Intersecting; 
	}
	
	void Plane::Intersects(const BoundingSphere sphere, out PlaneIntersectionType_t result) const
	{
		float dot = (sphere.Center.X * Normal.X) + (sphere.Center.Y * Normal.Y) + (sphere.Center.Z * Normal.Z) + D; 

        if(dot > sphere.Radius) 
   			result = PlaneIntersectionType::Front; 
  
        if(dot < -sphere.Radius) 
   			result = PlaneIntersectionType::Back; 
  
        result = PlaneIntersectionType::Intersecting; 
	}
	
	void Plane::Normalize()
    { 
        float magnitude = 1.0f / Math::Sqrt((Normal.X * Normal.X) + (Normal.Y * Normal.Y) + (Normal.Z * Normal.Z)); 
		
        Normal.X *= magnitude; 
        Normal.Y *= magnitude; 
        Normal.Z *= magnitude; 
        D *= magnitude; 
    }
    
    Plane Plane::Normalize(const Plane plane)
    {
	    float magnitude = 1.0f / Math::Sqrt((plane.Normal.X * plane.Normal.X) + (plane.Normal.Y * plane.Normal.Y) + (plane.Normal.Z * plane.Normal.Z)); 
  
        return Plane(plane.Normal.X * magnitude, plane.Normal.Y * magnitude, plane.Normal.Z * magnitude, plane.D * magnitude); 
    }
     
    void Plane::Normalize(const Plane plane, out Plane result)
    {
	    result = Normalize(plane);
    }

	const char* Plane::ToString() const
	{
		return String::Format("{Normal:%s D:%f}", Normal.ToString(), D);
	}
	
	Plane Plane::Transform(Plane plane, Matrix matrix)
	{
		Plane result; 
        float x = plane.Normal.X; 
        float y = plane.Normal.Y; 
        float z = plane.Normal.Z; 
        float d = plane.D; 
  
        matrix = Matrix::Invert(matrix);
        result.Normal.X = (((x * matrix.M11) + (y * matrix.M12)) + (z * matrix.M13)) + (d * matrix.M14); 
        result.Normal.Y = (((x * matrix.M21) + (y * matrix.M22)) + (z * matrix.M23)) + (d * matrix.M24); 
        result.Normal.Z = (((x * matrix.M31) + (y * matrix.M32)) + (z * matrix.M33)) + (d * matrix.M34); 
        result.D = (((x * matrix.M41) + (y * matrix.M42)) + (z * matrix.M43)) + (d * matrix.M44); 
  
        return result; 
	}
	
	void Plane::Transform(Plane plane, Matrix matrix, out Plane result)
	{
		float x = plane.Normal.X; 
        float y = plane.Normal.Y; 
        float z = plane.Normal.Z; 
        float d = plane.D; 
  
        matrix = Matrix::Invert(matrix); 
        result.Normal.X = (((x * matrix.M11) + (y * matrix.M12)) + (z * matrix.M13)) + (d * matrix.M14); 
        result.Normal.Y = (((x * matrix.M21) + (y * matrix.M22)) + (z * matrix.M23)) + (d * matrix.M24); 
        result.Normal.Z = (((x * matrix.M31) + (y * matrix.M32)) + (z * matrix.M33)) + (d * matrix.M34); 
        result.D = (((x * matrix.M41) + (y * matrix.M42)) + (z * matrix.M43)) + (d * matrix.M44); 
	}
	
	Plane Plane::Transform(Plane plane, Quaternion quaternion)
	{
		Plane result; 
        float x2 = quaternion.X + quaternion.X; 
        float y2 = quaternion.Y + quaternion.Y; 
        float z2 = quaternion.Z + quaternion.Z; 
        float wx = quaternion.W * x2; 
        float wy = quaternion.W * y2; 
        float wz = quaternion.W * z2; 
        float xx = quaternion.X * x2; 
        float xy = quaternion.X * y2; 
        float xz = quaternion.X * z2; 
        float yy = quaternion.Y * y2; 
        float yz = quaternion.Y * z2; 
        float zz = quaternion.Z * z2; 
  
        float x = plane.Normal.X; 
        float y = plane.Normal.Y; 
        float z = plane.Normal.Z; 
  
        result.Normal.X = ((x * ((1.0f - yy) - zz)) + (y * (xy - wz))) + (z * (xz + wy)); 
        result.Normal.Y = ((x * (xy + wz)) + (y * ((1.0f - xx) - zz))) + (z * (yz - wx)); 
        result.Normal.Z = ((x * (xz - wy)) + (y * (yz + wx))) + (z * ((1.0f - xx) - yy)); 
        result.D = plane.D; 
        return result;
	}
	
	void Plane::Transform(Plane plane, Quaternion quaternion, out Plane result)
	{
		float x2 = quaternion.X + quaternion.X; 
        float y2 = quaternion.Y + quaternion.Y; 
        float z2 = quaternion.Z + quaternion.Z; 
        float wx = quaternion.W * x2; 
        float wy = quaternion.W * y2; 
        float wz = quaternion.W * z2; 
        float xx = quaternion.X * x2; 
        float xy = quaternion.X * y2; 
        float xz = quaternion.X * z2; 
        float yy = quaternion.Y * y2; 
        float yz = quaternion.Y * z2; 
        float zz = quaternion.Z * z2; 
  
        float x = plane.Normal.X; 
        float y = plane.Normal.Y; 
        float z = plane.Normal.Z; 
  
        result.Normal.X = ((x * ((1.0f - yy) - zz)) + (y * (xy - wz))) + (z * (xz + wy)); 
        result.Normal.Y = ((x * (xy + wz)) + (y * ((1.0f - xx) - zz))) + (z * (yz - wx)); 
        result.Normal.Z = ((x * (xz - wy)) + (y * (yz + wx))) + (z * ((1.0f - xx) - yy)); 
        result.D = plane.D; 
	}
	
	bool Plane::operator==(const Plane& other) const
	{
		return ((D == other.D) && (Normal == other.Normal));
	}
	
	bool Plane::operator!=(const Plane& other) const
	{
		return !((D == other.D) && (Normal == other.Normal));
	}
}
