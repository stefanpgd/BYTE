#include "Graphics/UISystem.h"

#include "Graphics/UIRenderer.h"

void UISystem::Draw()
{
	for(UIRenderer* uiRenderer : uiRenderers)
	{
		if(uiRenderer->isActive)
		{
			uiRenderer->Draw();
		}
	}
}

void UISystem::AddUIRenderer(UIRenderer* ui)
{
	uiRenderers.push_back(ui);
}