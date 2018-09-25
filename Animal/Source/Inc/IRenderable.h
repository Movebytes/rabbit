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
#include "Material.h"
namespace aml {
// Forward declarations
class ISceneNode;
class IRenderer;
class Material;
// Declare renderable class
class IRenderable
{
protected:
	// Node of which is renderable representation
	shared_ptr<ISceneNode> m_Node;
public:
	// Default constructor
	explicit IRenderable(shared_ptr<ISceneNode> node);
	// Default destructor
	virtual ~IRenderable();
	// Render node
	virtual HRESULT Render(const IRenderer* pRenderer) final
	{
		return Render(pRenderer, m_Node);
	}
	// Get material
	virtual const Material& GetMaterial() const = 0;
protected:
	virtual HRESULT Render(const IRenderer* pScene, shared_ptr<ISceneNode> node) = 0;
}; // IRenderable
inline IRenderable::~IRenderable()
{
} // ~IRenderable
// Default constructor
inline IRenderable::IRenderable(shared_ptr<ISceneNode> node)
{
	m_Node = node;
} // IRenderable
} // aml