#pragma once
#include "GameObject.h"
#include <glm/glm.hpp>

class SpriteRenderer;

class Bullet : public GameObject
{
public:
	Bullet(glm::vec3 direction, float speed, float lifeTime, float spread = 0.0f);

	virtual void Update(float deltaTime) override;
	virtual void Draw(Camera* camera) override;

	glm::vec3 Color;
	float Emission;
	float BulletSize = 0.5f;

private:
	SpriteRenderer* spriteRenderer;

	glm::vec3 direction;
	float speed;
	float lifeTime;
	float spread;
};