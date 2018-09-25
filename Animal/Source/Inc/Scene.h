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
#include "ISceneNode.h"
#include "SceneNode.h"
#include "Matrix4.h"
namespace aml {
// Forward declarations
class ISceneNode;
class SceneNode;
class IRenderer;
class CameraNode;
class Matrix4;
// Declare type of scene nodes
typedef map<FActorId, shared_ptr<ISceneNode> > FActorNodeMap;
// Declaration of transparent node struct
struct AlphaNodeData
{
	// Pointer for a node
	shared_ptr<ISceneNode> pNode;
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
typedef list<AlphaNodeData*> FAlphaNodeList;
// Scene class declaration
class Scene
{
protected:
	shared_ptr<SceneNode> m_Root;
	shared_ptr<CameraNode> m_Camera;
	shared_ptr<IRenderer> m_Renderer;

	ID3DXMatrixStack* m_pMatrixStack;
	FAlphaNodeList m_AlphaNodeList;
	FActorNodeMap m_ActorNodeMap;

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
	// Camera acessors
	void SetCamera(shared_ptr<CameraNode> Camera);
	const shared_ptr<CameraNode> GetCamera() const;

}; // Scene
} // aml