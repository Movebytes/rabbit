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
    Vector3 m_vPosition;
    // Rotation vector
    Vector3 m_vRotation;
    // Scaling vector
    Vector3 m_vScale;
    // World matrix
    Matrix4 m_mWorld;
    // Build world matrix
    virtual void BuildWorldMatrix();
public:
	// Default constructor
	SceneNode(std::wstring strName,
			  ERenderPass RenderPass,
			  const FColor& Color);
	// Default destructor
	virtual ~SceneNode() override;
	// Restore state
	virtual HRESULT Restore(const Scene* pScene) override;
	// Update state
	virtual HRESULT Update(const Scene* pScene, const F64 iDt) override;
	// Pre render node
	virtual HRESULT PreRender(const Scene* pScene) override;
	// Render node
	virtual HRESULT Render(const Scene* pScene) override;
	// Render children nodes
	virtual HRESULT RenderChildren(const Scene* pScene) override;
	// Post render node
	virtual HRESULT PostRender(const Scene* pScene) override;
	// Add child node
	virtual bool AddChild(std::shared_ptr<ISceneNode> child) override;
	// Remove child node
	virtual bool RemoveChild(FActorId id) override;
	// Is node visible
	virtual bool IsVisible(const Scene* scene) const override;
	// Handle losing device
	virtual HRESULT LostDevice(const Scene* pScene) override;
	// Set and Get alpha
	void SetAlpha(const F32 fAlpha);
	F32 GetAlpha() const;
	// Get and Set position
	Vector3 GetPosition() const;
	void SetPosition(const Vector3& vPosition);
	// Get and Set rotation
	Vector3 GetRotation() const;
	void SetRotation(const Vector3& vRotation);
	// Get and Set scale
	Vector3 GetScale() const;
	void SetScale(const Vector3& vScale);
	// Set material
	void SetMaterial(const Material& material);
	virtual const Material& GetMaterial() const override;
}; // SceneNode
// Pre render node
inline HRESULT SceneNode::PreRender(const Scene* pScene)
{
	pScene->PushMatrix(m_mWorld);
	return S_OK;
}
// Render node
inline HRESULT SceneNode::Render(const Scene* pScene)
{
	return S_OK;
}
// Post render node
inline HRESULT SceneNode::PostRender(const Scene* pScene)
{
	pScene->PopMatrix();
	return S_OK;
}
// Set and Get alpha
inline void SceneNode::SetAlpha(const F32 fAlpha)
{
	m_Material.SetAlpha(fAlpha);
}
inline F32 SceneNode::GetAlpha() const
{
	return m_Material.GetAlpha();
}
// Get and Set position
inline Vector3 SceneNode::GetPosition() const
{
	return m_vPosition;
}
inline void SceneNode::SetPosition(const Vector3& vPosition)
{
	m_vPosition = vPosition;
}
// Get and Set rotation
inline Vector3 SceneNode::GetRotation() const
{
	return m_vRotation;
}
inline void SceneNode::SetRotation(const Vector3& vRotation)
{
	m_vRotation = vRotation;
}
// Get and Set scale
inline Vector3 SceneNode::GetScale() const
{
	return m_vScale;
}
inline void SceneNode::SetScale(const Vector3& vScale)
{
	m_vScale = vScale;
}
// Set material
inline void SceneNode::SetMaterial(const Material& material)
{
	m_Material = material;
}
inline const Material& SceneNode::GetMaterial() const
{
	return m_Material;
}
} // aml
#endif // _AML_SCENE_NODE_H_