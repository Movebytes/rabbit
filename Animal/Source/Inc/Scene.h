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
#ifndef _AML_SCENE_H_
#define _AML_SCENE_H_
#include <map>
#include "ISceneNode.h"
#include "SceneNode.h"
#include "Types.h"
namespace aml {
// Forward declarations
class ISceneNode;
class SceneNode;
class IRenderer;
// Declare type of scene nodes
typedef std::map<U32, std::shared_ptr<ISceneNode> > FSceneNodeMap;
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
// Scene class declaration
class Scene
{
protected:
	std::shared_ptr<SceneNode> m_Root;
	// TODO: std::shared_ptr<CameraNode> m_Camera;
	std::shared_ptr<IRenderer> m_Renderer;

	ID3DXMatrixStack* m_pMatrixStack;
	FAlphaNodeList m_AlphaNodeList;
	FSceneNodeMap m_NodeMap;

	// TODO: LightManager* m_pLightManager;
	void RenderAlphaNodes();
public:
	// Default constructor
	Scene();
	// Default destructor
	virtual ~Scene();
	// Render scene
	HRESULT Render();
	// Restore scene
	HRESULT Restore();
	// Handle loosing device
	HRESULT LostDevice();
	// Update scene state
	HRESULT Update(const U64 iDt);

}; // Scene
} // aml
#endif // _AML_SCENE_H_