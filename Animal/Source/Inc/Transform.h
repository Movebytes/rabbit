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
#include "Matrix4.h"
namespace aml {
// Forward declaration
class Vector3;
class Matrix4;
// Position component declaration
class Transform
{
private:
	// Position vector
	Vector3 m_vPosition;
	// Rotation vector
	Vector3 m_vRotation;
	// Scaling vector
	Vector3 m_vScale;
	// World matrix
	Matrix4 m_mWorld;
public:
	// Default constructor
	Transform();
	// Build world matrix
	void BuildWorldMatrix();
	// Access world matrix
	const Matrix4& GetWorldMatrix() const;
	// Position accessors
	Vector3 GetPosition() const;
	void SetPosition(const Vector3& vPosition);
	// Rotation accessors
	Vector3 GetRotation() const;
	void SetRotation(const Vector3& vRotation);
	// Scale accessors
	Vector3 GetScale() const;
	void SetScale(const Vector3& vScale);
}; // PositionComponent
} // aml