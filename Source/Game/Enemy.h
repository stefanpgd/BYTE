#pragma once
#include "GameObject.h"

class SpriteRenderer;
class BoxCollider;

class Enemy : public GameObject
{
public:
	Enemy(Transform* playerTransform);
	virtual ~Enemy() override;

	virtual void Update(float deltaTime) override;
	virtual void Draw(Camera* camera) override;
	virtual void OnCollision(const std::string& tag, GameObject* obj);

private:
	BoxCollider* collider;
	SpriteRenderer* enemyRenderer;
	SpriteRenderer* eyeRenderer;

	Transform* playerTransform;
	Transform eyeTransform;

	int health = 5;
	int maxHealth = health;

	float movementSpeed = 1.f;
	float avoidance = 0.7f;
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