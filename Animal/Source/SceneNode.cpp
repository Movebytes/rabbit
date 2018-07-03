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
#include "Inc\SceneNode.h"
// Default constructor
aml::SceneNode::SceneNode(std::wstring strName,
						  ERenderPass RenderPass,
						  const FColor& Color)
{
	m_pParent = nullptr;
	m_RenderPass = RenderPass;
	m_AlphaBlendingType = AlphaBlendingTypeOpaque;
	m_Material.SetDiffuse(Color);
	// Set default params
    m_vScale.SetCoords(1.0f, 1.0f, 1.0f);
	m_vPosition.SetCoords(0.0f, 0.0f, 0.0f);
	m_vRotation.SetCoords(0.0f, 0.0f, 0.0f);
	m_strName = strName;
	// Build world matrix
    BuildWorldMatrix();
}
// Build world matrix
void aml::SceneNode::BuildWorldMatrix()
{
	Matrix4 mPosition, mRotation, mScale;
    mPosition.FromTranslation(m_vPosition);
	mRotation.FromRotationZYX(m_vRotation.z, m_vRotation.y, m_vRotation.x);
	mScale.FromScaling(m_vScale.x, m_vScale.y, m_vScale.z);
    m_mWorld = mPosition * mRotation * mScale;
}
// Restore state
HRESULT aml::SceneNode::Restore(const Scene* pScene)
{
	HRESULT hResult = S_OK;
	for (const auto& it : m_Children)
	{
		hResult = it->Restore(pScene);
	}
	return hResult;
}
// Update state
HRESULT aml::SceneNode::Update(const Scene* pScene, const F64 iDt)
{
	// Update world matrix
	BuildWorldMatrix();
	// Iterate over all children
	HRESULT hResult = S_OK;
	for (const auto& it : m_Children)
	{
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
				F32 fAlpha = it->GetMaterial().GetAlpha();
				// First render only opaque node
				if (fAlpha == OPAQUE)
				{
					hResult = it->Render(pScene);
				}
				else if (fAlpha != TRANSPARENT)
				{
					// Collect transparent nodes

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
bool aml::SceneNode::AddChild(std::shared_ptr<ISceneNode> child)
{
}
// Remove child node
bool aml::SceneNode::RemoveChild(FActorId id) 
{
}
// Is node visible
bool aml::SceneNode::IsVisible(const Scene* scene) const
{
}
HRESULT aml::SceneNode:: LostDevice(const Scene* pScene)
{
}