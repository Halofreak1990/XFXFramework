// Copyright (C) 2010-2012, XFX Team
// All rights reserved.
// 
// Redistribution and use in source and binary forms, with or without 
// modification, are permitted provided that the following conditions are met:
// 
//* Redistributions of source code must retain the above copyright 
//notice, this list of conditions and the following disclaimer.
//* Redistributions in binary form must reproduce the above copyright 
//notice, this list of conditions and the following disclaimer in the 
//documentation and/or other materials provided with the distribution.
//* Neither the name of the copyright holder nor the names of any 
//contributors may be used to endorse or promote products derived from 
//this software without specific prior written permission.
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

#include <System/Math.h>
#include <MathHelper.h>
#include <Matrix.h>
#include <Plane.h>
#include <Quaternion.h>
#include <Vector3.h>

#include <sassert.h>

using namespace System;

namespace XFX
{
	const Matrix Matrix::Identity = Matrix(1.0f, 0, 0, 0, 0, 1.0f, 0, 0, 0, 0, 1.0f, 0, 0, 0, 0, 1.0f);
	
	Matrix::Matrix(float m11, float m12, float m13, float m14, float m21, float m22, float m23, float m24, float m31, float m32, float m33, float m34, float m41, float m42, float m43, float m44)
	{
		M11 = m11;
		M12 = m12;
		M13 = m13;
		M14 = m14;
		M21 = m21;
		M22 = m22;
		M23 = m23;
		M24 = m24;
		M31 = m31;
		M32 = m32;
		M33 = m33;
		M34 = m34;
		M41 = m41;
		M42 = m42;
		M43 = m43;
		M44 = m44;
	}
	
	Matrix::Matrix(const Matrix &obj)
	{
		M11 = obj.M11;
		M12 = obj.M12;
		M13 = obj.M13;
		M14 = obj.M14;
		M21 = obj.M21;
		M22 = obj.M22;
		M23 = obj.M23;
		M24 = obj.M24;
		M31 = obj.M31;
		M32 = obj.M32;
		M33 = obj.M33;
		M34 = obj.M34;
		M41 = obj.M41;
		M42 = obj.M42;
		M43 = obj.M43;
		M44 = obj.M44;
	}
	
	Matrix::Matrix()
	{
		M11 = 0;
		M12 = 0;
		M13 = 0;
		M14 = 0;
		M21 = 0;
		M22 = 0;
		M23 = 0;
		M24 = 0;
		M31 = 0;
		M32 = 0;
		M33 = 0;
		M34 = 0;
		M41 = 0;
		M42 = 0;
		M43 = 0;
		M44 = 0;
	}
	
	Vector3 Matrix::Backward()
	{
		return Vector3(M31, M32, M33);
	}
	
	void Matrix::Backward(Vector3 vector)
	{
		M31 = vector.X;
		M32 = vector.Y;
		M33 = vector.Z;
	}
	
	Vector3 Matrix::Down()
	{
		return Vector3(-M21, -M22, -M23);
	}
	
	void Matrix::Down(Vector3 vector)
	{
		M21 = -vector.X;
		M22 = -vector.Y;
		M23 = -vector.Z;
	}
	
	Vector3 Matrix::Forward()
	{
		return Vector3(-M31, -M32, -M33);
	}
	
	void Matrix::Forward(Vector3 vector)
	{
		M31 = -vector.X;
		M32 = -vector.Y;
		M33 = -vector.Z;
	}
	
	Vector3 Matrix::Left()
	{
		return Vector3(-M11, -M12, -M13);
	}
	
	void Matrix::Left(Vector3 vector)
	{
		M11 = -vector.X;
		M12 = -vector.Y;
		M13 = -vector.Z;
	}
	
	Vector3 Matrix::Right()
	{
		return Vector3(M11, M12, M13);
	}
	
	void Matrix::Right(Vector3 vector)
	{
		M11 = vector.X;
		M12 = vector.Y;
		M13 = vector.Z;
	}
	
	Vector3 Matrix::Translation()
	{
		return Vector3(M41, M42, M43);
	}
	
	void Matrix::Translation(Vector3 vector)
	{
		M41 = vector.X;
		M42 = vector.Y;
		M43 = vector.Z;
	}
	
	Vector3 Matrix::Up()
	{
		return Vector3(M21, M22, M23);
	}
	
	void Matrix::Up(Vector3 vector)
	{
		M21 = vector.X;
		M22 = vector.Y;
		M23 = vector.Z;
	}
	
	Matrix Matrix::Add(Matrix matrix1, Matrix matrix2)
	{
		Matrix result;
		Add(matrix1, matrix2, result);
		return result;
	}
	
	void Matrix::Add(Matrix matrix1, Matrix matrix2, out Matrix result)
	{
		result.M11 = matrix1.M11 + matrix2.M11;
		result.M12 = matrix1.M12 + matrix2.M12;
		result.M13 = matrix1.M13 + matrix2.M13;
		result.M14 = matrix1.M14 + matrix2.M14;
		result.M21 = matrix1.M21 + matrix2.M21;
		result.M22 = matrix1.M22 + matrix2.M22;
		result.M23 = matrix1.M23 + matrix2.M23;
		result.M24 = matrix1.M24 + matrix2.M24;
		result.M31 = matrix1.M31 + matrix2.M31;
		result.M32 = matrix1.M32 + matrix2.M32;
		result.M33 = matrix1.M33 + matrix2.M33;
		result.M34 = matrix1.M34 + matrix2.M34;
		result.M41 = matrix1.M41 + matrix2.M41;
		result.M42 = matrix1.M42 + matrix2.M42;
		result.M43 = matrix1.M43 + matrix2.M43;
		result.M44 = matrix1.M44 + matrix2.M44;
	}
	
	Matrix Matrix::CreateBillboard(Vector3 objectPosition, Vector3 cameraPosition, Vector3 cameraUpVector, Vector3* cameraForwardVector)
	{
		Matrix result; 
		CreateBillboard(objectPosition, cameraPosition, cameraUpVector, cameraForwardVector, result);
		return result; 
	}
	
