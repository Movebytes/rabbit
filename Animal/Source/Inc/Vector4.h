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
#ifndef _AML_VECTOR4_H_
#define _AML_VECTOR4_H_
#include <d3dx9math.h>
#include "Types.h"
namespace aml {
// Wrapper for vector
class Vector4 : public D3DXVECTOR4
{
public:
	// Default constructor
	Vector4();
	Vector4(D3DXVECTOR4& Vector);
	Vector4(const F32 fX, const F32 fY, const F32 fZ, const F32 fW);
	// Calculate length
	F32 GetLength() const;
	// Calculate length square
	F32 GetLengthSquare() const;
	// Normalize vector
	Vector4* Normalize();
	// Calculate dot product
	F32 GetDotProduct(const Vector4& Vector) const;
	// Calculate distance
    F32 GetDistace(const Vector4& Vector) const;
	// Linear interpolation
	Vector4 LERP(const Vector4& Vector, F32 fDt) const;
	// Mull by vector and return result
    Vector4 GetCrossProduct(const Vector4& Vector1, const Vector4& Vector2) const;
	// Compare vectors
	bool operator<=(const Vector4 & Vector) const;
    bool operator>=(const Vector4 & Vector) const;
    bool operator<(const Vector4 & Vector) const;
    bool operator>(const Vector4 & Vector) const;
}; // Vector4
} // aml
#endif // _AML_VECTOR4_H_