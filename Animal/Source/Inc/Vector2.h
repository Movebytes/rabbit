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
#include "Vector3.h"
namespace aml {
// Forward declarations
class Vector3;
// Wrapper for vector
class Vector2 : public D3DXVECTOR2
{
public:
	// Default constructor
	Vector2();
	Vector2(D3DXVECTOR2& Vector);
	Vector2(const F32 fX, const F32 fY);
	Vector2(const Vector3& Vector);
	// Calculate length
	F32 GetLength() const;
	// Calculate length square
	F32 GetLengthSquare() const;
	// Normalize vector
	Vector2* Normalize();
	// Calculate dot product
	F32 GetDotProduct(const Vector2& Vector) const;
	// Calculate distance
    F32 GetDistace(const Vector2& Vector) const;
	// Linear interpolation
	Vector2 LERP(const Vector2& Vector, F32 fDt) const;
	// Compare vectors
	bool operator<=(const Vector2 & Vector) const;
    bool operator>=(const Vector2 & Vector) const;
    bool operator<(const Vector2 & Vector) const;
    bool operator>(const Vector2 & Vector) const;
}; // Vector2
} // aml
#endif // _AML_VECTOR2_H_