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
#ifndef _AML_TARGET_CAMERA_H_
#define _AML_TARGET_CAMERA_H_
#include "Camera.h"
#include "Vector3.h"
#include "Macros.h"
#include "Types.h"
namespace aml {
// Forward declarations
class Camera;
class Vector3;
// TargetCamera class declaration
class TargetCamera : public Camera
{
protected:
    Vector3 m_vTarget;
    F32 m_fMinRy;
    F32 m_fMaxRy;
    F32 m_fDistance;
    F32 m_fMinDistance;
    F32 m_fMaxDistance;
public:
    // Default constructor
    TargetCamera()
        : Camera()
        , m_fMinRy(DEG_TO_RAD(-60.0f))
        , m_fMaxRy(DEG_TO_RAD(60.0f))
        , m_fMinDistance(1.0f)
        , m_fMaxDistance(10.0f)
        , m_vTarget(0.0f, 0.0f, 10.0f)
    {}
	// Rotate camera
    void Rotate(const F32 fYaw, const F32 fPitch, const F32 fRoll) override;
	// Update camera state
    void Update() override;
	// Set target
    void SetTarget(const Vector3& vecTarget);
	// Return target
    const Vector3 GetTarget() const;
	// Move camera
    void Pan(const F32 fDx, const F32 fDy);
    void Zoom(const F32 fAmount);
    void Move(const F32 fDx, const F32 fDy);
}; // TargetCamera
} // aml
#endif // _AML_TARGET_CAMERA_H_