	void Matrix::CreateBillboard(Vector3 objectPosition, Vector3 cameraPosition, Vector3 cameraUpVector, Vector3* cameraForwardVector, out Matrix result)
	{
		Vector3 vector;
        Vector3 vector2;
        Vector3 vector3;
        vector.X = objectPosition.X - cameraPosition.X;
        vector.Y = objectPosition.Y - cameraPosition.Y;
        vector.Z = objectPosition.Z - cameraPosition.Z;
        float num = vector.LengthSquared();
        if (num < 0.0001f)
        {
			vector = (cameraForwardVector != null) ? -Vector3(cameraForwardVector->X, cameraForwardVector->Y, cameraForwardVector->Z) : Vector3::Forward;
        }
        else
        {
			Vector3::Multiply(vector, (float) (1.0f / ((float) Math::Sqrt((double) num))), vector);
        }
		Vector3::Cross(cameraUpVector, vector, vector3);
		vector3.Normalize();
		Vector3::Cross(vector, vector3, vector2);
        result.M11 = vector3.X;
        result.M12 = vector3.Y;
        result.M13 = vector3.Z;
        result.M14 = 0.0f;
        result.M21 = vector2.X;
        result.M22 = vector2.Y;
        result.M23 = vector2.Z;
        result.M24 = 0.0f;
        result.M31 = vector.X;
        result.M32 = vector.Y;
        result.M33 = vector.Z;
        result.M34 = 0.0f;
        result.M41 = objectPosition.X;
        result.M42 = objectPosition.Y;
        result.M43 = objectPosition.Z;
        result.M44 = 1.0f;
	} 

	Matrix Matrix::CreateConstrainedBillboard(Vector3 objectPosition, Vector3 cameraPosition, Vector3 rotateAxis, Vector3* cameraForwardVector, Vector3* objectForwardVector)
	{
		Matrix result;
		CreateConstrainedBillboard(objectPosition, cameraPosition, rotateAxis, cameraForwardVector, objectForwardVector, result);
		return result;
	}

	void Matrix::CreateConstrainedBillboard(Vector3 objectPosition, Vector3 cameraPosition, Vector3 rotateAxis, Vector3* cameraForwardVector, Vector3* objectForwardVector, out Matrix result)
	{
		float num = 0.0f;
        Vector3 vector;
        Vector3 vector2;
        Vector3 vector3;
        vector2.X = objectPosition.X - cameraPosition.X;
        vector2.Y = objectPosition.Y - cameraPosition.Y;
        vector2.Z = objectPosition.Z - cameraPosition.Z;
        float num2 = vector2.LengthSquared();
        if (num2 < 0.0001f)
        {
			vector2 = (cameraForwardVector != null) ? -Vector3(cameraForwardVector->X, cameraForwardVector->Y, cameraForwardVector->Z) : Vector3::Forward;
        }
        else
        {
			Vector3::Multiply(vector2, (float) (1.0f / ((float) Math::Sqrt((double) num2))), vector2);
        }
        Vector3 vector4 = rotateAxis;
		Vector3::Dot(rotateAxis, vector2, num);
		if (Math::Abs(num) > 0.9982547f)
        {
            if (objectForwardVector != null)
            {
                vector = Vector3(objectForwardVector->X, objectForwardVector->Y, objectForwardVector->Z);
				Vector3::Dot(rotateAxis, vector, num);
				if (Math::Abs(num) > 0.9982547f)
                {
					num = ((rotateAxis.X * Vector3::Forward.X) + (rotateAxis.Y * Vector3::Forward.Y)) + (rotateAxis.Z * Vector3::Forward.Z);
					vector = (Math::Abs(num) > 0.9982547f) ? Vector3::Right : Vector3::Forward;
                }
            }
            else
            {
				num = ((rotateAxis.X * Vector3::Forward.X) + (rotateAxis.Y * Vector3::Forward.Y)) + (rotateAxis.Z * Vector3::Forward.Z);
				vector = (Math::Abs(num) > 0.9982547f) ? Vector3::Right : Vector3::Forward;
            }
			Vector3::Cross(rotateAxis, vector, vector3);
            vector3.Normalize();
			Vector3::Cross(vector3, rotateAxis, vector);
            vector.Normalize();
        }
        else
        {
			Vector3::Cross(rotateAxis, vector2, vector3);
			vector3.Normalize();
			Vector3::Cross(vector3, vector4, vector);
            vector.Normalize();
        }
        result.M11 = vector3.X;
        result.M12 = vector3.Y;
        result.M13 = vector3.Z;
        result.M14 = 0.0f;
        result.M21 = vector4.X;
        result.M22 = vector4.Y;
        result.M23 = vector4.Z;
        result.M24 = 0.0f;
        result.M31 = vector.X;
        result.M32 = vector.Y;
        result.M33 = vector.Z;
        result.M34 = 0.0f;
        result.M41 = objectPosition.X;
        result.M42 = objectPosition.Y;
        result.M43 = objectPosition.Z;
        result.M44 = 1.0f;
	}

	Matrix Matrix::CreateFromAxisAngle(Vector3 axis,float angle)
	{
		Matrix result;
		CreateFromAxisAngle(axis, angle, result);
 		return result;
	}
	
	void Matrix::CreateFromAxisAngle(Vector3 axis, float angle, out Matrix result) 
	{ 
 		if(axis.LengthSquared() != 1.0f) 
			axis.Normalize(); 

 		float x = axis.X; 
 		float y = axis.Y; 
 		float z = axis.Z; 
 		float cos = Math::Cos(angle); 
 		float sin = Math::Sin(angle); 
 		float xx = x * x; 
 		float yy = y * y; 
 		float zz = z * z; 
 		float xy = x * y; 
 		float xz = x * z; 
 		float yz = y * z; 

 		result.M11 = xx + (cos * (1.0f - xx)); 
 		result.M12 = (xy - (cos * xy)) + (sin * z); 
 		result.M13 = (xz - (cos * xz)) - (sin * y); 
 		result.M14 = 0.0f; 
 		result.M21 = (xy - (cos * xy)) - (sin * z); 
 		result.M22 = yy + (cos * (1.0f - yy)); 
 		result.M23 = (yz - (cos * yz)) + (sin * x); 
 		result.M24 = 0.0f; 
 		result.M31 = (xz - (cos * xz)) + (sin * y); 
 		result.M32 = (yz - (cos * yz)) - (sin * x); 
 		result.M33 = zz + (cos * (1.0f - zz)); 
 		result.M34 = 0.0f; 
 		result.M41 = 0.0f; 
 		result.M42 = 0.0f; 
 		result.M43 = 0.0f; 
 		result.M44 = 1.0f; 
	}

	Matrix Matrix::CreateFromQuaternion(Quaternion rotation)
	{
		Matrix result;
		CreateFromQuaternion(rotation, result);
		return result;
	}
	
