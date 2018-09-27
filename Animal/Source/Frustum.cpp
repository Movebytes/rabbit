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
#include "Inc/AnimalStd.h"
#include <cmath>
#include "Inc/Frustum.h"
 // Default constructor
aml::Frustum::Frustum()
{
	m_fNearZ = 0.1f;
	m_fFarZ = 1000.0f;
	m_fFov = PI_DIV_2;
	m_fAr = 1.0f;
}
// Get plane of frustum
const aml::Plane& aml::Frustum::GetPlane(EFrustumSide Side) const
{
	return m_arrPlanes[Side];
}
// Accessors of field of view
void aml::Frustum::SetFOV(const F32 fFOV)
{
	m_fFov = fFOV;
	// You have to recalculate planes manualy
}
F32 aml::Frustum::GetFOV() const
{
	return m_fFov;
}
// Accessors of aspect ratio
void aml::Frustum::SetAspectRation(const F32 fAr)
{
	m_fAr = fAr;
	// You have to recalculate planes manualy
}
F32 aml::Frustum::GetAspectRation() const
{
	return m_fAr;
}
// Accessors of near z
void aml::Frustum::SetNearZ(const F32 fNearZ)
{
	m_fNearZ = fNearZ;
	// You have to recalculate planes manualy
}
F32 aml::Frustum::GetNearZ() const
{
	return m_fNearZ;
}
// Accessors of far z
void aml::Frustum::SetFarZ(const F32 fFarZ)
{
	m_fFarZ = fFarZ;
	// You have to recalculate planes manualy
}
F32 aml::Frustum::GetFarZ() const
{
	return m_fFarZ;
}
// Check is Point inside Frustum
bool aml::Frustum::Contains(const Vector3& vPoint) const
{
    for (U32 i = 0; i < FrustumSideNumPlanes; i++)
    {
        if (m_arrPlanes[i].GetDistance(vPoint) < 0.0f)
        {
            return false;
        }
    }
    return true;
}
// Check is Shpere inside Frustum
bool aml::Frustum::Contains(const Vector3& vCenter, const F32 fRadius) const
{
    for (U32 i = 0; i < FrustumSideNumPlanes; i++)
    {
        F32 fDistance = m_arrPlanes[i].GetDistance(vCenter);
        if (fDistance < -fRadius)
        {
            return false;
        }
    }
    return true;
}
// Check is Box inside
bool aml::Frustum::Contains(const Vector3& vMin, const Vector3& vMax) const
{
    for (U32 i = 0; i < FrustumSideNumPlanes; i++)
    {
        Vector3 vP = vMin;
        Vector3 vN = vMax;
        Vector3 vNormal = m_arrPlanes[i].m_vNormal;
        if (vNormal.x >= 0.0f)
        {
            vP.x = vMax.x;
            vN.x = vMin.x;
        }
        if (vNormal.y >= 0.0f)
        {
            vP.y = vMax.y;
            vN.y = vMin.y;
        }
        if (vNormal.z >= 0.0f)
        {
            vP.z = vMax.z;
            vN.z = vMin.z;
        }
        if (m_arrPlanes[i].GetDistance(vP) < 0.0f)
        {
            return false;
        }
    }
    return true;
}
// Calculate all planes
void aml::Frustum::CalculatePlanes(const Vector3& vRight, const Vector3& vUp, const Vector3& vLook)
{
	// Calculate plane vectors
	F64 fTanFovDiv2 = tan(m_fFov / 2.0f);
	Vector3 vNearRight = (m_fNearZ * fTanFovDiv2) * m_fAr * vRight;
	Vector3 vFarRight = (m_fFarZ * fTanFovDiv2) * m_fAr * vRight;
	Vector3 vNearUp = (m_fNearZ * fTanFovDiv2) * vUp;
	Vector3 vFarUp = (m_fFarZ * fTanFovDiv2) * vUp;
	// Calculate near plane points
	const Vector3 vNear = m_fNearZ * vLook;
	m_arrNearPoints[0] = vNear - vNearRight + vNearUp;
	m_arrNearPoints[1] = vNear + vNearRight + vNearUp;
	m_arrNearPoints[2] = vNear + vNearRight - vNearUp;
	m_arrNearPoints[3] = vNear - vNearRight - vNearUp;
	// Calculate far plane points
	const Vector3 vFar = m_fFarZ * vLook;
	m_arrFarPoints[0] = vFar - vFarRight + vFarUp;
	m_arrFarPoints[1] = vFar + vFarRight + vFarUp;
	m_arrFarPoints[2] = vFar + vFarRight - vFarUp;
	m_arrFarPoints[3] = vFar - vFarRight - vFarUp;
	// Construct all planes
	const Vector3 vOrigin(0.0f, 0.0f, 0.0f);
	m_arrPlanes[FrustumSideNear] = Plane(m_arrNearPoints[2], m_arrNearPoints[1], m_arrNearPoints[0]);
	m_arrPlanes[FrustumSideFar] = Plane(m_arrFarPoints[0], m_arrFarPoints[1], m_arrFarPoints[2]);
	m_arrPlanes[FrustumSideRight] = Plane(m_arrFarPoints[2], m_arrFarPoints[1], vOrigin);
	m_arrPlanes[FrustumSideTop] = Plane(m_arrFarPoints[1], m_arrFarPoints[0], vOrigin);
	m_arrPlanes[FrustumSideLeft] = Plane(m_arrFarPoints[0], m_arrFarPoints[3], vOrigin);
	m_arrPlanes[FrustumSideBottom] = Plane(m_arrFarPoints[3], m_arrFarPoints[2], vOrigin);
}
	