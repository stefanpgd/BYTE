#include "GameSystems/GameObject.h"
#include "GameSystems/GameManager.h"
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
void GameObject::OnDestroy() { } 