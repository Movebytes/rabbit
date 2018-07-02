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
	FSceneNodeList::iterator i = m_Children.begin();
	FSceneNodeList::iterator end = m_Children.end();
	while (i != end)
	{
		(*i)->Restore(pScene);
		++i;
	}
	return S_OK;
}
// Update state
HRESULT aml::SceneNode::Update(const Scene* pScene, const F64 iDt)
{
	// Update world matrix
	BuildWorldMatrix();
	// Iterate over children
	FSceneNodeList::iterator i = m_Children.begin();
	FSceneNodeList::iterator end = m_Children.end();
	while (i != end)
	{
		(*i)->Update(pScene, iDt);
		++i;
	}
	return S_OK;
}
// Render children nodes
HRESULT RenderChildren(const Scene* pScene) override;
// Add child node
bool AddChild(std::shared_ptr<ISceneNode> child) override;
// Remove child node
bool RemoveChild(FActorId id) override;
// Is node visible
bool IsVisible(const Scene* scene) const override;