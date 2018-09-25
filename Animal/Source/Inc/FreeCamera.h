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
#include "Camera.h"
#include "Vector3.h"
namespace aml {
// Forward declarations
class Camera;
class Vector3;
// FreeCamera class declaration
class FreeCamera : public Camera
{
protected:
    // Move speed of camera
    F32 m_fSpeed;
    Vector3 m_vTranslation;
public:
    // Default constructor
    FreeCamera();
	// Update camera state
    void Update() override;
	// Move camera
    void Walk(const F32 fDt);
    void Strafe(const F32 fDt);
    void Lift(const F32 fDt);
	// Set distance for translation
    void SetTranslation(const Vector3 & vTranslation);
    Vector3 GetTranslation() const;
	// Set speed of translation
    void SetSpeed(const F32 fSpeed);
    const F32 GetSpeed() const;
}; // FreeCamera
// Default constructor
inline FreeCamera::FreeCamera()
	: Camera()
{
	m_fSpeed = 0.5f;
    m_vTranslation.SetCoords(0.0f, 0.0f, 0.0f);
}
// Move camera
inline void FreeCamera::Walk(const F32 fDt)
{
    m_vTranslation += ((D3DXVECTOR3)m_vLook * m_fSpeed * fDt);
}
inline void FreeCamera::Strafe(const F32 fDt)
{
    m_vTranslation += ((D3DXVECTOR3)m_vRight * m_fSpeed * fDt);
}
inline void FreeCamera::Lift(const F32 fDt)
{
    m_vTranslation += ((D3DXVECTOR3)m_vUp * m_fSpeed * fDt);
}
// Set distance for translation
inline void FreeCamera::SetTranslation(const Vector3& vTranslation)
{
    m_vTranslation = vTranslation;
}
inline Vector3 FreeCamera::GetTranslation() const
{
    return m_vTranslation;
}
// Set speed of translation
inline void FreeCamera::SetSpeed(const F32 fSpeed)
{
    m_fSpeed = fSpeed;
}
inline const F32 FreeCamera::GetSpeed() const
{
    return m_fSpeed;
}
} // aml
