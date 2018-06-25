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
#ifndef _AML_CAMERA_H_
#define _AML_CAMERA_H_
#include <d3dx9math.h>
#include "Vector3.h"
#include "Matrix4.h"
#include "Frustum.h"
#include "Types.h"
namespace aml {
// Forward declarations
class Vector3;
class Matrix4;
class Frustum;
// Camera class declaration
class Camera
{
protected:
    // Position of a camera
    Vector3 m_vPosition;
    // Basis (x, y, z)
    Vector3 m_vRight; // u
    Vector3 m_vUp;    // v
    Vector3 m_vLook;  // n
    // Rotations
    F32 m_fYaw;
    F32 m_fPitch;
    F32 m_fRoll;
    // Near z of cut of view space
    F32 m_fNearZ;
    // Far z of cut of view space
    F32 m_fFarZ;
    // Field of view angle
    F32 m_fFov;
    // Viewport width / Viewport height
    F32 m_fAr;
    // Matrices
    Matrix4 m_mView;
	Matrix4 m_mProjection;
    // View frustum
    Frustum m_viewFrustum;
public:
    // Default constructor
	Camera();
    void SetupProjection(const F32 fFov, const F32 fAspectRation, const F32 fNearZ, const F32 fFarZ);
    virtual void Update() = 0;
    virtual void Rotate(const F32 fYaw, const F32 fPitch, const F32 fRoll);
    const Matrix4 GetViewMatrix() const;
	const Matrix4 GetProjectionMatrix() const;
    void SetPosition(const Vector3 & vecPosition);
    const Vector3 GetPosition() const;
    void SetFOV(const F32 fFov);
    const F32 GetFOV() const;
    void SetAspectRation(const F32 fAr);
    const F32 GetAspectRation() const;
    Frustum GetViewFrustum() const;
protected:
    void CalculateViewMatrix(const Vector3 & vecTarget);
    void CalculateProjectionMatrix();
    void CalculateFrustumPlanes();
}; // Camera
// Calculate projection matrix
inline void Camera::CalculateProjectionMatrix()
{
	D3DXMatrixPerspectiveFovRH(&m_mProjection, m_fFov, m_fAr, m_fNearZ, m_fFarZ);
}
} // aml
#endif // _AML_CAMERA_H_
