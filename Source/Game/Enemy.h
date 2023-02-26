#pragma once
#include "Game/GameObject.h"

class SpriteRenderer;
class BoxCollider;
class GameManager;

class Enemy : public GameObject
{
public:
	Enemy(Transform* playerTransform, GameManager* gm);
	virtual ~Enemy() override;

	virtual void Update(float deltaTime) override;
	virtual void Draw(Camera* camera) override;
	virtual void OnCollision(BoxCollider* collider);

private:
	// Temp //
	GameManager* gameManager;

	BoxCollider* collider;
	SpriteRenderer* enemyRenderer;
	SpriteRenderer* eyeRenderer;

	Transform* playerTransform;
	Transform eyeTransform;

	int health = 5;
	int maxHealth = health;

	float movementSpeed = 1.f;
	float enemyAvoidance = 1.0f;
	float wallAvoidance = 1.4f;
	float wallAvoidanceTicks;

	float lastDeltaTime = 0.0f;
	float meleeRange = 1.0f;

	float damageTimer = 0.0f;
	float damageCooldown = 0.12f;
	float hitEffectTimer = 1.0f;
	float hitEffectDuration = 0.03f;

	float walkAnimTimer = 0.0f;
	float walkAnimSpeed = 25.0f;
	float walkAnimAngle = 3.0f;
	float walkResetSpeed = 12.0f;

	// Eyes //
	glm::vec3 eyeOffset = glm::vec3(-0.03f, -0.03f, 0.01f);
	float eyeFollowMax = 0.03f;
};