	void Matrix::CreateFromQuaternion(Quaternion rotation, out Matrix result) 
	{ 
		float xx = rotation.X * rotation.X; 
		float yy = rotation.Y * rotation.Y; 
		float zz = rotation.Z * rotation.Z; 
		float xy = rotation.X * rotation.Y; 
		float zw = rotation.Z * rotation.W; 
		float zx = rotation.Z * rotation.X; 
		float yw = rotation.Y * rotation.W; 
		float yz = rotation.Y * rotation.Z; 
		float xw = rotation.X * rotation.W; 
		
		result.M11 = 1.0f - (2.0f * (yy + zz)); 
		result.M12 = 2.0f * (xy + zw);
		result.M13 = 2.0f * (zx - yw); 
		result.M14 = 0.0f; 
		result.M21 = 2.0f * (xy - zw);
		result.M22 = 1.0f - (2.0f * (zz + xx)); 
		result.M23 = 2.0f * (yz + xw); 
		result.M24 = 0.0f; 
		result.M31 = 2.0f * (zx + yw); 
		result.M32 = 2.0f * (yz - xw); 
		result.M33 = 1.0f - (2.0f * (yy + xx)); 
		result.M34 = 0.0f; 
		result.M41 = 0.0f; 
		result.M42 = 0.0f; 
		result.M43 = 0.0f; 
		result.M44 = 1.0f; 
	}

	Matrix Matrix::CreateFromYawPitchRoll(float yaw, float pitch, float roll) 
	{ 
        Matrix result; 
        CreateFromYawPitchRoll(yaw, pitch, roll, result);
        return result; 
	}

	void Matrix::CreateFromYawPitchRoll(float yaw, float pitch, float roll, out Matrix result) 
	{ 
        Quaternion quaternion; 
        Quaternion::CreateFromYawPitchRoll(yaw, pitch, roll, quaternion); 
        CreateFromQuaternion(quaternion, result); 
	}
	
	Matrix Matrix::CreateLookAt(Vector3 cameraPosition, Vector3 cameraTarget, Vector3 cameraUpVector)
	{
		Matrix result;
		CreateLookAt(cameraPosition, cameraTarget, cameraUpVector, result);
		return result;
	}

	void Matrix::CreateLookAt(Vector3 cameraPosition, Vector3 cameraTarget, Vector3 cameraUpVector, out Matrix result)
	{
		Vector3 xaxis, yaxis, zaxis;
		Vector3::Subtract(cameraPosition, cameraTarget, zaxis);
		zaxis.Normalize();
		Vector3::Cross(cameraUpVector, zaxis, xaxis); 
		xaxis.Normalize();
		Vector3::Cross(zaxis, xaxis, yaxis);
		result = Matrix::Identity;
		result.M11 = xaxis.X;
		result.M21 = xaxis.Y;
		result.M31 = xaxis.Z;
		result.M12 = yaxis.X;
		result.M22 = yaxis.Y;
		result.M32 = yaxis.Z;
		result.M13 = zaxis.X;
		result.M23 = zaxis.Y;
		result.M33 = zaxis.Z;
		Vector3::Dot(xaxis, cameraPosition, result.M41);
		Vector3::Dot(yaxis, cameraPosition, result.M42);
		Vector3::Dot(zaxis, cameraPosition, result.M43);
		result.M41 = -result.M41;
		result.M42 = -result.M42;
		result.M43 = -result.M43;
	}

	Matrix Matrix::CreateOrthographic(float width, float height, float zNearPlane, float zFarPlane)
	{
		Matrix result;
		CreateOrthographic(width, height, zNearPlane, zFarPlane, result);
		return result;
	}

	void Matrix::CreateOrthographic(float width, float height, float zNearPlane, float zFarPlane, out Matrix result)
	{
		float halfWidth = width * 0.5f;
		float halfHeight = height * 0.5f;
		CreateOrthographicOffCenter(-halfWidth, halfWidth, -halfHeight, halfHeight, zNearPlane, zFarPlane, result);
	}

	Matrix Matrix::CreateOrthographicOffCenter(float left, float right, float bottom, float top, float zNearPlane, float zFarPlane)
	{
		Matrix result;
		CreateOrthographicOffCenter(left, right, bottom, top, zNearPlane, zFarPlane, result);
		return result;
	}

	void Matrix::CreateOrthographicOffCenter(float left, float right, float bottom, float top, float zNearPlane, float zFarPlane, out Matrix result)
	{
		float zRange = 1.0f / (zFarPlane - zNearPlane);
		result = Matrix::Identity;
		result.M11 = 2.0f / (right - left);
		result.M22 = 2.0f / (top - bottom);
		result.M33 = zRange;
		result.M41 = (left + right) / (left - right);
		result.M42 = (top + bottom) / (bottom - top);
		result.M43 = -zNearPlane * zRange;

		result.M33 *= -1.0f;
	}

	Matrix Matrix::CreatePerspective(float width, float height, float zNearPlane, float zFarPlane)
	{
		Matrix result;
		CreatePerspective(width, height, zNearPlane, zFarPlane);
		return result;
	}

	void Matrix::CreatePerspective(float width, float height, float zNearPlane, float zFarPlane, out Matrix result)
	{
		float halfWidth = width * 0.5f;
		float halfHeight = height * 0.5f;
		CreatePerspectiveOffCenter(-halfWidth, halfWidth, -halfHeight, halfHeight, zNearPlane, zFarPlane, result);
	}

	Matrix Matrix::CreatePerspectiveFieldOfView(float fieldOfView, float aspectRatio, float nearPlaneDistance, float farPlaneDistance)
	{
		Matrix result;
		CreatePerspectiveFieldOfView(fieldOfView, aspectRatio, nearPlaneDistance, farPlaneDistance);
		return result;
	}

	void Matrix::CreatePerspectiveFieldOfView(float fieldOfView, float aspectRatio, float nearPlaneDistance, float farPlaneDistance, out Matrix result)
	{
		float yScale = (float)(1.0 / Math::Tan(fieldOfView * 0.5f));
		float xScale = yScale / aspectRatio;
		float halfWidth = nearPlaneDistance / xScale;
		float halfHeight = nearPlaneDistance / yScale;
		CreatePerspectiveOffCenter(-halfWidth, halfWidth, -halfHeight, halfHeight, nearPlaneDistance, farPlaneDistance, result);
	}

	Matrix Matrix::CreatePerspectiveOffCenter(float left, float right, float bottom, float top, float nearPlaneDistance, float farPlaneDistance)
	{
		Matrix result;
		CreatePerspectiveOffCenter(left, right, bottom, top, nearPlaneDistance, farPlaneDistance, result);
		return result;
	}

