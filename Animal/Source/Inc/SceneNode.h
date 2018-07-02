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
#ifndef _AML_SCENE_NODE_H_
#define _AML_SCENE_NODE_H_
#include <vector>
#include <memory>
#include <string>
#include "Vector3.h"
#include "Matrix4.h"
#include "Material.h"
#include "ISceneNode.h"
#include "Types.h"
namespace aml {
// Forward declarations
class Vector3;
class Matrix4;
class Material;
class ISceneNode;
// Define scene node list
typedef std::vector<std::shared_ptr<ISceneNode> > FSceneNodeList;
// Define render pass
enum ERenderPass
{
	RenderPass0,						// Starting pass
	RenderPassStatic = RenderPass0,		// Static geometry
	RenderPassActor,					// Moveable objects
	RenderPassSky,						// Background
	RenderPassNotRendered,				// Not rendered objects
	RenderPassLast						// Last pass
};
// Define alpha blending type
enum EAlphaBlendingType
{
	AlphaBlendingTypeOpaque,
	AlphaBlendingTypeTexture,
	AlphaBlendingTypeMaterial,
	AlphaBlendingTypeVertex
};
// Declaration of SceneNode
class SceneNode : public ISceneNode
{
protected:
	// Entity name
    std::wstring m_strName;
	// Child nodes
	FSceneNodeList m_Children;
	// Parent node
	SceneNode* m_pParent;
	// Render pass
	ERenderPass m_RenderPass;
	// Material of node
	Material m_Material;
	// Alpha blending type
	EAlphaBlendingType m_AlphaBlendingType;
	// Position vector
    Vector3 m_vecPosition;
    // Rotation vector
    Vector3 m_vecRotation;
    // Scaling vector
    Vector3 m_vecScale;
    // World matrix
    Matrix4 m_matWorld;
    // Build world matrix
    virtual void BuildWorldMatrix();
public:
	// Default constructor
	SceneNode();
	// Default destructor
	~SceneNode() override;
	// Restore state
	HRESULT Restore(const Scene* pScene) override;
	// Pre render node
	HRESULT PreRender(const Scene* pScene) override;
	// Render node
	HRESULT Render(const Scene* pScene) override;
	// Render children nodes
	HRESULT RenderChildren(const Scene* pScene) override;
	// Post render node
	HRESULT PostRender(const Scene* pScene) override;
	// Add child node
	bool AddChild(std::shared_ptr<ISceneNode> child) override;
	// Remove child node
	bool RemoveChild(FActorId id) override;
	// Is node visible
	bool IsVisible(const Scene* scene) const override;
	// Set and Get alpha
	void SetAlpha(const F32 fAlpha);
	F32 GetAlpha() const;
	// Get and Set position
	Vector3 GetPosition() const;
	void SetPosition(const Vector3& vPosition);
	// Set radius
	void SetRadius(const F32 fRadius);
	// Set material
	void SetMaterial(const Material& material);
}; // SceneNode

} // aml
#endif // _AML_SCENE_NODE_H_