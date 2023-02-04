#pragma once
#include "Game/GameObject.h"

class TextRenderer;

class DamageTextEffect : public GameObject
{
public:
	DamageTextEffect(unsigned int damage, glm::vec3 position);

	virtual void Update(float deltaTime) override;
	virtual void Draw(Camera* camera) override;

private:
	TextRenderer* textRenderer;

	float textMoveSpeed;

	float baseScale = 0.10f;
	float bigNumDecrease = 0.25f;
	float baseMovementSpeed = 0.1f;

	glm::vec3 textMoveDir;

	float effectLifeTime = 1.0f;
	float maxMoveAngle = 30.0f;
};