	void Matrix::CreatePerspectiveOffCenter(float left, float right, float bottom, float top, float nearPlaneDistance, float farPlaneDistance, out Matrix result)
	{
		sassert(nearPlaneDistance > 0.0f, "You should specify a positive value for nearPlaneDistance.");

		sassert(farPlaneDistance > 0.0f, "You should specify a positive value for farPlaneDistance.");

		sassert(nearPlaneDistance < farPlaneDistance, "Near plane distance is larger than Far plane distance. Near plane distance must be smaller than Far plane distance.");

		result.M11 = (2.0f * nearPlaneDistance) / (right - left);
		result.M12 = result.M13 = result.M14 = 0.0f;
		result.M22 = (2.0f * nearPlaneDistance) / (top - bottom);
		result.M21 = result.M23 = result.M24 = 0.0f;
		result.M31 = (left + right) / (right - left);
		result.M32 = (top + bottom) / (top - bottom);
		result.M33 = farPlaneDistance / (nearPlaneDistance - farPlaneDistance);
		result.M34 = -1.0f;
		result.M43 = (nearPlaneDistance * farPlaneDistance) / (nearPlaneDistance - farPlaneDistance);
		result.M41 = result.M42 = result.M44 = 0.0f;
	}
	
	void Matrix::CreateReflection(Plane value, out Matrix result) 
    { 
		value.Normalize(); 
    	float x = value.Normal.X; 
    	float y = value.Normal.Y; 
    	float z = value.Normal.Z; 
    	float x2 = -2.0f * x; 
    	float y2 = -2.0f * y; 
    	float z2 = -2.0f * z; 
    	result.M11 = (x2 * x) + 1.0f; 
    	result.M12 = y2 * x; 
    	result.M13 = z2 * x; 
    	result.M14 = 0.0f; 
    	result.M21 = x2 * y; 
    	result.M22 = (y2 * y) + 1.0f; 
    	result.M23 = z2 * y; 
    	result.M24 = 0.0f; 
    	result.M31 = x2 * z; 
    	result.M32 = y2 * z; 
    	result.M33 = (z2 * z) + 1.0f; 
    	result.M34 = 0.0f; 
    	result.M41 = x2 * value.D; 
    	result.M42 = y2 * value.D; 
    	result.M43 = z2 * value.D; 
    	result.M44 = 1.0f; 
    } 
  
    Matrix Matrix::CreateReflection(Plane value) 
    { 
	    Matrix result; 
    	value.Normalize(); 
    	float x = value.Normal.X; 
    	float y = value.Normal.Y; 
    	float z = value.Normal.Z; 
    	float x2 = -2.0f * x; 
    	float y2 = -2.0f * y; 
    	float z2 = -2.0f * z; 
    	result.M11 = (x2 * x) + 1.0f; 
    	result.M12 = y2 * x; 
    	result.M13 = z2 * x; 
    	result.M14 = 0.0f; 
    	result.M21 = x2 * y; 
    	result.M22 = (y2 * y) + 1.0f; 
    	result.M23 = z2 * y; 
    	result.M24 = 0.0f; 
    	result.M31 = x2 * z; 
    	result.M32 = y2 * z; 
    	result.M33 = (z2 * z) + 1.0f; 
    	result.M34 = 0.0f; 
    	result.M41 = x2 * value.D; 
    	result.M42 = y2 * value.D; 
    	result.M43 = z2 * value.D; 
    	result.M44 = 1.0f; 
    	return result; 
    } 
	
	void Matrix::CreateRotationX(float radians, out Matrix result) 
    { 
		float num2 = (float) Math::Cos((double) radians);
		float num = (float) Math::Sin((double) radians);
		result.M11 = 1.0f;
		result.M12 = 0.0f;
		result.M13 = 0.0f;
		result.M14 = 0.0f;
		result.M21 = 0.0f;
		result.M22 = num2;
		result.M23 = num;
		result.M24 = 0.0f;
		result.M31 = 0.0f;
		result.M32 = -num;
		result.M33 = num2;
		result.M34 = 0.0f;
		result.M41 = 0.0f;
		result.M42 = 0.0f;
		result.M43 = 0.0f;
		result.M44 = 1.0f;
	}
	
	Matrix Matrix::CreateRotationX(float radians) 
    { 
    	Matrix result;
		CreateRotationX(radians, result);
    	return result; 
    }
    
    void Matrix::CreateRotationY(float radians, out Matrix result) 
    { 
		float num2 = (float) Math::Cos((double) radians);
		float num = (float) Math::Sin((double) radians);
		result.M11 = num2;
		result.M12 = 0.0f;
		result.M13 = -num;
		result.M14 = 0.0f;
		result.M21 = 0.0f;
		result.M22 = 1.0f;
		result.M23 = 0.0f;
		result.M24 = 0.0f;
		result.M31 = num;
		result.M32 = 0.0f;
		result.M33 = num2;
		result.M34 = 0.0f;
		result.M41 = 0.0f;
		result.M42 = 0.0f;
		result.M43 = 0.0f;
		result.M44 = 1.0f;
    }
    
    Matrix Matrix::CreateRotationY(float radians) 
    { 
    	Matrix result;
		CreateRotationY(radians, result);
    	return result; 
    }
    
    void Matrix::CreateRotationZ(float radians, out Matrix result) 
    { 
		float num2 = (float) Math::Cos((double) radians);
		float num = (float) Math::Sin((double) radians);
		result.M11 = num2;
		result.M12 = num;
		result.M13 = 0.0f;
		result.M14 = 0.0f;
		result.M21 = -num;
		result.M22 = num2;
		result.M23 = 0.0f;
		result.M24 = 0.0f;
		result.M31 = 0.0f;
		result.M32 = 0.0f;
		result.M33 = 1.0f;
		result.M34 = 0.0f;
		result.M41 = 0.0f;
		result.M42 = 0.0f;
		result.M43 = 0.0f;
		result.M44 = 1.0f;
    }
    
	Matrix Matrix::CreateRotationZ(float radians) 
    { 
    	Matrix result; 
		CreateRotationZ(radians, result);
		return result; 
    }
    
    void Matrix::CreateScale(float scale, out Matrix result)
    {
	    float num = scale;
        result.M11 = num;
        result.M12 = 0.0f;
        result.M13 = 0.0f;
        result.M14 = 0.0f;
        result.M21 = 0.0f;
        result.M22 = num;
        result.M23 = 0.0f;
        result.M24 = 0.0f;
        result.M31 = 0.0f;
        result.M32 = 0.0f;
        result.M33 = num;
        result.M34 = 0.0f;
        result.M41 = 0.0f;
        result.M42 = 0.0f;
        result.M43 = 0.0f;
        result.M44 = 1.0f;
    }
    
