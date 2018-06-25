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
#include "Inc\Frustum.h"
// Check is Point inside Frustum
bool aml::Frustum::IsPointInside(const Vector3& vPoint)
{
    for (U32 i = 0; i < 6; i++)
    {
        if (m_arrPlanes[i].GetDistance(vPoint) < 0.0f)
        {
            return false;
        }
    }
    return true;
}
// Check is Shpere inside Frustum
bool aml::Frustum::IsSphereInside(const Vector3& vCenter, const F32 fRadius)
{
    for (U32 i = 0; i < 6; i++)
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
bool aml::Frustum::IsBoxInside(const Vector3& vMin, const Vector3& vMax)
{
    for (U32 i = 0; i < 6; i++)
    {
        Vector3 vP = vMin;
        Vector3 vN = vMax;
        Vector3 vNormal = m_arrPlanes[i].m_vecNormal;
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