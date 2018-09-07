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
#ifndef _AML_POSITION_COMPONENT_H_
#define _AML_POSITION_COMPONENT_H_
#include "IComponent.h"
#include "Vector3.h"
#include "Matrix4.h"
#include "Types.h"
namespace aml {
// Forward declaration
class IComponent;
class Vector3;
class Matrix4;
// Position component declaration
class TransformComponent : public IComponent
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
	virtual HRESULT Init() final;
	virtual HRESULT Update(const F64 iDt) final;
	virtual HRESULT Release() final;
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
inline HRESULT TransformComponent::Init()
{
	// Set default params
	m_vScale.SetCoords(1.0f, 1.0f, 1.0f);
	m_vPosition.SetCoords(0.0f, 0.0f, 0.0f);
	m_vRotation.SetCoords(0.0f, 0.0f, 0.0f);
	// Build world matrix
	return Update(0);
}
inline HRESULT TransformComponent::Update(const F64 iDt)
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
	// Everything is OK :)
	return S_OK;
}
inline HRESULT TransformComponent::Release()
{
	return S_OK;
}
// Get and Set position
inline Vector3 TransformComponent::GetPosition() const
{
	return m_vPosition;
}
inline void TransformComponent::SetPosition(const Vector3& vPosition)
{
	m_vPosition = vPosition;
}
// Get and Set rotation
inline Vector3 TransformComponent::GetRotation() const
{
	return m_vRotation;
}
inline void TransformComponent::SetRotation(const Vector3& vRotation)
{
	m_vRotation = vRotation;
}
// Get and Set scale
inline Vector3 TransformComponent::GetScale() const
{
	return m_vScale;
}
inline void TransformComponent::SetScale(const Vector3& vScale)
{
	m_vScale = vScale;
}
} // aml
#endif // _AML_POSITION_COMPONENT_H_