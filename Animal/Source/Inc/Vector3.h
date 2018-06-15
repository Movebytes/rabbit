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
#ifndef _AML_VECTOR3_H_
#define _AML_VECTOR3_H_
#include <d3dx9math.h>
#include "Macros.h"
#include "Types.h"
namespace {
// Forward declarations
class Vector4;
class Quaternion;
// Wrapper for vector
class Vector3 : public D3DXVECTOR3
{
public:
	// Default constructor
	Vector3();
	Vector3(D3DXVECTOR3& Vector);
	Vector3(const F32 fX, const F32 fY, const F32 fZ);
	Vector3(const Vector4& Vector);
	// Calculate length
	F32 GetLength() const;
	// Calculate length square
	F32 GetLengthSquare() const;
	// Normalize vector
	Vector3* Normalize();
	// Calculate dot product
	F32 GetDotProduct(const Vector3& Vector) const;
	// Calculate distance
    F32 GetDistace(const Vector3& Vector) const;
	// Rotate vector by quaternion
    void Rotate(const Quaternion& Quat);
	// Mull by vector and return result
    Vector3 operator*(const Vector3& Vector) const;
	// Mull by vector and assign result
    Vector3& operator*=(const Vector3& Vector);
	// Compare vectors
	bool operator<=(const Vector3 & Vector) const;
    bool operator>=(const Vector3 & Vector) const;
    bool operator<(const Vector3 & Vector) const;
    bool operator>(const Vector3 & Vector) const;
}; // Vector3
// Implementation
inline Vector3::Vector3()
	: D3DXVECTOR3()
{}
inline Vector3::Vector3(D3DXVECTOR3& Vector)
	: D3DXVECTOR3(Vector)
{}
inline Vector3::Vector3(const F32 fX, const F32 fY, const F32 fZ)
	: D3DXVECTOR3(fX, fY, fZ)
{}
inline Vector3::Vector3(const Vector4& Vector)
	: D3DXVECTOR3(Vector.x, Vector.y, Vector.z)
{}
// Calculate length
inline F32 Vector3::GetLength() const
{
	return D3DXVec3Length(this);
}
// Calculate length square
inline F32 Vector3::GetLengthSquare() const
{
	return D3DXVec3LengthSq(this);
}
// Normalize vector
inline Vector3* Vector3::Normalize()
{
	return static_cast<Vector3*>(D3DXVec3Normalize(this, this));
}
// Calculate dot product
inline F32 Vector3::GetDotProduct(const Vector3& Vector) const
{
	return D3DXVec3Dot(this, &Vector);
}
// Calculate distance
inline F32 Vector3::GetDistace(const Vector3& Vector) const
{
	const Vector3 vecResult = Vector - *this;
	return vecResult.GetLength();
}
// Rotate vector by quaternion
inline void Vector3::Rotate(const Quaternion& Quat);
// Mull by vector and return result
inline Vector3 Vector3::operator*(const Vector3& Vector) const
{
	Vector3 Result;
	D3DXVec3Cross(&Result, this, &Vector);
	return Result;
}
// Mull by vector and assign result
inline Vector3& Vector3::operator*=(const Vector3& Vector)
{
	D3DXVec3Cross(this, this, &Vector);
	return *this;
}
// Compare vectors
inline bool Vector3::operator<=(const Vector3 & Vector) const
{
	return (operator<(Vector)) || (operator==(Vector));
}
inline bool Vector3::operator>=(const Vector3 & Vector) const
{
	return (operator>(Vector)) || (operator==(Vector));
}
inline bool Vector3::operator<(const Vector3 & Vector) const
{
	return (x < Vector.x && y < Vector.y && z < Vector.z);
}
inline bool Vector3::operator>(const Vector3 & Vector) const
{
	return (x > Vector.x && y > Vector.y && z > Vector.z);
}
} // aml
#endif // _AML_VECTOR3_H_