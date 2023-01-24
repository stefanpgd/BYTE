#pragma once
#include "GameObject.h"

class SpriteRenderer;

class Player : public GameObject
{
public:
	Player(Camera* camera);

	virtual void Update(float deltaTime) override;
	virtual void Draw(Camera* camera) override;

private:
	SpriteRenderer* spriteRenderer;
	Camera* camera;

	float movementSpeed = 5.0f;
	float horizontalInput = 0.0f;
	float verticalInput = 0.0f;

	float inputReponse = 8.0f;
	float cameraFollowSpeed = 6.0f;
};