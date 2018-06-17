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
#include "Inc\Vector3.h"
// Implementation
aml::Vector3::Vector3()
	: D3DXVECTOR3()
{}
aml::Vector3::Vector3(D3DXVECTOR3& Vector)
	: D3DXVECTOR3(Vector)
{}
aml::Vector3::Vector3(const F32 fX, const F32 fY, const F32 fZ)
	: D3DXVECTOR3(fX, fY, fZ)
{}
aml::Vector3::Vector3(const Vector4& Vector)
	: D3DXVECTOR3(Vector.x, Vector.y, Vector.z)
{}
// Calculate length
F32 aml::Vector3::GetLength() const
{
	return D3DXVec3Length(this);
}
// Calculate length square
F32 aml::Vector3::GetLengthSquare() const
{
	return D3DXVec3LengthSq(this);
}
// Normalize vector
aml::Vector3* aml::Vector3::Normalize()
{
	return static_cast<Vector3*>(D3DXVec3Normalize(this, this));
}
// Calculate dot product
F32 aml::Vector3::GetDotProduct(const Vector3& Vector) const
{
	return D3DXVec3Dot(this, &Vector);
}
// Calculate distance
F32 aml::Vector3::GetDistace(const Vector3& Vector) const
{
	const Vector3 vecResult = Vector - *this;
	return vecResult.GetLength();
}
// Rotate vector by quaternion
void aml::Vector3::Rotate(const Quaternion& Quat);
// Linear interpolation
aml::Vector3 aml::Vector3::LERP(const Vector3& Vector, F32 fDt) const
{
	Vector3 Result;
	D3DXVec3Lerp(&Result, this, &Vector, fDt);
	return Result;
}
// Mull by vector and return result
aml::Vector3 aml::Vector3::operator*(const Vector3& Vector) const
{
	Vector3 Result;
	D3DXVec3Cross(&Result, this, &Vector);
	return Result;
}
// Mull by vector and assign result
aml::Vector3& aml::Vector3::operator*=(const Vector3& Vector)
{
	D3DXVec3Cross(this, this, &Vector);
	return *this;
}
// Compare vectors
bool aml::Vector3::operator<=(const Vector3 & Vector) const
{
	return (operator<(Vector)) || (operator==(Vector));
}
bool aml::Vector3::operator>=(const Vector3 & Vector) const
{
	return (operator>(Vector)) || (operator==(Vector));
}
bool aml::Vector3::operator<(const Vector3 & Vector) const
{
	return (x < Vector.x && y < Vector.y && z < Vector.z);
}
bool aml::Vector3::operator>(const Vector3 & Vector) const
{
	return (x > Vector.x && y > Vector.y && z > Vector.z);
}