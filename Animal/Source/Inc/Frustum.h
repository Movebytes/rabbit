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
#ifndef _AML_FRUSTUM_H_
#define _AML_FRUSTUM_H_
#include "Vector3.h"
#include "Plane.h"
#include "Types.h"
namespace aml {
// Forward declarations
class Plane;
class Vector3;
// Frustum class declaration
class Frustum
{
public:
	enum FrustumSide 
	{
		Near = 0,
		Far,
		Top, 
		Right,
		Bottom,
		Left,
		NumPlanes
	};
public:
    // Frustum planes
    Plane m_arrPlanes[NumPlanes];
    // Frustum points
    Vector3 m_arrFarPoints[4];
    Vector3 m_arrNearPoints[4];
public:
	// Get plane of frustum
	const Plane& GetPlane(FrustumSide Side) const;
	// Check is Point inside Frustum
    bool Contains(const Vector3& vPoint);
	// Check is Shpere inside Frustum
    bool Contains(const Vector3& vCenter, const F32 fRadius);
	// Check is Box inside
    bool Contains(const Vector3& vMin, const Vector3& vMax);
}; // Frustum
} // aml
#endif // _AML_FRUSTUM_H_
