/**
*  Copyright 2017 Movebytes Group
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
#include <cmath>
#include "Inc\Constants.h"
#include "Inc\Camera.h"
#include "Inc\Quaternion.h"
// Default constructor
aml::Camera::Camera()
{
    m_vRight.SetCoords(1.0f, 0.0f, 0.0f);
    m_vUp.SetCoords(0.0f, 1.0f, 0.0f);
    m_vLook.SetCoords(0.0f, 0.0f, -1.0f);
    m_fFov = PI_DIV_2;
    m_fNearZ = 0.1f;
    m_fFarZ = 1000.0f;
    m_fYaw = 0.0f;
    m_fPitch = 0.0f;
    m_fRoll = 0.0f;
	m_mView = Matrix4::Identity;
	m_mProjection = Matrix4::Identity;
}
// Set camera position
void aml::Camera::SetPosition(const Vector3& vPosition)
{
    m_vPosition = vPosition;
}
// Get camera position
const aml::Vector3 aml::Camera::GetPosition() const
{
    return m_vPosition;
}
// Get view matrix
const aml::Matrix4 aml::Camera::GetViewMatrix() const
{
    return m_mView;
}
// Get projection matrix for left handed system
const aml::Matrix4 aml::Camera::GetProjectionMatrix() const
{
    return m_mProjection;
}
void aml::Camera::SetupProjection(const F32 fFov, const F32 fAspectRation, const F32 fNearZ=1.0f, const F32 fFarZ=1000.0f)
{
    m_fFov = fFov;
    m_fAr = fAspectRation;
    m_fNearZ = fNearZ;
    m_fFarZ = fFarZ;
    // Update projection matrix
    CalculateProjectionMatrix();
}
void aml::Camera::Rotate(const F32 fYaw, const F32 fPitch, const F32 fRoll)
{
    m_fYaw = fYaw;
    m_fPitch = fPitch;
    m_fRoll = fRoll;
    Update();
}
// Calculate view matrix
void aml::Camera::CalculateViewMatrix(const Vector3& vecTarget)
{
    Vector3 vecF = m_vPosition - vecTarget;
    vecF.Normalize();
    Vector3 vecS = vecF * m_vUp;
    vecS.Normalize();
    Vector3 vecU = vecS * vecF;
	m_mView = Matrix4::Identity;
    // First coll
	m_mView._11 = vecS.x;
    m_mView._21 = vecS.y;
    m_mView._31 = vecS.z;
    m_mView._41 = -(vecS.GetDotProduct(vecTarget));
    // Second coll
    m_mView._12 = vecU.x;
    m_mView._22 = vecU.y;
    m_mView._32 = vecU.z;
    m_mView._42 = -(vecU.GetDotProduct(vecTarget));
    // Third coll
    m_mView._13 = -vecF.x;
    m_mView._23 = -vecF.y;
    m_mView._33 = -vecF.z;
    m_mView._43 = vecF.GetDotProduct(vecTarget);
}
void aml::Camera::CalculateFrustumPlanes()
{
	// todo
}
void aml::Camera::SetFOV(const F32 fFov)
{
    m_fFov = fFov;
    // Update projection matrix
    CalculateProjectionMatrix();
}
const F32 aml::Camera::GetFOV() const
{
    return m_fFov;
}
void aml::Camera::SetAspectRation(const F32 fAr)
{
    m_fAr = fAr;
    // Update projection matrix
    CalculateProjectionMatrix();
}
const F32 aml::Camera::GetAspectRation() const
{
    return m_fAr;
}
aml::Frustum aml::Camera::GetViewFrustum() const
{
    return m_viewFrustum;
}