    Matrix Matrix::CreateScale(float scale) 
    { 
    	Matrix result;
		CreateScale(scale, result);
		return result;
    } 
    
    void Matrix::CreateScale(float xScale, float yScale, float zScale, out Matrix result) 
    { 
    	float num3 = xScale;
        float num2 = yScale;
        float num = zScale;
        result.M11 = num3;
        result.M12 = 0.0f;
        result.M13 = 0.0f;
        result.M14 = 0.0f;
        result.M21 = 0.0f;
        result.M22 = num2;
        result.M23 = 0.0f;
        result.M24 = 0.0f;
        result.M31 = 0.0f;
        result.M32 = 0.0f;
        result.M33 = num;
        result.M34 = 0.0f;
        result.M41 = 0.0f;
        result.M42 = 0.0f;
        result.M43 = 0.0f;
        result.M44 = 1.0f;
    }
    
    Matrix Matrix::CreateScale(float xScale, float yScale, float zScale) 
    { 
    	Matrix result;
		CreateScale(xScale, yScale, zScale, result);
    	return result; 
    }
    
    void Matrix::CreateScale(Vector3 scales, out Matrix result) 
    { 
    	float x = scales.X;
        float y = scales.Y;
        float z = scales.Z;
        result.M11 = x;
        result.M12 = 0.0f;
        result.M13 = 0.0f;
        result.M14 = 0.0f;
        result.M21 = 0.0f;
        result.M22 = y;
        result.M23 = 0.0f;
        result.M24 = 0.0f;
        result.M31 = 0.0f;
        result.M32 = 0.0f;
        result.M33 = z;
        result.M34 = 0.0f;
        result.M41 = 0.0f;
        result.M42 = 0.0f;
        result.M43 = 0.0f;
        result.M44 = 1.0f;
    }
    
    Matrix Matrix::CreateScale(Vector3 scales) 
    { 
    	Matrix result; 
		CreateScale(scales, result);
    	return result; 
    }  
    
    void Matrix::CreateShadow(Vector3 lightDirection, Plane plane, out Matrix result)
    {
	    plane.Normalize(); 
    	float dot = ((plane.Normal.X * lightDirection.X) + (plane.Normal.Y * lightDirection.Y)) + (plane.Normal.Z * lightDirection.Z); 
    	float x = -plane.Normal.X; 
    	float y = -plane.Normal.Y; 
    	float z = -plane.Normal.Z; 
    	float d = -plane.D; 
    	result.M11 = (x * lightDirection.X) + dot; 
    	result.M21 = y * lightDirection.X; 
    	result.M31 = z * lightDirection.X; 
    	result.M41 = d * lightDirection.X; 
    	result.M12 = x * lightDirection.Y; 
     	result.M22 = (y * lightDirection.Y) + dot; 
     	result.M32 = z * lightDirection.Y; 
    	result.M42 = d * lightDirection.Y; 
     	result.M13 = x * lightDirection.Z; 
    	result.M23 = y * lightDirection.Z; 
    	result.M33 = (z * lightDirection.Z) + dot; 
    	result.M43 = d * lightDirection.Z; 
    	result.M14 = 0.0f; 
    	result.M24 = 0.0f; 
    	result.M34 = 0.0f; 
    	result.M44 = dot; 
    }
    
    Matrix Matrix::CreateShadow(Vector3 lightDirection, Plane plane)
    {
	    Matrix result;
	    CreateShadow(lightDirection, plane, result);
	    return result;
    }
    
    void Matrix::CreateTranslation(float xPosition, float yPosition, float zPosition, out Matrix result) 
    { 
    	result.M11 = 1.0f;
        result.M12 = 0.0f;
        result.M13 = 0.0f;
        result.M14 = 0.0f;
        result.M21 = 0.0f;
        result.M22 = 1.0f;
        result.M23 = 0.0f;
        result.M24 = 0.0f;
        result.M31 = 0.0f;
        result.M32 = 0.0f;
        result.M33 = 1.0f;
        result.M34 = 0.0f;
        result.M41 = xPosition;
        result.M42 = yPosition;
        result.M43 = zPosition;
        result.M44 = 1.0f;
    } 
    
    Matrix Matrix::CreateTranslation(float xPosition, float yPosition, float zPosition)
    {
	    Matrix result;
	    CreateTranslation(xPosition, yPosition, zPosition, result);
    	return result;
    }
    
    void Matrix::CreateTranslation(Vector3 position, out Matrix result) 
    { 
    	result.M11 = 1.0f;
        result.M12 = 0.0f;
        result.M13 = 0.0f;
        result.M14 = 0.0f;
        result.M21 = 0.0f;
        result.M22 = 1.0f;
        result.M23 = 0.0f;
        result.M24 = 0.0f;
        result.M31 = 0.0f;
        result.M32 = 0.0f;
        result.M33 = 1.0f;
        result.M34 = 0.0f;
        result.M41 = position.X;
        result.M42 = position.Y;
        result.M43 = position.Z;
        result.M44 = 1.0f;
    }
    
    Matrix Matrix::CreateTranslation(Vector3 position)
    {
	    Matrix result;
	    CreateTranslation(position, result);
	    return result;
    }

	Matrix Matrix::CreateWorld(Vector3 position, Vector3 forward, Vector3 up) 
	{ 
 		Matrix ret; 
 		CreateWorld(position, forward, up, out ret); 
 		return ret; 
	}

	void Matrix::CreateWorld(Vector3 position, Vector3 forward, Vector3 up, out Matrix result) 
	{ 
		Vector3 vector = Vector3::Normalize(position - forward);
		Vector3 vector2 = Vector3::Normalize(Vector3::Cross(up, vector));
		Vector3 vector3 = Vector3::Cross(vector, vector2);
		result.M11 = vector2.X;
		result.M12 = vector2.Y;
		result.M13 = vector2.Z;
		result.M21 = vector3.X;
		result.M22 = vector3.Y;
		result.M23 = vector3.Z;
		result.M31 = vector.X;
		result.M32 = vector.Y;
		result.M33 = vector.Z;
		result.M41 = 0;
		result.M42 = 0;
		result.M43 = 0;
		result.M44 = 1;
		result.M14 = -Vector3::Dot(vector2, position);
		result.M24 = -Vector3::Dot(vector3, position);
		result.M34 = -Vector3::Dot(vector, position);
	}

