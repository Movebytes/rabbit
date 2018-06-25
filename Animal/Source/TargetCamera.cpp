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
#include "Inc\TargetCamera.h"
#include "Inc\Quaternion.h"
void aml::TargetCamera::Update()
{
    // Calculate rotation
    Quaternion qYaw(Vector3(0.0f, 0.0f, 1.0f), m_fYaw); // z
    Quaternion qPitch(Vector3(0.0f, 1.0f, 0.0f), m_fPitch); // y
    Quaternion qRoll(Vector3(1.0f, 0.0f, 0.0f), m_fRoll); // z
    Quaternion qRot = qYaw * qPitch * qRoll;
    // Translation
    Vector3 vTranslation(0.0f, 0.0f, m_fDistance);
    vTranslation.Rotate(qRot);
    m_vPosition = m_vTarget + vTranslation;
    // Update basis
    m_vLook = m_vTarget - m_vPosition;
    m_vLook.Normalize();
    m_vUp.SetCoords(0.0f, 1.0f, 0.0f);
    m_vUp.Rotate(qRot);
    m_vRight = m_vLook * m_vUp;
    // Update view matrix
    CalculateViewMatrix(m_vTarget);
    // Update frustum
    CalculateFrustumPlanes();
}
void aml::TargetCamera::SetTarget(const Vector3& vTarget)
{
    m_vTarget = vTarget;
    m_fDistance = m_vPosition.GetDistace(vTarget);
    m_fDistance = MAX(m_fMinDistance, MIN(m_fDistance, m_fMaxDistance));
}
const aml::Vector3 aml::TargetCamera::GetTarget() const
{
    return m_vTarget;
}
void aml::TargetCamera::Rotate(const F32 fYaw, const F32 fPitch, const F32 fRoll)
{
    F32 fCorrectPitch = MIN(MAX(fPitch, m_fMinRy), m_fMaxRy);
    Camera::Rotate(fYaw, fCorrectPitch, fRoll);
}
void aml::TargetCamera::Pan(const F32 fDx, const F32 fDy)
{
	Vector3 vecX = (D3DXVECTOR3)m_vRight * fDx;
    Vector3 vecY = (D3DXVECTOR3)m_vUp * fDy;
    m_vPosition += vecX + vecY;
    m_vTarget += vecX + vecY;
}
void aml::TargetCamera::Zoom(const F32 fAmount)
{
    m_vPosition += (D3DXVECTOR3)m_vLook * fAmount;
    m_fDistance = m_vPosition.GetDistace(m_vTarget);
    m_fDistance = MAX(m_fMinDistance, MIN(m_fDistance, m_fMaxDistance));
}
void aml::TargetCamera::Move(const F32 fDx, const F32 fDy)
{
    Vector3 vecX = (D3DXVECTOR3)m_vRight * fDx;
    Vector3 vecY = (D3DXVECTOR3)m_vLook * fDy;
    m_vPosition += vecX + vecY;
    m_vTarget += vecX + vecY;
}