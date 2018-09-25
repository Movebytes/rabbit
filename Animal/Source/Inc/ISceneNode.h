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
#include "Scene.h"
#include "Matrix4.h"
#include "Transform.h"
#include "IRenderable.h"
namespace aml {
// Forward declarations
class Scene;
class Matrix4;
class Transform;
class ISceneNode;
class IRenderable;
// Define scene node list
typedef vector<shared_ptr<ISceneNode> > FSceneNodeList;
// Declaration of SceneNode class
class ISceneNode
{
public:
	// Default destructor
	virtual ~ISceneNode();
	// Update state
	virtual HRESULT Update(const Scene* pScene, const F64 iDt) = 0;
	// Restore state
	virtual HRESULT Restore(const Scene* pScene) = 0;
	// Add child node
	virtual bool AddChild(shared_ptr<ISceneNode> child) = 0;
	// Remove child node
	virtual bool RemoveChild(FActorId id) = 0;
	// Pre render node
	virtual HRESULT PreRender(const Scene* pScene) = 0;
	// Render children nodes
	virtual HRESULT RenderChildren(const Scene* pScene) = 0;
	// Post render node
	virtual HRESULT PostRender(const Scene* pScene) = 0;
	// Handle losing device
	virtual HRESULT LostDevice(const Scene* pScene) = 0;
	// Get renderable representation of node
	virtual const IRenderable& GetRenderable() const = 0;
	// Is node visible
	virtual bool IsVisible(const Scene* scene) const = 0;
	// Get transform data
	virtual const Transform& GetTransform() const = 0;
}; // ISceneNode
// Default destructor
inline ISceneNode::~ISceneNode()
{}
} // aml