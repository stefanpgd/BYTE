#pragma once
#include <vector>
#include "../Engine/Transform.h"

class UIRenderer;

class UISystem
{
public:
	void Draw();

	static void AddUIRenderer(UIRenderer* ui);

private:
	static inline std::vector<UIRenderer*> uiRenderers;
};