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
#include "Inc\Vector2.h"
// Implementation
aml::Vector2::Vector2()
	: D3DXVECTOR2()
{}
aml::Vector2::Vector2(D3DXVECTOR2& Vector)
	: D3DXVECTOR2(Vector)
{}
aml::Vector2::Vector2(const F32 fX, const F32 fY)
	: D3DXVECTOR2(fX, fY)
{}
aml::Vector2::Vector2(const Vector3& Vector)
	: D3DXVECTOR2(Vector.x, Vector.y)
{}
// Calculate length
F32 aml::Vector2::GetLength() const
{
	return D3DXVec2Length(this);
}
// Calculate length square
F32 aml::Vector2::GetLengthSquare() const
{
	return D3DXVec2LengthSq(this);
}
// Normalize vector
aml::Vector2* aml::Vector2::Normalize()
{
	return static_cast<Vector2*>(D3DXVec2Normalize(this, this));
}
// Calculate dot product
F32 aml::Vector2::GetDotProduct(const Vector2& Vector) const
{
	return D3DXVec2Dot(this, &Vector);
}
// Calculate distance
F32 aml::Vector2::GetDistace(const Vector2& Vector) const
{
	const Vector2 vecResult = Vector - *this;
	return vecResult.GetLength();
}
// Linear interpolation
aml::Vector2 aml::Vector2::LERP(const Vector2& Vector, F32 fDt) const
{
	Vector2 Result;
	D3DXVec2Lerp(&Result, this, &Vector, fDt);
	return Result;
}
// Compare vectors
bool aml::Vector2::operator<=(const Vector2 & Vector) const
{
	return (operator<(Vector)) || (operator==(Vector));
}
bool aml::Vector2::operator>=(const Vector2 & Vector) const
{
	return (operator>(Vector)) || (operator==(Vector));
}
bool aml::Vector2::operator<(const Vector2 & Vector) const
{
	return (x < Vector.x && y < Vector.y);
}
bool aml::Vector2::operator>(const Vector2 & Vector) const
{
	return (x > Vector.x && y > Vector.y);
}