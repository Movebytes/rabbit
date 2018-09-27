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
#include "Vector3.h"
#include "Constants.h"
#include "Plane.h"
namespace aml {
// Forward declarations
class Plane;
class Vector3;
// Frustum class declaration
class Frustum
{
public:
	enum EFrustumSide 
	{
		FrustumSideNear = 0,
		FrustumSideFar,
		FrustumSideTop, 
		FrustumSideRight,
		FrustumSideBottom,
		FrustumSideLeft,
		FrustumSideNumPlanes
	};
private:
    // Frustum planes
    Plane m_arrPlanes[FrustumSideNumPlanes];
    // Frustum points
    Vector3 m_arrFarPoints[4];
    Vector3 m_arrNearPoints[4];
	// Near z of cut of view space
    F32 m_fNearZ;
    // Far z of cut of view space
    F32 m_fFarZ;
    // Field of view angle
    F32 m_fFov;
    // Viewport width / Viewport height
    F32 m_fAr;
public:
	// Default constructor
	Frustum();
	// Calculate all planes
	void CalculatePlanes(const Vector3& vRight, const Vector3& vUp, const Vector3& vLook);
	// Check is Point inside Frustum
    bool Contains(const Vector3& vPoint) const;
	// Check is Shpere inside Frustum
    bool Contains(const Vector3& vCenter, const F32 fRadius) const;
	// Check is Box inside
    bool Contains(const Vector3& vMin, const Vector3& vMax) const;
	// Get plane of frustum
	const Plane& GetPlane(EFrustumSide Side) const;
	// Accessors of field of view
	void SetFOV(const F32 fFOV);
	F32 GetFOV() const;
	// Accessors of aspect ratio
	void SetAspectRation(const F32 fAr);
	F32 GetAspectRation() const;
	// Accessors of near z
	void SetNearZ(const F32 fNearZ);
	F32 GetNearZ() const;
	// Accessors of far z
	void SetFarZ(const F32 fNearZ);
	F32 GetFarZ() const;
}; // Frustum
} // aml
