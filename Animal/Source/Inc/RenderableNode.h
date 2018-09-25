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
#include "IRenderable.h"
#include "Material.h"
#include "Scene.h"
#include "Matrix4.h"
namespace aml {
// Forward declarations
class IRenderable;
class IRenderer;
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
	RenderableNode(shared_ptr<ISceneNode> node, 
				   ERenderPass RenderPass,
				   const FColor& Color);
	// Set material
	void SetMaterial(const Material& material);
	// Access material data
	virtual const Material& GetMaterial() const override;
protected:
	virtual HRESULT Render(const IRenderer* pRenderer, shared_ptr<ISceneNode> node) override;
}; // RenderableNode
// Render node
inline HRESULT RenderableNode::Render(const IRenderer* pRenderer, shared_ptr<ISceneNode> node)
{
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