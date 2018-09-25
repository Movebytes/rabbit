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
#include "Matrix4.h"
namespace aml {
// Forward declarations
class Matrix4;
// Wrapper for vector
class Vector4 : public D3DXVECTOR4
{
public:
	// Default constructor
	Vector4();
	// Conversion constructor
	Vector4(const D3DXVECTOR4& Vector);
	Vector4(const F32 fX, const F32 fY, const F32 fZ, const F32 fW);
	// Accessors
	void SetCoords(const F32 fX, const F32 fY, const F32 fZ, const F32 fW);
	// Calculate length
	F32 GetLength() const;
	// Calculate length square
	F32 GetLengthSquare() const;
	// Normalize vector
	void Normalize();
	// Negate vector
    void Conjugate();
	// Calculate dot product
	F32 GetDotProduct(const Vector4& Vector) const;
	// Calculate distance
    F32 GetDistace(const Vector4& Vector) const;
	// Linear interpolation
	Vector4 LERP(const Vector4& Vector, F32 fDt) const;
	// Mull by vector and return result
    Vector4 GetCrossProduct(const Vector4& Vector1, const Vector4& Vector2) const;
	// Assign vector
    Vector4& operator=(const Vector4& Vector);
	// Mull by matrix 4x4 and return result
    Vector4 operator*(const Matrix4& Matrix) const;
	// Mull by matrix 4x4 and assign result
    Vector4& operator*=(const Matrix4& matrix);
	// Compare vectors
	bool operator<=(const Vector4& Vector) const;
    bool operator>=(const Vector4& Vector) const;
    bool operator<(const Vector4& Vector) const;
    bool operator>(const Vector4& Vector) const;
}; // Vector4
// Implementation
inline Vector4::Vector4()
	: D3DXVECTOR4()
{}
inline Vector4::Vector4(const D3DXVECTOR4& Vector)
	: D3DXVECTOR4(Vector)
{}
inline Vector4::Vector4(const F32 fX, const F32 fY, const F32 fZ, const F32 fW)
	: D3DXVECTOR4(fX, fY, fZ, fW)
{}
// Accessors
inline void Vector4::SetCoords(const F32 fX, const F32 fY, const F32 fZ, const F32 fW)
{
	x = fX;
	y = fY;
	z = fZ;
	w = fW;
}
// Calculate length
inline F32 Vector4::GetLength() const
{
	return D3DXVec4Length(this);
}
// Calculate length square
inline F32 Vector4::GetLengthSquare() const
{
	return D3DXVec4LengthSq(this);
}
// Normalize vector
inline void Vector4::Normalize()
{
	D3DXVec4Normalize(this, this);
}
// Negate vector
inline void Vector4::Conjugate()
{
	x = -x;
	y = -y;
	z = -z;
	w = -w;
}
// Calculate dot product
inline F32 Vector4::GetDotProduct(const Vector4& Vector) const
{
	return D3DXVec4Dot(this, &Vector);
}
// Calculate distance
inline F32 Vector4::GetDistace(const Vector4& Vector) const
{
	const Vector4 vecResult = Vector - *this;
	return vecResult.GetLength();
}
// Linear interpolation
inline Vector4 Vector4::LERP(const Vector4& Vector, F32 fDt) const
{
	Vector4 Result;
	D3DXVec4Lerp(&Result, this, &Vector, fDt);
	return Result;
}
// Mull by vector and return result
inline Vector4 Vector4::GetCrossProduct(const Vector4& Vector1, const Vector4& Vector2) const
{
	Vector4 Result;
	D3DXVec4Cross(&Result, this, &Vector1, &Vector2);
	return Result;
}
// Assign vector
Vector4& Vector4::operator=(const Vector4& Vector)
{
	x = Vector.x;
	y = Vector.y;
	z = Vector.z;
	w = Vector.w;
	return *this;
}
// Mull by matrix 4x4 and return result
Vector4 Vector4::operator*(const Matrix4& Matrix) const
{
	Vector4 vResult;
	D3DXVec4Transform(vResult, this, &Matrix);
	return vResult;
}
// Mull by matrix 4x4 and assign result
Vector4& Vector4::operator*=(const Matrix4& matrix)
{
	D3DXVec4Transform(this, this, &Matrix);
	return *this;
}
// Compare vectors
inline bool Vector4::operator<=(const Vector4 & Vector) const
{
	return (operator<(Vector)) || (operator==(Vector));
}
inline bool Vector4::operator>=(const Vector4 & Vector) const
{
	return (operator>(Vector)) || (operator==(Vector));
}
inline bool Vector4::operator<(const Vector4 & Vector) const
{
	return (x < Vector.x && y < Vector.y && z < Vector.z && w < Vector.w);
}
inline bool Vector4::operator>(const Vector4 & Vector) const
{
	return (x > Vector.x && y > Vector.y && z > Vector.z && w > Vector.w);
}
} // aml