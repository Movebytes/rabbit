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
#include "Inc/SceneNode.h"
#include "Inc/Exception.h"
#include "Inc/RenderableNode.h"
// Default constructor
aml::SceneNode::SceneNode(FString strName)
{
	m_pParent = nullptr;
	m_strName = strName;
	m_Transform.BuildWorldMatrix();
}
// Restore state
HRESULT aml::SceneNode::Restore(const Scene* pScene)
{
	// Iterate over all children
	HRESULT hResult = S_OK;
	for (const auto& it : m_Children)
	{
		// Restore every child
		hResult = it->Restore(pScene);
	}
	return hResult;
}
// Update state
HRESULT aml::SceneNode::Update(const Scene* pScene, const F64 iDt)
{
	// Update world matrix
	m_Transform.BuildWorldMatrix();
	// Iterate over all children
	HRESULT hResult = S_OK;
	for (const auto& it : m_Children)
	{
		// Update every child
		hResult = it->Update(pScene, iDt);
	}
	return hResult;
}
// Render children nodes
HRESULT aml::SceneNode::RenderChildren(const Scene* pScene)
{
	HRESULT hResult = S_OK;
	// Iterate over all children
	for (const auto& it : m_Children)
	{
		// Pre render setup
		if (it->PreRender(pScene) == S_OK)
		{
			// Render only visible node
			if (it->IsVisible(pScene))
			{
				const RenderableNode& renderable = (RenderableNode&)it->GetRenderable();
				F32 fAlpha = renderable.GetMaterial().GetAlpha();
				// First render only opaque node
				if (fAlpha == OPAQUE)
				{
					hResult = renderable.Render(pScene->GetRenderer());
				}
				else if (fAlpha != TRANSPARENT)
				{
					// Collect almost transparent nodes
					AlphaNodeData* pData = new AlphaNodeData;
					AML_ASSERT(pData);
					pData->pNode = it;
					pData->mWorldMatrix = pScene->GetTopMatrix();
					// todo: 
				}
			}
			// Render children node
			hResult = it->RenderChildren(pScene);
		}
		// Post render setup
		it->PostRender(pScene);
	}
	return hResult;
}
// Add child node
bool aml::SceneNode::AddChild(shared_ptr<ISceneNode> child)
{
	m_Children.push_back(child);
	// Todo: calc bounding object
}
// Remove child node
bool aml::SceneNode::RemoveChild(FActorId id) 
{
}
// Is node visible
bool aml::SceneNode::IsVisible(const Scene* scene) const
{
}