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
#ifndef _AML_RENDERABLE_NODE_H_
#define _AML_RENDERABLE_NODE_H_
#include <memory>
#include <list>
#include <vector>
#include "IRenderable.h"
#include "Material.h"
#include "Scene.h"
#include "Matrix4.h"
#include "Types.h"
namespace aml {
// Forward declarations
class IRenderable;
class Scene;
class Material;
class Matrix4;
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
struct AlphaNodeData
{
	// Pointer for a node
	std::shared_ptr<ISceneNode> pNode;
	// Depth position
	F32 fDepth;
	// World matrix
	Matrix4 mWorldMatrix;
	// For sorting in depth
	bool const operator<(const AlphaNodeData& Node)
	{
		return fDepth < Node.fDepth;
	}
};
// Define transparent nodes list
typedef std::list<AlphaNodeData*> FAlphaNodeList;
// Declaration of renderable representation of node
class RenderableNode : public IRenderable
{
private:
	// Render pass
	ERenderPass m_RenderPass;
	// Material of node
	Material m_Material;
	// Alpha blending type
	EAlphaBlendingType m_AlphaBlendingType;
public:
	// Default constructor
	RenderableNode(std::shared_ptr<ISceneNode> node, 
				   ERenderPass RenderPass,
				   const FColor& Color);
	// Pre render node
	virtual HRESULT PreRender(const Scene* pScene) override;
	// Render children nodes
	virtual HRESULT RenderChildren(const Scene* pScene) override;
	// Post render node
	virtual HRESULT PostRender(const Scene* pScene) override;
	// Handle losing device
	virtual HRESULT LostDevice(const Scene* pScene) override;
	// Set material
	void SetMaterial(const Material& material);
	// Access material data
	virtual const Material& GetMaterial() const override;
protected:
	virtual HRESULT Render(const Scene* pScene, std::shared_ptr<ISceneNode> node) override;
}; // RenderableNode
// Pre render node
inline HRESULT RenderableNode::PreRender(const Scene* pScene)
{
	pScene->PushMatrix(m_Node->GetTransform().GetWorldMatrix());
	return S_OK;
}
// Render node
inline HRESULT RenderableNode::Render(const Scene* pScene, std::shared_ptr<ISceneNode> node)
{
	return S_OK;
}
// Post render node
inline HRESULT RenderableNode::PostRender(const Scene* pScene)
{
	pScene->PopMatrix();
	return S_OK;
}
// Set material
inline void RenderableNode::SetMaterial(const Material& material)
{
	m_Material = material;
}
inline const Material& RenderableNode::GetMaterial() const
{
	return m_Material;
}
} // aml
#endif // _AML_RENDERABLE_NODE_H_