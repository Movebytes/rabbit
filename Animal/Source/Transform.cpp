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
#include "Inc/Transform.h"
// Implementation
aml::Transform::Transform()
{
	// Set default params
	m_vScale.SetCoords(1.0f, 1.0f, 1.0f);
	m_vPosition.SetCoords(0.0f, 0.0f, 0.0f);
	m_vRotation.SetCoords(0.0f, 0.0f, 0.0f);
	// Build world matrix
	BuildWorldMatrix();
}
void aml::Transform::BuildWorldMatrix()
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
const aml::Matrix4& aml::Transform::GetWorldMatrix() const
{
	return m_mWorld;
}
// Get and Set position
aml::Vector3 aml::Transform::GetPosition() const
{
	return m_vPosition;
}
void aml::Transform::SetPosition(const Vector3& vPosition)
{
	m_vPosition = vPosition;
}
// Get and Set rotation
aml::Vector3 aml::Transform::GetRotation() const
{
	return m_vRotation;
}
void aml::Transform::SetRotation(const Vector3& vRotation)
{
	m_vRotation = vRotation;
}
// Get and Set scale
aml::Vector3 aml::Transform::GetScale() const
{
	return m_vScale;
}
void aml::Transform::SetScale(const Vector3& vScale)
{
	m_vScale = vScale;
}