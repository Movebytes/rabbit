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
#include "Types.h"
namespace aml {
class Vector4;
class Quaternion;
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
} // aml
#endif // _AML_VECTOR3_H_