/**
 *  Copyright 2018 Movebytes Group
 *
 *  Licensed under the Apache License, Version 2.0 (the "License");
 *  you may not use this file except in compliance with the License.
 *  You may obtain a copy of the License at
 *
 *      http://www.apache.org/licenses/LICENSE-2.0
 *
 *  Unless required by applicable law or agreed to in writing, software
 *  distributed under the License is distributed on an "AS IS" BASIS,
 *  WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 *  See the License for the specific language governing permissions and
 *  limitations under the License.
 */
#ifndef _AML_MATRIX4_H_
#define _AML_MATRIX4_H_
#include <d3dx9math.h>
#include "Vector3.h"
#include "Vector4.h"
#include "Types.h"
namespace aml {
// Forward declarations
class Vector3;
class Vector4;
class Quaternion;
// Matrix wrapper declaration
class Matrix4 : public D3DXMATRIX 
{
public:
	// Matrix Identity
	static const Matrix4 Identity;
public:
	// Default constructors
	Matrix4();
	// Conversion constructor
	Matrix4(const D3DXMATRIX& mMatrix);
	Matrix4(F32 a11, F32 a12, F32 a13, F32 a14,
		    F32 a21, F32 a22, F32 a23, F32 a24,
			F32 a31, F32 a32, F32 a33, F32 a34,
			F32 a41, F32 a42, F32 a43, F32 a44);
	// Transpose matrix
    void Transpose();
	// Inverse matrix
	void Inverse();
	// Fill the matrix by zero
    void Null();
	// Return determinant of the matrix
    F32 GetDeterminant() const;
	// Build translation matrix from 3d vector
	void FromTranslation(const Vector3& vPosition);
	// Build translation matrix from 4d vector
	void FromTranslation(const Vector4& vPosition);
	// Build rotation matrix over X axis
	void FromRotationX(const F32 fAngle);
	// Build rotation matrix over Y axis
	void FromRotationY(const F32 fAngle);
	// Build rotation matrix over Z axis
	void FromRotationZ(const F32 fAngle);
	// Build rotation matrix over ZYX axisses
	void FromRotationZYX(const F32 fYaw, const F32 fPitch, const F32 fRoll);
	// Build rotation matrix from Quaternion
	void FromQuaternion(const Quaternion& Quat);
	// Build matrix from position|target|up vectors
	void FromLookAt(const Vector3& vPosition, const Vector3& vTarget, const Vector3& vUp);
	// Build matrix from axis and angle rotation data
    void FromAxisAndAngle(const Vector3& vAxis, const F32 fAngle);
	// Build scaling matrix
    void FromScaling(const F32 fScaleX, const F32 fScaleY, const F32 fScaleZ);
}; // Matrix4
// Implementation
const Matrix4 Matrix4::Identity(Matrix4(1.0f, 0.0f, 0.0f, 0.0f,
										0.0f, 1.0f, 0.0f, 0.0f,
										0.0f, 0.0f, 1.0f, 0.0f,
										0.0f, 0.0f, 0.0f, 1.0f));
// Default constructors
inline Matrix4::Matrix4()
	: D3DXMATRIX()
{}
inline Matrix4::Matrix4(const D3DXMATRIX& mMatrix)
	: D3DXMATRIX(mMatrix)
{}
inline Matrix4::Matrix4(F32 a11, F32 a12, F32 a13, F32 a14,
						F32 a21, F32 a22, F32 a23, F32 a24,
						F32 a31, F32 a32, F32 a33, F32 a34,
						F32 a41, F32 a42, F32 a43, F32 a44)
	: D3DXMATRIX(a11, a12, a13, a14,
				 a21, a22, a23, a24,
				 a31, a32, a33, a34,
				 a41, a42, a43, a44)
{}
// Transpose matrix
inline void Matrix4::Transpose()
{
	D3DXMatrixTranspose(this, this);
}
// Inverse matrix
inline void Matrix4::Inverse()
{
	D3DXMatrixInverse(this, NULL, this);
}
// Fill the matrix by zero
inline void Matrix4::Null()
{
	ZeroMemory(&m, sizeof(m));
}
// Return determinant of the matrix
inline F32 Matrix4::GetDeterminant() const
{
	return D3DXMatrixDeterminant(this);
}
// Build translation matrix from 3d vector
inline void Matrix4::FromTranslation(const Vector3& vPosition)
{
	D3DXMatrixTranslation(this, vPosition.x, vPosition.y, vPosition.z);
}
// Build translation matrix from 4d vector
inline void Matrix4::FromTranslation(const Vector4& vPosition)
{
	D3DXMatrixTranslation(this, vPosition.x, vPosition.y, vPosition.z);
}
// Build rotation matrix over X axis
inline void Matrix4::FromRotationX(const F32 fAngle)
{
	D3DXMatrixRotationX(this, fAngle);
}
// Build rotation matrix over Y axis
inline void Matrix4::FromRotationY(const F32 fAngle)
{
	D3DXMatrixRotationY(this, fAngle);
}
// Build rotation matrix over Z axis
inline void Matrix4::FromRotationZ(const F32 fAngle)
{
	D3DXMatrixRotationZ(this, fAngle);
}
// Build rotation matrix over ZYX axisses
inline void Matrix4::FromRotationZYX(const F32 fYaw, const F32 fPitch, const F32 fRoll)
{
	D3DXMatrixRotationYawPitchRoll(this, fYaw, fPitch, fRoll);
}
// Build rotation matrix from Quaternion
inline void Matrix4::FromQuaternion(const Quaternion& Quat)
{
	D3DXMatrixRotationQuaternion(this, &Quat);
}
// Build matrix from position|target|up vectors
inline void Matrix4::FromLookAt(const Vector3& vPosition, const Vector3& vTarget, const Vector3& vUp)
{
	D3DXMatrixLookAtRH(this, &vPosition, &vTarget, &vUp);
}
// Build matrix from axis and angle rotation data
inline void Matrix4::FromAxisAndAngle(const Vector3& vAxis, const F32 fAngle)
{
	D3DXMatrixRotationAxis(this, &vAxis, fAngle);
}
// Build scaling matrix
inline void Matrix4::FromScaling(const F32 fScaleX, const F32 fScaleY, const F32 fScaleZ)
{
	D3DXMatrixScaling(this, fScaleX, fScaleY, fScaleZ);
}
} // aml
#endif // _AML_MATRIX4_H_