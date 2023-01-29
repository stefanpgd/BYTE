#include "GameObject.h"
#include "GameManager.h"

GameObject::GameObject()
{
	GameManager::AddGameObject(this);
}

void GameObject::Delete()
{
	markedForDelete = true;
}

void GameObject::ImGuiDraw() { }