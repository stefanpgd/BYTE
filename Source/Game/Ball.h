#pragma once
#include "GameSystems/GameObject.h"

class SpriteRenderer;
class BoxCollider;

class Ball : public GameObject
{
public:
	Ball();

	virtual void Update(float deltaTime) override;
	virtual void Draw(Camera* camera) override;
	virtual void OnCollision(BoxCollider* collider);

	virtual void ImGuiDraw();

private:
	SpriteRenderer* ballSprite;
	BoxCollider* collider;

	glm::vec3 moveDirection;
	float moveSpeed = 48.0f;

	float rotationSpeed = 420.0f;

	// Map Boundaries //
	float mapX = 15.5f;
	float mapTop = 15.5f;
	float mapBottom = -19.5f;

	float hitTimer = 0.0f;
	float hitCooldown = 0.02f;
};