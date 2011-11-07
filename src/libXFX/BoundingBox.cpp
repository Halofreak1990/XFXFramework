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
#include <Ray.h>
#include <System/Array.h>
#include <System/Math.h>
#include <System/Single.h>

using namespace System;

namespace XFX
{	
	const int BoundingBox::CornerCount = 8;
	
	BoundingBox::BoundingBox(Vector3 min, Vector3 max)
	{
		Min = min;
		Max = max;
	}
	
	BoundingBox::BoundingBox(const BoundingBox &obj)
	{
		Min = obj.Min;
		Max = obj.Max;
	}
	
	BoundingBox::BoundingBox()
	{
		Min = Vector3::Zero;
		Max = Vector3::Zero;
	}

	ContainmentType_t BoundingBox::Contains(BoundingBox box)
	{
		if( Max.X < box.Min.X || Min.X > box.Max.X ) 
        	return ContainmentType::Disjoint; 
  
        if( Max.Y < box.Min.Y || Min.Y > box.Max.Y ) 
            return ContainmentType::Disjoint; 
  
        if( Max.Z < box.Min.Z || Min.Z > box.Max.Z ) 
            return ContainmentType::Disjoint; 
  
        if( Min.X <= box.Min.X && box.Max.X <= Max.X && Min.Y <= box.Min.Y &&  
            box.Max.Y <= Max.Y && Min.Z <= box.Min.Z && box.Max.Z <= Max.Z ) 
                return ContainmentType::Contains; 
  
        return ContainmentType::Intersects; 
	}

	void BoundingBox::Contains(BoundingBox box, out ContainmentType_t result)
	{
		if( Max.X < box.Min.X || Min.X > box.Max.X ) 
        	result = ContainmentType::Disjoint; 
  
        if( Max.Y < box.Min.Y || Min.Y > box.Max.Y ) 
            result = ContainmentType::Disjoint; 
  
        if( Max.Z < box.Min.Z || Min.Z > box.Max.Z ) 
            result = ContainmentType::Disjoint; 
  
        if( Min.X <= box.Min.X && box.Max.X <= Max.X && Min.Y <= box.Min.Y &&  
            box.Max.Y <= Max.Y && Min.Z <= box.Min.Z && box.Max.Z <= Max.Z ) 
                result = ContainmentType::Contains; 
  
        result = ContainmentType::Intersects; 
	}
	
	ContainmentType_t BoundingBox::Contains(BoundingSphere sphere)
	{
		float dist; 
        Vector3 clamped; 
  
        Vector3::Clamp(sphere.Center, Min, Max, clamped); 
  
        float x = sphere.Center.X - clamped.X; 
        float y = sphere.Center.Y - clamped.Y; 
        float z = sphere.Center.Z - clamped.Z; 
  
        dist = (x * x) + (y * y) + (z * z); 
        float radius = sphere.Radius; 
  
        if(dist > (radius * radius)) 
            return ContainmentType::Disjoint; 
  
        if(Min.X + radius <= sphere.Center.X && sphere.Center.X <= Max.X - radius &&  
            Max.X - Min.X > radius && Min.Y + radius <= sphere.Center.Y &&  
            sphere.Center.Y <= Max.Y - radius && Max.Y - Min.Y > radius &&  
            Min.Z + radius <= sphere.Center.Z && sphere.Center.Z <= Max.Z - radius && 
            Max.X - Min.X > radius) 
                return ContainmentType::Contains; 
  
        return ContainmentType::Intersects; 
	}
	
	void BoundingBox::Contains(BoundingSphere sphere, out ContainmentType_t result)
	{
		float dist; 
        Vector3 clamped; 
  
        Vector3::Clamp(sphere.Center, Min, Max, clamped); 
  
        float x = sphere.Center.X - clamped.X; 
        float y = sphere.Center.Y - clamped.Y; 
        float z = sphere.Center.Z - clamped.Z; 
  
        dist = (x * x) + (y * y) + (z * z); 
        float radius = sphere.Radius; 
  
        if(dist > (radius * radius)) 
            result = ContainmentType::Disjoint; 
  
        if(Min.X + radius <= sphere.Center.X && sphere.Center.X <= Max.X - radius &&  
            Max.X - Min.X > radius && Min.Y + radius <= sphere.Center.Y &&  
            sphere.Center.Y <= Max.Y - radius && Max.Y - Min.Y > radius &&  
            Min.Z + radius <= sphere.Center.Z && sphere.Center.Z <= Max.Z - radius && 
            Max.X - Min.X > radius) 
                result = ContainmentType::Contains; 
  
        result = ContainmentType::Intersects;
	}
	
	ContainmentType_t BoundingBox::Contains(Vector3 vector)
	{
		if(Min.X <= vector.X && vector.X <= Max.X && Min.Y <= vector.Y &&  
            vector.Y <= Max.Y && Min.Z <= vector.Z && vector.Z <= Max.Z) 
                return ContainmentType::Contains; 
  
        return ContainmentType::Disjoint; 
	}
	
