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
#include "Transform.h"
#include "ISceneNode.h"
#include "Scene.h"
#include "Types.h"
namespace aml {
// Forward declarations
class Vector3;
class Matrix4;
class Transform;
class ISceneNode;
class Scene;
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
	// World transform
	Transform m_Transform;
public:
	// Default constructor
	SceneNode(std::wstring strName);
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
	// Access children
	virtual const FSceneNodeList& GetChildren() const override;
	// Is node visible
	virtual bool IsVisible(const Scene* scene) const override;
	// Get transform data
	virtual const Transform& GetTransform() const override;
}; // SceneNode
// Get transform component
const Transform& SceneNode::GetTransform() const
{
	return m_Transform;
} // GetTransform
const FSceneNodeList& SceneNode::GetChildren() const
{

}
} // aml
#endif // _AML_SCENE_NODE_H_