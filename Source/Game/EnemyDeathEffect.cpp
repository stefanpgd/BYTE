#include "Game/EnemyDeathEffect.h"
#include "Game/GameTime.h"

#include "Engine/Utilities.h"
#include "Graphics/SpriteRenderer.h"
#include "Graphics/ParticleSystem.h"

EnemyDeathEffect::EnemyDeathEffect(glm::vec3 position, glm::vec3 playerPosition, int enemySpriteIndex)
{
	headTransform.Position = position;
	legTransform.Position = position;

	headRenderer = new SpriteRenderer("enemy1Head.png", &headTransform);
	legRenderer = new SpriteRenderer("enemy1Legs.png", &legTransform);

	glm::vec3 dir = glm::normalize(position - playerPosition);
	float angle = glm::degrees(atan2f(dir.y, dir.x));
	
	float headAngle = RandomInRange(angle - angleOffset, angle + angleOffset);
	float legAngle = RandomInRange(angle - angleOffset, angle + angleOffset);

	float travelDistanceHead = RandomInRange(minTravelDistance, maxTravelDistance);
	float travelDistanceLegs = RandomInRange(minTravelDistance, maxTravelDistance * 0.75f);

	headTarget.x = cosf(glm::radians(headAngle)) * travelDistanceHead;
	headTarget.y = sinf(glm::radians(headAngle)) * travelDistanceHead;

	legTarget.x = cosf(glm::radians(legAngle)) * travelDistanceLegs;
	legTarget.y = sinf(glm::radians(legAngle)) * travelDistanceLegs;

	headTarget += position;
	legTarget += position;

	headEffectSpeed = RandomInRange(effectSpeedMin, effectSpeedMax);
	legEffectSpeed = RandomInRange(effectSpeedMin, effectSpeedMax);

	headRotationZ = RandomInRange(-headRotationMax, headRotationMax);
	legRotationZ = RandomInRange(-legRotationMax, legRotationMax);

	// Particle System //
	Particle minParticle;
	minParticle.LifeTime = 10.0f;
	minParticle.Color = glm::vec3(1.0f, 0.0f, 0.0f);
	minParticle.Emission = 0.0f;
	minParticle.Z = -0.01f;
	minParticle.Size = 1.0f / 18.0f;
	minParticle.MoveSpeed = 0.5f;
	minParticle.Drag = 10.0f;

	Particle maxParticle = minParticle;
	maxParticle.Color = glm::vec3(0.4f, 0.0f, 0.0f);
	maxParticle.Size = 1.0f / 12.0f;
	maxParticle.MoveSpeed = 4.5f;
	maxParticle.Drag = 25.0f;

	ParticleSystemSettings system;
	system.UseMinMax = true;
	system.MinParticle = minParticle;
	system.MaxParticle = maxParticle;
	system.particlesPerSeconds = 75;
	system.duration = 3.5f;

	headParticleEffect = new ParticleSystem(system, headTransform.Position);
	headParticleEffect->Activate();

	legParticleEffect = new ParticleSystem(system, legTransform.Position);
	legParticleEffect->Activate();

	GameTime::QueuePauseTicks(pauseTicks);
}

void EnemyDeathEffect::Update(float deltaTime)
{
	headTransform.Rotation.z += headRotationZ * deltaTime;
	legTransform.Rotation.z += legRotationZ * deltaTime;

	headRotationZ = Lerp(headRotationZ, 0.0f, headEffectSpeed * deltaTime);
	legRotationZ = Lerp(legRotationZ, 0.0f, legEffectSpeed * deltaTime);

	headTransform.Position = Lerp(headTransform.Position, headTarget, headEffectSpeed * deltaTime);
	legTransform.Position = Lerp(legTransform.Position, legTarget, legEffectSpeed * deltaTime);

	headParticleEffect->Update(deltaTime);
	legParticleEffect->Update(deltaTime);
}

void EnemyDeathEffect::Draw(Camera* camera)
{
	headParticleEffect->Draw(camera);
	legParticleEffect->Draw(camera);
	headRenderer->Draw(camera);
	legRenderer->Draw(camera);
}