	int Matrix::Decompose(Vector3 scale, Quaternion rotation, Vector3 translation)
	{
		translation.X = M41;
		translation.Y = M42;
		translation.Z = M43;
		float xs, ys, zs;
		if (Math::Sign(M11 * M12 * M13 * M14) < 0)
			xs = -1.0f;
		else
			xs = 1.0f;
		if (Math::Sign(M21 * M22 * M23 * M24) < 0)
			ys = -1.0f;
		else
			ys = 1.0f;
		if (Math::Sign(M31 * M32 * M33 * M34) < 0)
			zs = -1.0f;
		else
			zs = 1.0f;
		scale.X = xs * (float)Math::Sqrt(M11 * M11 + M12 * M12 + M13 * M13);
		scale.Y = ys * (float)Math::Sqrt(M21 * M21 + M22 * M22 + M23 * M23);
		scale.Z = zs * (float)Math::Sqrt(M31 * M31 + M32 * M32 + M33 * M33);
		if (scale.X == 0.0 || scale.Y == 0.0 || scale.Z == 0.0)
		{
			rotation = Quaternion::Identity;
			return false;
		}
		Matrix m1 = Matrix(M11/scale.X, M12/scale.X, M13/scale.X, 0, 
			M21/scale.Y, M22/scale.Y, M23/scale.Y, 0,
			M31/scale.Z, M32/scale.Z, M33/scale.Z, 0,
			0, 0, 0, 1);
		rotation = Quaternion::CreateFromRotationMatrix(m1);
		return true;
	}

	float Matrix::Determinant() 
    { 
    	float temp1 = (M33 * M44) - (M34 * M43); 
   		float temp2 = (M32 * M44) - (M34 * M42); 
    	float temp3 = (M32 * M43) - (M33 * M42); 
    	float temp4 = (M31 * M44) - (M34 * M41); 
    	float temp5 = (M31 * M43) - (M33 * M41); 
    	float temp6 = (M31 * M42) - (M32 * M41); 
 
    	return ((((M11 * (((M22 * temp1) - (M23 * temp2)) + (M24 * temp3))) - (M12 * (((M21 * temp1) -  
        	(M23 * temp4)) + (M24 * temp5)))) + (M13 * (((M21 * temp2) - (M22 * temp4)) + (M24 * temp6)))) -  
        	(M14 * (((M21 * temp3) - (M22 * temp5)) + (M23 * temp6)))); 
    } 

	Matrix Matrix::Divide(Matrix matrix1, Matrix matrix2)
    {
	    Matrix result;
	    Divide(matrix1, matrix2, result);
	    return result;
    }

    void Matrix::Divide(Matrix matrix1, Matrix matrix2, out Matrix result) 
    { 
    	Matrix inverse = Matrix::Invert(matrix2); 
        Matrix::Multiply(matrix1, inverse, result); 
    }
    
    void Matrix::Divide(Matrix matrix1, float divider, out Matrix result)
    {
	    float num = 1 / divider;
		result.M11 = matrix1.M11 * num;
		result.M12 = matrix1.M12 * num;
		result.M13 = matrix1.M13 * num;
		result.M14 = matrix1.M14 * num;
		result.M21 = matrix1.M21 * num;
		result.M22 = matrix1.M22 * num;
		result.M23 = matrix1.M23 * num;
		result.M24 = matrix1.M24 * num;
		result.M31 = matrix1.M31 * num;
		result.M32 = matrix1.M32 * num;
		result.M33 = matrix1.M33 * num;
		result.M34 = matrix1.M34 * num;
		result.M41 = matrix1.M41 * num;
		result.M42 = matrix1.M42 * num;
		result.M43 = matrix1.M43 * num;
		result.M44 = matrix1.M44 * num;
    }
    
    Matrix Matrix::Divide(Matrix matrix1, float divider)
    {
	    Matrix result;
	    Divide(matrix1, divider, result);
	    return result;
    }
    
    bool Matrix::Equals(const Matrix other) const
    { 
    	return ((M11 == other.M11) & (M12 == other.M12) & (M13 == other.M13) & (M14 == other.M14) &
				(M21 == other.M21) & (M22 == other.M22) & (M23 == other.M23) & (M24 == other.M24) &
				(M31 == other.M31) & (M32 == other.M32) & (M33 == other.M33) & (M34 == other.M34) &
				(M41 == other.M41) & (M42 == other.M42) & (M43 == other.M43) & (M44 == other.M44));
    } 

	int Matrix::GetHashCode() const
	{
		return ((int)M11 ^ (int)M12 ^ (int)M13 ^ (int)M14 ^ (int)M21 ^ (int)M22 ^ (int)M23 ^ (int)M24 ^
			(int)M31 ^ (int)M32 ^ (int)M33 ^ (int)M34 ^ (int)M41 ^ (int)M42 ^ (int)M43 ^ (int)M44);
	}
    
