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
#ifndef _AML_VECTOR2_H_
#define _AML_VECTOR2_H_
#include <d3dx9math.h>
#include "Types.h"
#include "Matrix4.h"
#include "Vector3.h"
namespace aml {
// Forward declarations
class Vector3;
class Matrix4;
// Wrapper for vector
class Vector2 : public D3DXVECTOR2
{
public:
	// Default constructor
	Vector2();
	// Conversion constructor
	Vector2(const D3DXVECTOR2& Vector);
	Vector2(const F32 fX, const F32 fY);
	Vector2(const Vector3& Vector);
	// Accessors
	void SetCoords(const F32 fX, const F32 fY);
	// Calculate length
	F32 GetLength() const;
	// Calculate length square
	F32 GetLengthSquare() const;
	// Normalize vector
	void Normalize();
	// Negate vector
    void Conjugate();
	// Calculate dot product
	F32 GetDotProduct(const Vector2& Vector) const;
	// Calculate distance
    F32 GetDistace(const Vector2& Vector) const;
	// Linear interpolation
	Vector2 LERP(const Vector2& Vector, F32 fDt) const;
	// Assign vector
    Vector2& operator=(const Vector2& Vector);
    // Mull by matrix 4x4 and return result
    Vector2 operator*(const Matrix4& Matrix) const;
    // Mull by matrix 4x4 and assign result
    Vector2& operator*=(const Matrix4& Matrix);
	// Compare vectors
    bool operator==(const Vector2& Vector) const;
    bool operator!=(const Vector2& Vector) const;
	bool operator<=(const Vector2& Vector) const;
    bool operator>=(const Vector2& Vector) const;
    bool operator<(const Vector2& Vector) const;
    bool operator>(const Vector2& Vector) const;
}; // Vector2
// Implementation
inline Vector2::Vector2()
	: D3DXVECTOR2()
{}
inline Vector2::Vector2(const D3DXVECTOR2& Vector)
	: D3DXVECTOR2(Vector)
{}
inline Vector2::Vector2(const F32 fX, const F32 fY)
	: D3DXVECTOR2(fX, fY)
{}
inline Vector2::Vector2(const Vector3& Vector)
	: D3DXVECTOR2(Vector.x, Vector.y)
{}
// Accessors
inline void Vector2::SetCoords(const F32 fX, const F32 fY)
{
	x = fX;
	y = fY;
}
// Calculate length
inline F32 Vector2::GetLength() const
{
	return D3DXVec2Length(this);
}
// Calculate length square
inline F32 aml::Vector2::GetLengthSquare() const
{
	return D3DXVec2LengthSq(this);
}
// Normalize vector
inline void Vector2::Normalize()
{
	D3DXVec2Normalize(this, this);
}
// Negate vector
inline void Vector2::Conjugate()
{
	x = -x;
	y = -y;
}
// Calculate dot product
inline F32 Vector2::GetDotProduct(const Vector2& Vector) const
{
	return D3DXVec2Dot(this, &Vector);
}
// Calculate distance
inline F32 Vector2::GetDistace(const Vector2& Vector) const
{
	const Vector2 vecResult = Vector - *this;
	return vecResult.GetLength();
}
// Linear interpolation
inline Vector2 Vector2::LERP(const Vector2& Vector, F32 fDt) const
{
	Vector2 Result;
	D3DXVec2Lerp(&Result, this, &Vector, fDt);
	return Result;
}
// Assign vector
Vector2& Vector2::operator=(const Vector2& Vector)
{
	x = Vector.x;
	y = Vector.y;
	return *this;
}
// Mull by matrix 4x4 and return result
inline Vector2 Vector2::operator*(const Matrix4& Matrix) const
{
	Vector2 vResult;
	D3DXVec2TransformCoord(&vResult, this, &Matrix);
	return vResult;
}
// Mull by matrix 4x4 and assign result
inline Vector2& Vector2::operator*=(const Matrix4& Matrix)
{
	D3DXVec2TransformCoord(this, this, &Matrix);
	return *this;
}
inline bool Vector2::operator<=(const Vector2 & Vector) const
{
	return (operator<(Vector)) || (operator==(Vector));
}
inline bool Vector2::operator>=(const Vector2 & Vector) const
{
	return (operator>(Vector)) || (operator==(Vector));
}
inline bool Vector2::operator<(const Vector2 & Vector) const
{
	return (x < Vector.x && y < Vector.y);
}
inline bool Vector2::operator>(const Vector2 & Vector) const
{
	return (x > Vector.x && y > Vector.y);
}
} // aml
#endif // _AML_VECTOR2_H_