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
#include "Inc\FreeCamera.h"
#include "Inc\Quaternion.h"
void aml::FreeCamera::Update()
{
    // Update camera position
    m_vPosition += m_vTranslation;
    // Calc rotation
    Quaternion qYaw(Vector3(0.0f, 0.0f, 1.0f), m_fYaw); // z
    Quaternion qPitch(Vector3(0.0f, 1.0f, 0.0f), m_fPitch); // y
    Quaternion qRoll(Vector3(1.0f, 0.0f, 0.0f), m_fRoll); // z
    Quaternion qRot = qYaw * qPitch * qRoll;
    // Update basis
    m_vLook.SetCoords(0.0f, 0.0f, 1.0f);
    m_vLook.Rotate(qRot);
    m_vUp.SetCoords(0.0f, 1.0f, 0.0f);
    m_vUp.Rotate(qRot);
    m_vRight = m_vLook * m_vUp;
    // Calculate target point
    Vector3 vTarget = m_vPosition + m_vLook;
    // Update view matrix
    CalculateViewMatrix(vTarget);
    // Update frustum
	m_viewFrustum.CalculatePlanes(m_vRight, m_vUp, m_vLook);
    m_vTranslation.SetCoords(0.0f, 0.0f, 0.0f);
}
void aml::FreeCamera::Walk(const F32 fDt)
{
    m_vTranslation += ((D3DXVECTOR3)m_vLook * m_fSpeed * fDt);
}
void aml::FreeCamera::Strafe(const F32 fDt)
{
    m_vTranslation += ((D3DXVECTOR3)m_vRight * m_fSpeed * fDt);
}
void aml::FreeCamera::Lift(const F32 fDt)
{
    m_vTranslation += ((D3DXVECTOR3)m_vUp * m_fSpeed * fDt);
}
void aml::FreeCamera::SetTranslation(const Vector3& vTranslation)
{
    m_vTranslation = vTranslation;
}
aml::Vector3 aml::FreeCamera::GetTranslation() const
{
    return m_vTranslation;
}
void aml::FreeCamera::SetSpeed(const F32 fSpeed)
{
    m_fSpeed = fSpeed;
}
const F32 aml::FreeCamera::GetSpeed() const
{
    return m_fSpeed;
}