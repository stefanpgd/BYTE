#include "Game/GameObject.h"
#include "Game/GameManager.h"
#include "Engine/BoxCollider.h"

GameObject::GameObject()
{
	GameManager::AddGameObject(this);
}

GameObject::~GameObject() {}

void GameObject::DeleteGameObject()
{
	markedForDelete = true;
}

void GameObject::ImGuiDraw() { }
void GameObject::OnCollision(BoxCollider* collider) {}