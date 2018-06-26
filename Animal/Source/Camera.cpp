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
    m_fYaw = 0.0f;
    m_fPitch = 0.0f;
    m_fRoll = 0.0f;
	m_mView = Matrix4::Identity;
	m_mProjection = Matrix4::Identity;
}
void aml::Camera::SetupProjection(const F32 fFov, const F32 fAspectRation, const F32 fNearZ=1.0f, const F32 fFarZ=1000.0f)
{
	m_viewFrustum.SetFOV(fFov);
    m_viewFrustum.SetAspectRation(fAspectRation);
    m_viewFrustum.SetNearZ(fNearZ);
    m_viewFrustum.SetFarZ(fFarZ);
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