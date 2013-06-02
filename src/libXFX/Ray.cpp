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

#include <BoundingBox.h>
#include <BoundingSphere.h>
#include <Plane.h>
#include <Ray.h>
#include <System/Math.h>
#include <System/Single.h>
#include <System/String.h>
#include <Vector3.h>

using namespace System;

namespace XFX
{
	Ray::Ray(Vector3 direction, Vector3 position)
		: Direction(direction), Position(position)
	{
	}
	
	Ray::Ray(const Ray &obj)
		: Direction(obj.Direction), Position(obj.Position)
	{
	}
	
	Ray::Ray()
		: Direction(Vector3::Zero), Position(Vector3::Zero)
	{
	}

	bool Ray::Equals(Object const * const obj) const
	{
		return is(this, obj) ? *this == *(Ray *)obj : false;
	}

	bool Ray::Equals(const Ray other) const
	{
		return (*this == other);
	}
	
	int Ray::GetHashCode() const
	{
		return (Direction.GetHashCode() ^ Position.GetHashCode());
	}

	int Ray::GetType() const
	{
		// TODO: implement
	}

	float Ray::Intersects(BoundingBox boundingbox) const
	{
		float distance;
		float d = 0.0f; 
		float MAXValue = Single::MaxValue; 
  
		if (Math::Abs(Direction.X) < 0.0000001) 
        { 
       		if (Position.X < boundingbox.Min.X || Position.X > boundingbox.Max.X) 
       		{ 
      			distance = 0.0f;
      			return distance; 
       		} 
        } 
        else 
        { 
       		float inv = 1.0f / Direction.X; 
       		float MIN = (boundingbox.Min.X - Position.X) * inv; 
       		float MAX = (boundingbox.Max.X - Position.X) * inv; 
  
       		if (MIN > MAX) 
       		{ 
      			float temp = MIN; 
      			MIN = MAX; 
      			MAX = temp; 
       		} 
  
       		d = Math::Max(MIN, d); 
       		MAXValue = Math::Min(MAX, MAXValue); 
  
       		if (d > MAXValue) 
       		{ 
      			distance = 0.0f;
      			return distance;
       		} 
        } 
  
        if (Math::Abs(Direction.Y) < 0.0000001) 
        { 
       		if (Position.Y < boundingbox.Min.Y || Position.Y > boundingbox.Max.Y) 
       		{ 
      			distance = 0.0f;
      			return distance;
       		} 
        } 
        else 
        { 
       		float inv = 1.0f / Direction.Y; 
       		float MIN = (boundingbox.Min.Y - Position.Y) * inv; 
       		float MAX = (boundingbox.Max.Y - Position.Y) * inv; 
  
       		if (MIN > MAX) 
       		{ 
      			float temp = MIN; 
      			MIN = MAX; 
      			MAX = temp; 
       		} 
  
       		d = Math::Max(MIN, d); 
       		MAXValue = Math::Min(MAX, MAXValue); 
  
       		if (d > MAXValue)
       		{ 
      			distance = 0.0f;
      			return distance;
       		} 
       	} 
  
        if (Math::Abs(Direction.Z) < 0.0000001)
        { 
       		if (Position.Z < boundingbox.Min.Z || Position.Z > boundingbox.Max.Z) 
       		{ 
      			distance = 0.0f;
      			return distance;
       		} 
       	} 
        else 
        { 
       		float inv = 1.0f / Direction.Z; 
       		float MIN = (boundingbox.Min.Z - Position.Z) * inv; 
       		float MAX = (boundingbox.Max.Z - Position.Z) * inv; 
  
       		if (MIN > MAX)
       		{
      			float temp = MIN; 
      			MIN = MAX; 
      			MAX = temp; 
       		} 
  
       		d = Math::Max(MIN, d);
       		MAXValue = Math::Min(MAX, MAXValue);
  
       		if (d > MAXValue)
       		{
      			distance = 0.0f; 
      			return distance;
			} 
        }
  
        distance = d; 
        return distance;
	}
	
	void Ray::Intersects(BoundingBox boundingbox, out float& distance) const
	{
		distance = Intersects(boundingbox);
	}

	float Ray::Intersects(BoundingSphere sphere) const
	{
		float distance;
		float x = sphere.Center.X - Position.X; 
        float y = sphere.Center.Y - Position.Y; 
        float z = sphere.Center.Z - Position.Z; 
        float pyth = (x * x) + (y * y) + (z * z); 
        float rr = sphere.Radius * sphere.Radius; 
  
        if (pyth <= rr)
        { 
       		distance = 0.0f; 
       		return distance; 
        } 
  
        float dot = (x * Direction.X) + (y * Direction.Y) + (z * Direction.Z); 
        if (dot < 0.0f)
        { 
       		distance = 0.0f; 
       		return distance; 
        } 
  
        float temp = pyth - (dot * dot); 
        if (temp > rr)
        { 
       		distance = 0.0f; 
       		return distance; 
        } 
  
        distance = dot - Math::Sqrt(rr - temp); 
        return distance; 
	}
	
	void Ray::Intersects(BoundingSphere sphere, out float& distance) const
	{
		distance = Intersects(sphere);
	}

	float Ray::Intersects(Plane plane) const
	{
		float dotDirection = (plane.Normal.X * Direction.X) + (plane.Normal.Y * Direction.Y) + (plane.Normal.Z * Direction.Z); 
		float distance;
  
        if (Math::Abs(dotDirection) < 0.000001f)
        { 
       		distance = 0.0f; 
       		return distance; 
        } 
  
        float dotPosition = (plane.Normal.X * Position.X) + (plane.Normal.Y * Position.Y) + (plane.Normal.Z * Position.Z); 
        float num = (-plane.D - dotPosition) / dotDirection; 
  
        if (num < 0.0f)
        {
       		if (num < -0.000001f)
       		{
      			distance = 0.0f; 
      			return distance; 
       		}
       		num = 0.0f; 
        }
  
        distance = num; 
        return distance;
	}
	
	void Ray::Intersects(Plane plane, out float& distance) const
	{ 
		distance = Intersects(plane);
	}

	const String& Ray::ToString() const
	{
		return "{Position:"+ Position.ToString() + " Direction:" + Direction.ToString() + "}";
	}

	bool Ray::operator==(const Ray& right) const
	{
		return ((Direction == right.Direction) && (Position == right.Position));
	}

	bool Ray::operator!=(const Ray& right) const
	{
		return ((Direction != right.Direction) || (Position != right.Position));
	}
}
