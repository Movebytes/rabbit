#pragma once
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
#include <d3dx9math.h>
#include "Vector3.h"
#include "Matrix4.h"
namespace aml {
// Forward declarations
class Vector3;
class Matrix4;
// Quaternion wrapper declaration
class Quaternion : public D3DXQUATERNION
{
public:
	static const Quaternion Identity;
public:
	// Default constructor
	Quaternion();
	// Conversion constructor
	Quaternion(const D3DXQUATERNION& Quat);
	Quaternion(const Vector3& Vector, const F32 fAngle);
	Quaternion(const F32 fX, const F32 fY, const F32 fZ, const F32 fW);
	// Build quaternion from direction vector and angle
    void FromAxisAndAngle(const Vector3 & vAxis, F32 fAngle);
    // Build quaternion from rotation angles
    void FromRotationZYX(F32 fYaw, F32 fPitch, F32 fRoll);
	// Build quaternion from matrix
	void FromRotationMatrix(const Matrix4& Matrix);
    // Return vector
    void ToVectorAndAngle(Vector3& vOut, F32* fAngleOut) const;
    // Get magnitude of quaternion
    F32 GetLength() const;
    // Get square of length
    F32 GetLengthSquare() const;
    // Inverse the quaternion
    void Inverse();
	// Change sign of quaternion
    void Conjugate();
    // Normalize the quaternion
    void Normalize();
    // Return interpolized quaternion
    void LERP(const Quaternion& Quat, F32 fInterpolation, Quaternion & qOut) const;
    // Return interpolized quaternion
    void SLERP(const Quaternion& Quat, F32 fInterpolation, Quaternion & qOut) const;
    // Return dot product
    F32 GetDotProduct(const Quaternion & Quat) const;
}; // Quaternion
// Implementation
const Quaternion Quaternion::Identity(Quaternion(0.0f, 0.0f, 0.0f, 1.0f));
// Default constructor
inline Quaternion::Quaternion()
	: D3DXQUATERNION()
{}
inline Quaternion::Quaternion(const D3DXQUATERNION& Quat)
	: D3DXQUATERNION(Quat.x, Quat.y, Quat.z, Quat.w)
{}
inline Quaternion::Quaternion(const Vector3& Vector, const F32 fAngle)
{
	FromAxisAndAngle(Vector, fAngle);
}
inline Quaternion::Quaternion(const F32 fX, const F32 fY, const F32 fZ, const F32 fW)
	: D3DXQUATERNION(fX, fY, fZ, fW)
{}
// Build quaternion from direction vector and angle
inline void Quaternion::FromAxisAndAngle(const Vector3& vAxis, F32 fAngle)
{
	D3DXQuaternionRotationAxis(this, &vAxis, fAngle);
}
// Build quaternion from rotation angles
inline void Quaternion::FromRotationZYX(F32 fYaw, F32 fPitch, F32 fRoll)
{
	D3DXQuaternionRotationYawPitchRoll(this, fYaw, fPitch, fRoll);
}
// Build quaternion from matrix
inline void Quaternion::FromRotationMatrix(const Matrix4& Matrix)
{
	D3DXQuaternionRotationMatrix(this, &Matrix);
}
// Return vector
inline void Quaternion::ToVectorAndAngle(Vector3& vOut, F32* fAngleOut) const
{
	D3DXQuaternionToAxisAngle(this, &vOut, fAngleOut);
}
// Get magnitude of quaternion
inline F32 Quaternion::GetLength() const
{
	return D3DXQuaternionLength(this);
}
// Get square of length
inline F32 Quaternion::GetLengthSquare() const
{
	return D3DXQuaternionLengthSq(this);
}
// Inverse the quaternion
inline void Quaternion::Inverse()
{
	D3DXQuaternionInverse(this, this);
}
// Change sign of quaternion
inline void Quaternion::Conjugate()
{
	D3DXQuaternionConjugate(this, this);
}
// Normalize the quaternion
inline void Quaternion::Normalize()
{
	D3DXQuaternionNormalize(this, this);
}
// Return interpolized quaternion
inline void Quaternion::LERP(const Quaternion& Quat, F32 fInterpolation, Quaternion & qOut) const
{
	qOut = Quat;
	qOut -= *this;
	qOut *= fInterpolation;
	qOut += *this;
    qOut.Normalize();
}
// Return interpolized quaternion
inline void Quaternion::SLERP(const Quaternion& Quat, F32 fInterpolation, Quaternion & qOut) const
{
	D3DXQuaternionSlerp(&qOut, this, &Quat, fInterpolation);
}
// Return dot product
inline F32 Quaternion::GetDotProduct(const Quaternion & Quat) const
{
	return D3DXQuaternionDot(this, &Quat);
}
} // aml