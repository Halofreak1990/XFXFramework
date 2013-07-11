/*****************************************************************************
 *	Matrix.h																 *
 *																			 *
 *	XFX Matrix definition file												 *
 *	Copyright (c) XFX Team. All Rights Reserved 							 *
 *****************************************************************************/
#ifndef _XFX_MATRIX_
#define _XFX_MATRIX_

#include <System/Interfaces.h>

using namespace System;

namespace XFX
{
	struct Plane;
	struct Quaternion;
	struct Vector3;
	
	// Defines a Matrix.
	struct Matrix : IEquatable<Matrix>, Object
	{
		float M11;
		float M12;
		float M13;
		float M14;
		float M21;
		float M22;
		float M23;
		float M24;
		float M31;
		float M32;
		float M33;
		float M34;
		float M41;
		float M42;
		float M43;
		float M44;
		Vector3 Backward();
		void Backward(Vector3 vector);
		Vector3 Down();
		void Down(Vector3 vector);
		Vector3 Forward();
		void Forward(Vector3 vector);
		static const Matrix Identity;
		Vector3 Left();
		void Left(Vector3 vector);
		Vector3 Right();
		void Right(Vector3 vector);
		Vector3 Translation();
		void Translation(Vector3 vector);
		Vector3 Up();
		void Up(Vector3 vector);

		Matrix(float m11, float m12, float m13, float m14, float m21, float m22, float m23, float m24, float m31, float m32, float m33, float m34, float m41, float m42, float m43, float m44);
		Matrix(const Matrix& obj);
		Matrix();
		
