#pragma once
#include "../Engine/Transform.h"
#include "../Engine/Camera.h"

class GameObject
{
public:
	GameObject();

	void Delete();

	virtual void Update(float deltaTime) = 0;
	virtual void Draw(Camera* camera) = 0;
	virtual void ImGuiDraw();

	Transform transform;

private:
	bool markedForDelete = false;

	friend class GameManager;
};