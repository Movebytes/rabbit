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
#ifndef _AML_PLANE_H_
#define _AML_PLANE_H_
#include <d3dx9math.h>
#include "Vector3.h"
#include "Constants.h"
#include "Types.h"
namespace aml {
// Forward declarations
class Vector3;
// Position relative to plane
enum PlanePosition
{
    PLANE_POS_COPLANAR,
    PLANE_POS_FRONT,
    PLANE_POS_BACK
};
// Plane class declaration
class Plane : public D3DXPLANE
{
public:
    // Default constructor
	Plane();
	// Conversion constructor
	Plane(const D3DXPLANE& Plane);
	Plane(const Vector3& vA, const Vector3& vB, const Vector3& vC);
	// Normalize plane
	void Normalize();
	// Get distance to plane
	F32 GetDistance(const Vector3& vPoint) const;
	// Check point position regarding the plane
	PlanePosition Classify(const Vector3& vPoint) const;
	// Check sphere position regarding the plane
	PlanePosition Classify(const Vector3& vPoint, const F32 fRadius) const;
}; // Plane
// Default constructor
inline Plane::Plane()
	: D3DXPLANE()
{}
// Conversion constructor
inline Plane::Plane(const D3DXPLANE& Plane)
	: D3DXPLANE(Plane.a, Plane.b, Plane.c, Plane.d)
{}
inline Plane::Plane(const Vector3& vA, const Vector3& vB, const Vector3& vC)
	: D3DXPLANE()
{
	D3DXPlaneFromPoints(this, &vA, &vB, &vC);
	Normalize();
}
// Normalize plane
inline void Plane::Normalize()
{
	D3DXPlaneNormalize(this, this);
}
// Get distance to plane
inline F32 Plane::GetDistance(const Vector3& vPoint) const
{
	return D3DXPlaneDotCoord(this, &vPoint);
}
// Check point position regarding the plane
inline PlanePosition Plane::Classify(const Vector3& vPoint) const
{
	F32 fDistance = GetDistance(vPoint);
    if (fDistance > EPSILON_E4)
    {
        return PLANE_POS_FRONT;
    }
    else if (fDistance < EPSILON_E4)
    {
        return PLANE_POS_BACK;
    }
    else
    {
        return PLANE_POS_COPLANAR;
    }
}
// Check sphere position regarding the plane
inline PlanePosition Plane::Classify(const Vector3& vPoint, const F32 fRadius) const
{
	F32 fDistance = GetDistance(vPoint);
	if (fDistance >= -fRadius)
    {
        return PLANE_POS_FRONT;
    }
    else if (fDistance < -fRadius)
    {
        return PLANE_POS_BACK;
    }
    else
    {
        return PLANE_POS_COPLANAR;
    }
}
} // aml
#endif // _AML_PLANE_H_