		static Matrix Add(Matrix matrix1, Matrix matrix2);
		static void Add(Matrix matrix1, Matrix matrix2, out Matrix& result);
		static Matrix CreateBillboard(Vector3 objectPosition, Vector3 cameraPosition, Vector3 cameraUpVector, Vector3* cameraForwardVector);
		static void CreateBillboard(Vector3 objectPosition, Vector3 cameraPosition, Vector3 cameraUpVector, Vector3* cameraForwardVector, out Matrix& result);
		static Matrix CreateConstrainedBillboard(Vector3 objectPosition, Vector3 cameraPosition, Vector3 rotateAxis, Vector3* cameraForwardVector, Vector3* objectForwardVector);
		static void CreateConstrainedBillboard(Vector3 objectPosition, Vector3 cameraPosition, Vector3 rotateAxis, Vector3* cameraForwardVector, Vector3* objectForwardVector, out Matrix& result); 
		static Matrix CreateFromAxisAngle(Vector3 axis,  float angle);
		static void CreateFromAxisAngle(Vector3 axis, float angle, out Matrix& result);
		static Matrix CreateFromQuaternion(Quaternion rotation);
		static void CreateFromQuaternion(Quaternion rotation, out Matrix& result);
		static Matrix CreateFromYawPitchRoll(float yaw, float pitch, float roll);
		static void CreateFromYawPitchRoll(float yaw, float pitch, float roll, out Matrix& result);
		static Matrix CreateLookAt(Vector3 cameraPosition, Vector3 cameraTarget, Vector3 cameraUpVector);
		static void CreateLookAt(Vector3 cameraPosition, Vector3 cameraTarget, Vector3 cameraUpVector, out Matrix& result);
		static Matrix CreateOrthographic(float width, float height, float zNearPlane, float zFarPlane);
		static void CreateOrthographic(float width, float height, float zNearPlane, float zFarPlane, out Matrix& result);
		static Matrix CreateOrthographicOffCenter(float left, float right, float bottom, float top, float zNearPlane, float zFarPlane);
		static void CreateOrthographicOffCenter(float left, float right, float bottom, float top, float zNearPlane, float zFarPlane, out Matrix& result);
		static Matrix CreatePerspective(float width, float height, float zNearPlane, float zFarPlane);
		static void CreatePerspective(float width, float height, float zNearPlane, float zFarPlane, out Matrix& result);
		static Matrix CreatePerspectiveFieldOfView(float fieldOfView, float aspectRatio, float nearPlaneDistance, float farPlaneDistance);
		static void CreatePerspectiveFieldOfView(float fieldOfView, float aspectRatio, float nearPlaneDistance, float farPlaneDistance, out Matrix& result);
		static Matrix CreatePerspectiveOffCenter(float left, float right, float bottom, float top, float nearPlaneDistance, float farPlaneDistance);
		static void CreatePerspectiveOffCenter(float left, float right, float bottom, float top, float nearPlaneDistance, float farPlaneDistance, out Matrix& result);
		static Matrix CreateReflection(Plane value);
		static void CreateReflection(Plane value, out Matrix& result);
		static Matrix CreateRotationX(float radians);
		static void CreateRotationX(float radians, out Matrix& result);
		static Matrix CreateRotationY(float radians); 
		static void CreateRotationY(float radians, out Matrix& result);
		static Matrix CreateRotationZ(float radians);
		static void CreateRotationZ(float radians, out Matrix& result);
		static Matrix CreateScale(float scale);
		static void CreateScale(float scale, out Matrix& result);
		static Matrix CreateScale(float xScale, float yScale, float zScale);
		static void CreateScale(float xScale, float yScale, float zScale, out Matrix& result);
		static Matrix CreateScale(Vector3 scales);
		static void CreateScale(Vector3 scales, out Matrix& result);
		static Matrix CreateShadow(Vector3 lightDirection, Plane plane);
		static void CreateShadow(Vector3 lightDirection, Plane plane, out Matrix& result);
		static Matrix CreateTranslation(float xPosition, float yPosition, float zPosition);
		static void CreateTranslation(float xPosition, float yPosition, float zPosition, out Matrix& result);
		static Matrix CreateTranslation(Vector3 position);
		static void CreateTranslation(Vector3 position, out Matrix& result);
		static Matrix CreateWorld(Vector3 position, Vector3 forward, Vector3 up);
		static void CreateWorld(Vector3 position, Vector3 forward, Vector3 up, out Matrix& result);
		int Decompose(out Vector3& scale, out Quaternion& rotation, out Vector3& translation);
		float Determinant();
		static Matrix Divide(Matrix matrix1, Matrix matrix2);
		static void Divide(Matrix matrix1, Matrix matrix2, out Matrix& result);
		static Matrix Divide(Matrix matrix1, float divider);
		static void Divide(Matrix matrix1, float divider, out Matrix& result);
		bool Equals(Object const * const obj) const;
		bool Equals(const Matrix other) const;
		int GetHashCode() const;
		static int GetType();
		static Matrix Invert(Matrix matrix);
		static void Invert(Matrix matrix, out Matrix& result);
		static Matrix Lerp(Matrix value1, Matrix value2, float amount);
		static void Lerp(Matrix matrix1, Matrix matrix2, float amount, out Matrix& result);
		static Matrix Multiply(Matrix matrix1, Matrix matrix2);
		static void Multiply(Matrix matrix1, Matrix matrix2, out Matrix& result);
		static Matrix Multiply(Matrix matrix1, float scaleFactor);
		static void Multiply(Matrix matrix1, float scaleFactor, out Matrix& result);
		static Matrix Negate(Matrix matrix);
		static void Negate(Matrix matrix, out Matrix& result);
		static Matrix Subtract(Matrix matrix1, Matrix matrix2);
		static void Subtract(Matrix matrix1, Matrix matrix2, out Matrix& result);
		const String ToString() const;
		static Matrix Transform(Matrix value, Quaternion rotation);
		static void Transform(Matrix value, Quaternion rotation, out Matrix& result);
		static Matrix Transpose(Matrix matrix);
		static void Transpose(Matrix matrix, out Matrix& result);

		Matrix operator+(const Matrix& other);
		Matrix operator/(const Matrix& other);
		Matrix operator/(const float divider);
		bool operator==(const Matrix& other) const;
		bool operator!=(const Matrix& other) const;
		Matrix operator*(const Matrix& other);
		Matrix operator*(const float scaleFactor);
		Matrix operator-(const Matrix& other);
		Matrix operator-();
	} ALIGNED16;
}

#endif //_XFX_MATRIX_
