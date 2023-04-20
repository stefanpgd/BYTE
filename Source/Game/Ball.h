#pragma once
#include "GameSystems/GameObject.h"
#include <vector>

class SpriteRenderer;
class BoxCollider;
class ParticleSystem;

class Ball : public GameObject
{
public:
	Ball();

	virtual void Update(float deltaTime) override;
	virtual void Draw(Camera* camera) override;
	virtual void OnCollision(BoxCollider* collider);

	virtual void ImGuiDraw();

	void PanicMode();

private:
	void Bounce(glm::vec3 normal);
	void BlockBounce(BoxCollider* collider, glm::vec3 normal);

	SpriteRenderer* ballSprite;
	SpriteRenderer* ballHitSprite;
	BoxCollider* collider;

	std::vector<ParticleSystem*> particleSystems;

	glm::vec3 moveDirection;
	bool firstBounce = true;

	float moveSpeed = 12.0f;
	float speedIncreasePerBlock = 0.42f;
	float maxSpeed = 30.5f;

	float paddleSteerStrength = 1.2f;

	float rotationSpeed = 420.0f;

	float bounceShakeDuration = 0.08f;
	float bounceShakeStrength = 0.07f;

	// Map Boundaries //
	float mapX = 15.5f;
	float mapTop = 15.5f;
	float mapBottom = -19.5f;

	float hitTimer = 0.0f;
	float hitCooldown = 0.02f;

	float hitSpriteTimer = 0.0f;
	float hitSpriteDelay = 0.4f;

	float time = 0.0f;

	// Game Elements //
	float panicModeMultiplier = 2.25f;

	float blipJumpHeight = -4.0f;
	int bounceCount = 0;
	int bounceTillBlip = 0;
	int maxBounceTillBlip = 25;
	float jumpLength = 5.5f;
};