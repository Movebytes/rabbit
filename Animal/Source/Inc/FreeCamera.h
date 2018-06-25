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
#ifndef _AML_FREE_CAMERA_H_
#define _AML_FREE_CAMERA_H_
#include "Camera.h"
#include "Vector3.h"
#include "Types.h"
namespace aml {
// Forward declarations
class Camera;
class Vector3;
// FreeCamera class declaration
class FreeCamera : public Camera
{
protected:
    // Move speed of camera
    F32 m_fSpeed;
    Vector3 m_vTranslation;
public:
    // Default constructor
    FreeCamera()
        : Camera()
        , m_fSpeed(0.5f)
        , m_vTranslation(0.0f, 0.0f, 0.0f)
    {}
    void Update() override;
    void Walk(const F32 fDt);
    void Strafe(const F32 fDt);
    void Lift(const F32 fDt);
    void SetTranslation(const Vector3 & vTranslation);
    Vector3 GetTranslation() const;
    void SetSpeed(const F32 fSpeed);
    const F32 GetSpeed() const;
}; // FreeCamera
} // aml
#endif // _AML_FREE_CAMERA_H_
