#pragma once
#include "GameSystems/GameObject.h"

class SpriteRenderer;
class BoxCollider;

class PlayerPaddle : public GameObject
{
public:
	PlayerPaddle();

	virtual void Update(float deltaTime) override;
	virtual void Draw(Camera* camera) override;
	virtual void OnCollision(BoxCollider* collider);

	virtual void ImGuiDraw();

private:
	SpriteRenderer* sprite;
	BoxCollider* collider;

	float horizontalInput;
	float inputResponse = 6.0f;
	float paddleSpeed = 25.0f;
	float boundary = 13.45f;
};