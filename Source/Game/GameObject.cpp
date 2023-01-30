#include "GameObject.h"
#include "GameManager.h"

GameObject::GameObject()
{
	GameManager::AddGameObject(this);
}

void GameObject::DeleteGameObject()
{
	markedForDelete = true;
}

void GameObject::ImGuiDraw() { }
void GameObject::OnCollision(const std::string& tag) {}