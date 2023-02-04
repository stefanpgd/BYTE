#pragma once
#include "Game/GameObject.h"

class SpriteRenderer;
class ParticleSystem;

class EnemyDeathEffect : public GameObject
{
public:
	EnemyDeathEffect(glm::vec3 position, glm::vec3 playerPosition, int enemySpriteIndex);

	virtual void Update(float deltaTime) override;
	virtual void Draw(Camera* camera) override;

private:
	SpriteRenderer* headRenderer;
	SpriteRenderer* legRenderer;

	ParticleSystem* headParticleEffect;
	ParticleSystem* legParticleEffect;

	Transform headTransform;
	Transform legTransform;

	glm::vec3 headTarget;
	glm::vec3 legTarget;

	int pauseTicks = 24;

	float angleOffset = 30.0f;
	float minTravelDistance = 0.65f;
	float maxTravelDistance = 3.5f;

	float headEffectSpeed = 0.0f;
	float legEffectSpeed = 0.0f;
	float effectSpeedMin = 3.0f;
	float effectSpeedMax = 5.0f;

	float headRotationZ = 0.0f;
	float legRotationZ = 0.0f;
	float headRotationMax = 1080.0f;
	float legRotationMax = 720.0f;
};