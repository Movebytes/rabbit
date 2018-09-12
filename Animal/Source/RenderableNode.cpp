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
#include "Inc/RenderableNode.h"
// Render children nodes
HRESULT aml::RenderableNode::RenderChildren(const Scene* pScene)
{
	HRESULT hResult = S_OK;
	auto children = m_Node->GetChildren();
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
					// Collect almost transparent nodes
					AlphaSceneNode* pAlphaNode = new AlphaSceneNode;
					AML_ASSERT(pAlphaNode);
					pAlphaNode->pNode = it;
					pAlphaNode->mWorldMatrix = pScene->GetTopMatrix();
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