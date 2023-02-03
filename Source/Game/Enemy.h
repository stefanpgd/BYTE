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

	float damageTimer = 0.0f;
	float damageCooldown = 0.12f;
	float hitEffectTimer = 1.0f;
	float hitEffectDuration = 0.03f;

	// Eyes //
	glm::vec3 eyeOffset = glm::vec3(-0.03f, -0.03f, 0.01f);
	float eyeFollowMax = 0.03f;
};