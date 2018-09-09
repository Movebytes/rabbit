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
#include <list>
#include <memory>
#include <string>
#include "Vector3.h"
#include "Matrix4.h"
#include "Material.h"
#include "Transform.h"
#include "ISceneNode.h"
#include "Scene.h"
#include "Types.h"
namespace aml {
// Forward declarations
class Vector3;
class Matrix4;
class Material;
class Transform;
class ISceneNode;
class Scene;
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
// Declaration of transparent node struct
struct AlphaSceneNode
{
	// Pointer for a node
	std::shared_ptr<ISceneNode> pNode;
	// Depth position
	F32 fDepth;
	// World matrix
	Matrix4 mWorldMatrix;
	// For sorting in depth
	bool const operator<(const AlphaSceneNode& Node)
	{
		return fDepth < Node.fDepth;
	}
};
// Define transparent nodes list
typedef std::list<AlphaSceneNode*> FAlphaSceneNodeList;
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
	// World transform
	Transform m_Transform;
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
	// Get transform data
	const Transform& GetTransform() const;
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
// Get transform component
const Transformt& SceneNode::GetTransform() const
{
	return m_Transform;
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