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
#include "Vector3.h"
#include "Matrix4.h"
namespace aml {
// Forward declaration
class Vector3;
class Matrix4;
// Position component declaration
class Transform
{
private:
	// Position vector
	Vector3 m_vPosition;
	// Rotation vector
	Vector3 m_vRotation;
	// Scaling vector
	Vector3 m_vScale;
	// World matrix
	Matrix4 m_mWorld;
public:
	// Default constructor
	Transform();
	// Build world matrix
	void BuildWorldMatrix();
	// Access world matrix
	const Matrix4& GetWorldMatrix() const;
	// Position accessors
	Vector3 GetPosition() const;
	void SetPosition(const Vector3& vPosition);
	// Rotation accessors
	Vector3 GetRotation() const;
	void SetRotation(const Vector3& vRotation);
	// Scale accessors
	Vector3 GetScale() const;
	void SetScale(const Vector3& vScale);
}; // PositionComponent
// Implementation
Transform::Transform()
{
	// Set default params
	m_vScale.SetCoords(1.0f, 1.0f, 1.0f);
	m_vPosition.SetCoords(0.0f, 0.0f, 0.0f);
	m_vRotation.SetCoords(0.0f, 0.0f, 0.0f);
	// Build world matrix
	BuildWorldMatrix();
}
inline void Transform::BuildWorldMatrix()
{
	Matrix4 mPosition, mRotation, mScale;
	// Build translation matrix
	mPosition.FromTranslation(m_vPosition);
	// Build rotation matrix
	mRotation.FromRotationZYX(m_vRotation.z, m_vRotation.y, m_vRotation.x);
	// Build scale matrix
	mScale.FromScaling(m_vScale.x, m_vScale.y, m_vScale.z);
	// Combine matrices
	m_mWorld = mPosition * mRotation * mScale;
}
// Access world matrix
const Matrix4& Transform::GetWorldMatrix() const
{
	return m_mWorld;
}
// Get and Set position
inline Vector3 Transform::GetPosition() const
{
	return m_vPosition;
}
inline void Transform::SetPosition(const Vector3& vPosition)
{
	m_vPosition = vPosition;
}
// Get and Set rotation
inline Vector3 Transform::GetRotation() const
{
	return m_vRotation;
}
inline void Transform::SetRotation(const Vector3& vRotation)
{
	m_vRotation = vRotation;
}
// Get and Set scale
inline Vector3 Transform::GetScale() const
{
	return m_vScale;
}
inline void Transform::SetScale(const Vector3& vScale)
{
	m_vScale = vScale;
}
} // aml