    void Matrix::Invert(Matrix matrix, out Matrix result) 
    {       
    	float num5 = matrix.M11;
		float num4 = matrix.M12;
		float num3 = matrix.M13;
		float num2 = matrix.M14;
		float num9 = matrix.M21;
		float num8 = matrix.M22;
		float num7 = matrix.M23;
		float num6 = matrix.M24;
		float num17 = matrix.M31;
		float num16 = matrix.M32;
		float num15 = matrix.M33;
		float num14 = matrix.M34;
		float num13 = matrix.M41;
		float num12 = matrix.M42;
		float num11 = matrix.M43;
		float num10 = matrix.M44;
		float num23 = (num15 * num10) - (num14 * num11);
		float num22 = (num16 * num10) - (num14 * num12);
		float num21 = (num16 * num11) - (num15 * num12);
		float num20 = (num17 * num10) - (num14 * num13);
		float num19 = (num17 * num11) - (num15 * num13);
		float num18 = (num17 * num12) - (num16 * num13);
		float num39 = ((num8 * num23) - (num7 * num22)) + (num6 * num21);
		float num38 = -(((num9 * num23) - (num7 * num20)) + (num6 * num19));
		float num37 = ((num9 * num22) - (num8 * num20)) + (num6 * num18);
		float num36 = -(((num9 * num21) - (num8 * num19)) + (num7 * num18));
		float num = 1.0f / ((((num5 * num39) + (num4 * num38)) + (num3 * num37)) + (num2 * num36));
		result.M11 = num39 * num;
		result.M21 = num38 * num;
		result.M31 = num37 * num;
		result.M41 = num36 * num;
		result.M12 = -(((num4 * num23) - (num3 * num22)) + (num2 * num21)) * num;
		result.M22 = (((num5 * num23) - (num3 * num20)) + (num2 * num19)) * num;
		result.M32 = -(((num5 * num22) - (num4 * num20)) + (num2 * num18)) * num;
		result.M42 = (((num5 * num21) - (num4 * num19)) + (num3 * num18)) * num;
		float num35 = (num7 * num10) - (num6 * num11);
		float num34 = (num8 * num10) - (num6 * num12);
		float num33 = (num8 * num11) - (num7 * num12);
		float num32 = (num9 * num10) - (num6 * num13);
		float num31 = (num9 * num11) - (num7 * num13);
		float num30 = (num9 * num12) - (num8 * num13);
		result.M13 = (((num4 * num35) - (num3 * num34)) + (num2 * num33)) * num;
		result.M23 = -(((num5 * num35) - (num3 * num32)) + (num2 * num31)) * num;
		result.M33 = (((num5 * num34) - (num4 * num32)) + (num2 * num30)) * num;
		result.M43 = -(((num5 * num33) - (num4 * num31)) + (num3 * num30)) * num;
		float num29 = (num7 * num14) - (num6 * num15);
		float num28 = (num8 * num14) - (num6 * num16);
		float num27 = (num8 * num15) - (num7 * num16);
		float num26 = (num9 * num14) - (num6 * num17);
		float num25 = (num9 * num15) - (num7 * num17);
		float num24 = (num9 * num16) - (num8 * num17);
		result.M14 = -(((num4 * num29) - (num3 * num28)) + (num2 * num27)) * num;
		result.M24 = (((num5 * num29) - (num3 * num26)) + (num2 * num25)) * num;
		result.M34 = -(((num5 * num28) - (num4 * num26)) + (num2 * num24)) * num;
		result.M44 = (((num5 * num27) - (num4 * num25)) + (num3 * num24)) * num;
	} 
	
	Matrix Matrix::Invert(Matrix matrix)
	{
		Invert(matrix, matrix);
		return matrix;
	}
	
	void Matrix::Lerp(Matrix matrix1, Matrix matrix2, float amount, out Matrix result)
	{
		result.M11 = matrix1.M11 + ((matrix2.M11 - matrix1.M11) * amount);
		result.M12 = matrix1.M12 + ((matrix2.M12 - matrix1.M12) * amount);
		result.M13 = matrix1.M13 + ((matrix2.M13 - matrix1.M13) * amount);
		result.M14 = matrix1.M14 + ((matrix2.M14 - matrix1.M14) * amount);
		result.M21 = matrix1.M21 + ((matrix2.M21 - matrix1.M21) * amount);
		result.M22 = matrix1.M22 + ((matrix2.M22 - matrix1.M22) * amount);
		result.M23 = matrix1.M23 + ((matrix2.M23 - matrix1.M23) * amount);
		result.M24 = matrix1.M24 + ((matrix2.M24 - matrix1.M24) * amount);
		result.M31 = matrix1.M31 + ((matrix2.M31 - matrix1.M31) * amount);
		result.M32 = matrix1.M32 + ((matrix2.M32 - matrix1.M32) * amount);
		result.M33 = matrix1.M33 + ((matrix2.M33 - matrix1.M33) * amount);
		result.M34 = matrix1.M34 + ((matrix2.M34 - matrix1.M34) * amount);
		result.M41 = matrix1.M41 + ((matrix2.M41 - matrix1.M41) * amount);
		result.M42 = matrix1.M42 + ((matrix2.M42 - matrix1.M42) * amount);
		result.M43 = matrix1.M43 + ((matrix2.M43 - matrix1.M43) * amount);
		result.M44 = matrix1.M44 + ((matrix2.M44 - matrix1.M44) * amount);
	}
	
	Matrix Matrix::Lerp(Matrix value1, Matrix value2, float amount)
	{
		Matrix result;
		Lerp(value1, value2, amount, result);
		return result;
	}

	Matrix Matrix::Multiply(Matrix matrix1, Matrix matrix2)
    {
	    Matrix result;
	    Multiply(matrix1, matrix2, result);
	    return result;
    }
	
	void Matrix::Multiply(Matrix matrix1, Matrix matrix2, out Matrix result) 
    { 
    	float num16 = (((matrix1.M11 * matrix2.M11) + (matrix1.M12 * matrix2.M21)) + (matrix1.M13 * matrix2.M31)) + (matrix1.M14 * matrix2.M41);
		float num15 = (((matrix1.M11 * matrix2.M12) + (matrix1.M12 * matrix2.M22)) + (matrix1.M13 * matrix2.M32)) + (matrix1.M14 * matrix2.M42);
		float num14 = (((matrix1.M11 * matrix2.M13) + (matrix1.M12 * matrix2.M23)) + (matrix1.M13 * matrix2.M33)) + (matrix1.M14 * matrix2.M43);
		float num13 = (((matrix1.M11 * matrix2.M14) + (matrix1.M12 * matrix2.M24)) + (matrix1.M13 * matrix2.M34)) + (matrix1.M14 * matrix2.M44);
		float num12 = (((matrix1.M21 * matrix2.M11) + (matrix1.M22 * matrix2.M21)) + (matrix1.M23 * matrix2.M31)) + (matrix1.M24 * matrix2.M41);
		float num11 = (((matrix1.M21 * matrix2.M12) + (matrix1.M22 * matrix2.M22)) + (matrix1.M23 * matrix2.M32)) + (matrix1.M24 * matrix2.M42);
		float num10 = (((matrix1.M21 * matrix2.M13) + (matrix1.M22 * matrix2.M23)) + (matrix1.M23 * matrix2.M33)) + (matrix1.M24 * matrix2.M43);
		float num9 = (((matrix1.M21 * matrix2.M14) + (matrix1.M22 * matrix2.M24)) + (matrix1.M23 * matrix2.M34)) + (matrix1.M24 * matrix2.M44);
		float num8 = (((matrix1.M31 * matrix2.M11) + (matrix1.M32 * matrix2.M21)) + (matrix1.M33 * matrix2.M31)) + (matrix1.M34 * matrix2.M41);
		float num7 = (((matrix1.M31 * matrix2.M12) + (matrix1.M32 * matrix2.M22)) + (matrix1.M33 * matrix2.M32)) + (matrix1.M34 * matrix2.M42);
		float num6 = (((matrix1.M31 * matrix2.M13) + (matrix1.M32 * matrix2.M23)) + (matrix1.M33 * matrix2.M33)) + (matrix1.M34 * matrix2.M43);
		float num5 = (((matrix1.M31 * matrix2.M14) + (matrix1.M32 * matrix2.M24)) + (matrix1.M33 * matrix2.M34)) + (matrix1.M34 * matrix2.M44);
		float num4 = (((matrix1.M41 * matrix2.M11) + (matrix1.M42 * matrix2.M21)) + (matrix1.M43 * matrix2.M31)) + (matrix1.M44 * matrix2.M41);
		float num3 = (((matrix1.M41 * matrix2.M12) + (matrix1.M42 * matrix2.M22)) + (matrix1.M43 * matrix2.M32)) + (matrix1.M44 * matrix2.M42);
		float num2 = (((matrix1.M41 * matrix2.M13) + (matrix1.M42 * matrix2.M23)) + (matrix1.M43 * matrix2.M33)) + (matrix1.M44 * matrix2.M43);
		float num = (((matrix1.M41 * matrix2.M14) + (matrix1.M42 * matrix2.M24)) + (matrix1.M43 * matrix2.M34)) + (matrix1.M44 * matrix2.M44);
		result.M11 = num16;
		result.M12 = num15;
		result.M13 = num14;
		result.M14 = num13;
		result.M21 = num12;
		result.M22 = num11;
		result.M23 = num10;
		result.M24 = num9;
		result.M31 = num8;
		result.M32 = num7;
		result.M33 = num6;
		result.M34 = num5;
		result.M41 = num4;
		result.M42 = num3;
		result.M43 = num2;
		result.M44 = num;
    }