	void BoundingBox::Contains(Vector3 vector, out ContainmentType_t result)
	{
		if(Min.X <= vector.X && vector.X <= Max.X && Min.Y <= vector.Y &&  
            vector.Y <= Max.Y && Min.Z <= vector.Z && vector.Z <= Max.Z) 
                result = ContainmentType::Contains; 
  
        result = ContainmentType::Disjoint;
	}
	
	BoundingBox BoundingBox::CreateFromPoints(Vector3 points[])
	{
		if((!points) || Array::Length(points) <= 0) 
            return BoundingBox();
  
		Vector3 min = Single::MinValue; 
		Vector3 max = Single::MaxValue; 
  
		for(int i = 0; i < Array::Length(points); i++)
        {
	        Vector3::Min(min, points[i], min); 
            Vector3::Max(max, points[i], max);
        }
  
        return BoundingBox(min, max); 
	}
	
	BoundingBox BoundingBox::CreateFromSphere(BoundingSphere sphere)
	{
		BoundingBox result; 
        result.Min = Vector3(sphere.Center.X - sphere.Radius, sphere.Center.Y - sphere.Radius, sphere.Center.Z - sphere.Radius ); 
        result.Max = Vector3(sphere.Center.X + sphere.Radius, sphere.Center.Y + sphere.Radius, sphere.Center.Z + sphere.Radius ); 
        return result; 
	}
	
	void BoundingBox::CreateFromSphere(BoundingSphere sphere, out BoundingBox result)
	{
		result.Min = Vector3(sphere.Center.X - sphere.Radius, sphere.Center.Y - sphere.Radius, sphere.Center.Z - sphere.Radius ); 
        result.Max = Vector3(sphere.Center.X + sphere.Radius, sphere.Center.Y + sphere.Radius, sphere.Center.Z + sphere.Radius ); 
	}
	
	BoundingBox BoundingBox::CreateMerged(BoundingBox box1, BoundingBox box2)
	{
		BoundingBox result; 
        Vector3::Min(box1.Min, box2.Min, result.Min); 
        Vector3::Max(box1.Max, box2.Max, result.Max); 
        return result; 
	}
	
	void BoundingBox::CreateMerged(BoundingBox box1, BoundingBox box2, out BoundingBox result)
	{
		Vector3::Min(box1.Min, box2.Min, result.Min); 
        Vector3::Max(box1.Max, box2.Max, result.Max); 
	}
	
	bool BoundingBox::Equals(BoundingBox obj)
	{
		return ((Max == obj.Max) && (Min == obj.Min));
	}
	
	int BoundingBox::Intersects(BoundingBox box)
	{
		if (Max.X < box.Min.X || Min.X > box.Max.X) 
            return false; 
  
        if (Max.Y < box.Min.Y || Min.Y > box.Max.Y) 
            return false; 
  
        return (Max.Z >= box.Min.Z && Min.Z <= box.Max.Z);  
	}
	
	void BoundingBox::Intersects(BoundingBox box, out int result)
	{
		if (Max.X < box.Min.X || Min.X > box.Max.X) 
            result = false; 
  
        if (Max.Y < box.Min.Y || Min.Y > box.Max.Y) 
            result = false; 
  
        result = (Max.Z >= box.Min.Z && Min.Z <= box.Max.Z); 
	}
	
	int BoundingBox::Intersects(BoundingSphere sphere)
	{
		float dist; 
        Vector3 clamped; 
  
        Vector3::Clamp(sphere.Center, Min, Max, clamped); 
  
        float x = sphere.Center.X - clamped.X; 
        float y = sphere.Center.Y - clamped.Y; 
        float z = sphere.Center.Z - clamped.Z; 
  
        dist = (x * x) + (y * y) + (z * z); 
  
        return (dist <= (sphere.Radius * sphere.Radius)); 
	}
	
	void BoundingBox::Intersects(BoundingSphere sphere, out int result)
	{
		float dist; 
        Vector3 clamped; 
  
        Vector3::Clamp(sphere.Center, Min, Max, clamped); 
  
        float x = sphere.Center.X - clamped.X; 
        float y = sphere.Center.Y - clamped.Y; 
        float z = sphere.Center.Z - clamped.Z; 
  
        dist = (x * x) + (y * y) + (z * z); 
  
        result = (dist <= (sphere.Radius * sphere.Radius));
	}
	
	PlaneIntersectionType_t BoundingBox::Intersects(Plane plane)
	{
		return plane.Intersects(*this);
	}
	
	void BoundingBox::Intersects(Plane plane, out PlaneIntersectionType_t result)
	{
		result = plane.Intersects(*this);
	}
	
	float BoundingBox::Intersects(Ray ray)
	{
		float distance = 0;
		ray.Intersects(*this, distance);
		return distance;
	}
	
	void BoundingBox::Intersects(Ray ray, out float distance)
	{
		ray.Intersects(*this, distance);
	}
	
	bool BoundingBox::operator!=(const BoundingBox other)
	{
		return !Equals(other);
	}
	
	bool BoundingBox::operator==(const BoundingBox other)
	{
		return Equals(other);
	}
	
	BoundingBox BoundingBox::operator=(const BoundingBox other)
	{
		Max = other.Max;
		Min = other.Min;
		return *this;
	}
}
