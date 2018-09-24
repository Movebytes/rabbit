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
#include "Vector3.h"
#include "Matrix4.h"
#include "Transform.h"
#include "ISceneNode.h"
#include "IRenderable.h"
#include "RenderableNode.h"
#include "Scene.h"
#include "Types.h"
namespace aml {
// Forward declarations
class Vector3;
class Matrix4;
class Transform;
class ISceneNode;
class IRenderable;
class Scene;
// Declaration of SceneNode
class SceneNode : public ISceneNode
{
protected:
	// Entity name
    wstring m_strName;
	// Child nodes
	FSceneNodeList m_Children;
	// Parent node
	SceneNode* m_pParent;
	// World transform
	Transform m_Transform;
	// Renderable
	RenderableNode m_Renderable;
public:
	// Default constructor
	SceneNode(wstring strName);
	// Default destructor
	virtual ~SceneNode() override;
	// Restore state
	virtual HRESULT Restore(const Scene* pScene) override;
	// Update state
	virtual HRESULT Update(const Scene* pScene, const F64 iDt) override;
	// Add child node
	virtual bool AddChild(std::shared_ptr<ISceneNode> child) override;
	// Remove child node
	virtual bool RemoveChild(FActorId id) override;
	// Pre render node
	virtual HRESULT PreRender(const Scene* pScene) override;
	// Render children nodes
	virtual HRESULT RenderChildren(const Scene* pScene) override;
	// Post render node
	virtual HRESULT PostRender(const Scene* pScene) override;
	// Handle losing device
	virtual HRESULT LostDevice(const Scene* pScene) override;
	// Is node visible
	virtual bool IsVisible(const Scene* scene) const override;
	// Get renderable representation of node
	virtual const IRenderable& GetRenderable() const = 0;
	// Get transform data
	virtual const Transform& GetTransform() const override;
}; // SceneNode
// Get transform component
inline const Transform& SceneNode::GetTransform() const
{
	return m_Transform;
} // GetTransform
  // Pre render node
inline HRESULT SceneNode::PreRender(const Scene* pScene)
{
	pScene->PushMatrix(m_Transform.GetWorldMatrix());
	return S_OK;
}
// Post render node
inline HRESULT SceneNode::PostRender(const Scene* pScene)
{
	pScene->PopMatrix();
	return S_OK;
}
// Get renderable representation of node
inline const IRenderable& SceneNode::GetRenderable() const
{
	return m_Renderable;
} // GetRenderable
} // aml
#endif // _AML_SCENE_NODE_H_