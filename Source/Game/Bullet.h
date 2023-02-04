#pragma once
#include "Game/GameObject.h"
#include <glm/glm.hpp>

class SpriteRenderer;
class BoxCollider;

class Bullet : public GameObject
{
public:
	Bullet(glm::vec3 direction, float speed, float lifeTime, float spread = 0.0f);
	virtual ~Bullet() override;

	virtual void Update(float deltaTime) override;
	virtual void Draw(Camera* camera) override;

	glm::vec4 Color;
	float Emission;
	float BulletSize = 0.5f;

private:
	BoxCollider* collider;
	SpriteRenderer* spriteRenderer;

	glm::vec3 direction;
	float speed;
	float lifeTime;
	float spread;
	float zRotationSpeed = 0.0f;
};