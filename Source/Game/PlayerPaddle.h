#pragma once
#include "GameSystems/GameObject.h"

class SpriteRenderer;

class PlayerPaddle : public GameObject
{
public:
	PlayerPaddle();

	virtual void Update(float deltaTime) override;
	virtual void Draw(Camera* camera) override;

	virtual void ImGuiDraw();

private:
	SpriteRenderer* sprite;

	float horizontalInput;
	float inputResponse = 6.0f;
	float paddleSpeed = 15.0f;
};