#pragma once
#include "Engine/Transform.h"
#include "Engine/Camera.h"

class BoxCollider;

class GameObject
{
public:
	GameObject();
	virtual ~GameObject();

	void DeleteGameObject();

	virtual void Update(float deltaTime) = 0;
	virtual void Draw(Camera* camera) = 0;
	virtual void OnCollision(BoxCollider* collider);
	virtual void OnDestroy();

	virtual void ImGuiDraw();

	Transform transform;

	// Temp //
	bool markedForDelete = false;

private:
	friend class GameManager;
};