	Matrix Matrix::Multiply(Matrix matrix1, float scaleFactor)
    {
	    Matrix result;
		Multiply(matrix1, scaleFactor, result);
		return result;
    }
    
    void Matrix::Multiply(Matrix matrix1, float scaleFactor, out Matrix result) 
    { 
    	float num = scaleFactor;
		result.M11 = matrix1.M11 * num;
		result.M12 = matrix1.M12 * num;
		result.M13 = matrix1.M13 * num;
		result.M14 = matrix1.M14 * num;
		result.M21 = matrix1.M21 * num;
		result.M22 = matrix1.M22 * num;
		result.M23 = matrix1.M23 * num;
		result.M24 = matrix1.M24 * num;
		result.M31 = matrix1.M31 * num;
		result.M32 = matrix1.M32 * num;
		result.M33 = matrix1.M33 * num;
		result.M34 = matrix1.M34 * num;
		result.M41 = matrix1.M41 * num;
		result.M42 = matrix1.M42 * num;
		result.M43 = matrix1.M43 * num;
		result.M44 = matrix1.M44 * num;
    }

	Matrix Matrix::Negate(Matrix matrix)
	{
		Matrix result;
		Negate(matrix, result);
		return result;
	}

	void Matrix::Negate(Matrix matrix, out Matrix result)
	{
		result.M11 = -matrix.M11;
		result.M12 = -matrix.M12;
		result.M13 = -matrix.M13;
		result.M14 = -matrix.M14;
		result.M21 = -matrix.M21;
		result.M22 = -matrix.M22;
		result.M23 = -matrix.M23;
		result.M24 = -matrix.M24;
		result.M31 = -matrix.M31;
		result.M32 = -matrix.M32;
		result.M33 = -matrix.M33;
		result.M34 = -matrix.M34;
		result.M41 = -matrix.M41;
		result.M42 = -matrix.M42;
		result.M43 = -matrix.M43;
		result.M44 = -matrix.M44;
	}

	Matrix Matrix::Subtract(Matrix matrix1, Matrix matrix2)
	{
		Matrix result;
		Subtract(matrix1, matrix2, result);
		return result;
	}

	void Matrix::Subtract(Matrix matrix1, Matrix matrix2, out Matrix result)
	{
		result.M11 = matrix1.M11 - matrix2.M11;
		result.M12 = matrix1.M12 - matrix2.M12;
		result.M13 = matrix1.M13 - matrix2.M13;
		result.M14 = matrix1.M14 - matrix2.M14;
		result.M21 = matrix1.M21 - matrix2.M21;
		result.M22 = matrix1.M22 - matrix2.M22;
		result.M23 = matrix1.M23 - matrix2.M23;
		result.M24 = matrix1.M24 - matrix2.M24;
		result.M31 = matrix1.M31 - matrix2.M31;
		result.M32 = matrix1.M32 - matrix2.M32;
		result.M33 = matrix1.M33 - matrix2.M33;
		result.M34 = matrix1.M34 - matrix2.M34;
		result.M41 = matrix1.M41 - matrix2.M41;
		result.M42 = matrix1.M42 - matrix2.M42;
		result.M43 = matrix1.M43 - matrix2.M43;
		result.M44 = matrix1.M44 - matrix2.M44; 
	}

	Matrix Matrix::Transpose(Matrix matrix)
	{
		Matrix ret;
		Transpose(matrix, ret);
		return ret;  
	}

	void Matrix::Transpose(Matrix matrix, Matrix result)
	{
		result.M11 = matrix.M11;
		result.M12 = matrix.M21;
		result.M13 = matrix.M31;
		result.M14 = matrix.M41;
		result.M21 = matrix.M12;
		result.M22 = matrix.M22;
		result.M23 = matrix.M32;
		result.M24 = matrix.M42;
		result.M31 = matrix.M13;
		result.M32 = matrix.M23;
		result.M33 = matrix.M33;
		result.M34 = matrix.M43;
		result.M41 = matrix.M14;
		result.M42 = matrix.M24;
		result.M43 = matrix.M34;
		result.M44 = matrix.M44;  
	}
    
    Matrix Matrix::operator+(const Matrix other)
    {
		return Add(*this, other);
    }

	Matrix Matrix::operator /(const Matrix other)
	{
		return Divide(*this, other);
	}

	Matrix Matrix::operator /(const float divider)
	{
		return Divide(*this, divider);
	}

	bool Matrix::operator==(const Matrix other) const
	{
		return Equals(other);
	}
	
	bool Matrix::operator!=(const Matrix other) const
	{
		return !Equals(other);
	}

	Matrix Matrix::operator *(const Matrix other)
	{
		return Multiply(*this, other);
	}

	Matrix Matrix::operator *(const float scaleFactor)
	{
		return Multiply(*this, scaleFactor);
	}

	Matrix Matrix::operator -(const Matrix other)
	{
		return Subtract(*this, other);
	}

	Matrix Matrix::operator -()
	{
		return Negate(*this);
	}
}
