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
#include "Inc\Vector4.h"
// Implementation
aml::Vector4::Vector4()
	: D3DXVECTOR4()
{}
aml::Vector4::Vector4(D3DXVECTOR4& Vector)
	: D3DXVECTOR4(Vector)
{}
aml::Vector4::Vector4(const F32 fX, const F32 fY, const F32 fZ, const F32 fW)
	: D3DXVECTOR4(fX, fY, fZ, fW)
{}
// Calculate length
F32 aml::Vector4::GetLength() const
{
	return D3DXVec4Length(this);
}
// Calculate length square
F32 aml::Vector4::GetLengthSquare() const
{
	return D3DXVec4LengthSq(this);
}
// Normalize vector
aml::Vector4* aml::Vector4::Normalize()
{
	return static_cast<Vector4*>(D3DXVec4Normalize(this, this));
}
// Calculate dot product
F32 aml::Vector4::GetDotProduct(const Vector4& Vector) const
{
	return D3DXVec4Dot(this, &Vector);
}
// Calculate distance
F32 aml::Vector4::GetDistace(const Vector4& Vector) const
{
	const Vector4 vecResult = Vector - *this;
	return vecResult.GetLength();
}
// Linear interpolation
aml::Vector4 aml::Vector4::LERP(const Vector4& Vector, F32 fDt) const
{
	Vector4 Result;
	D3DXVec4Lerp(&Result, this, &Vector, fDt);
	return Result;
}
// Mull by vector and return result
aml::Vector4 aml::Vector4::GetCrossProduct(const Vector4& Vector1, const Vector4& Vector2) const
{
	Vector4 Result;
	D3DXVec4Cross(&Result, this, &Vector1, &Vector2);
	return Result;
}
// Compare vectors
bool aml::Vector4::operator<=(const Vector4 & Vector) const
{
	return (operator<(Vector)) || (operator==(Vector));
}
bool aml::Vector4::operator>=(const Vector4 & Vector) const
{
	return (operator>(Vector)) || (operator==(Vector));
}
bool aml::Vector4::operator<(const Vector4 & Vector) const
{
	return (x < Vector.x && y < Vector.y && z < Vector.z && w < Vector.w);
}
bool aml::Vector4::operator>(const Vector4 & Vector) const
{
	return (x > Vector.x && y > Vector.y && z > Vector.z && w > Vector.w);
}