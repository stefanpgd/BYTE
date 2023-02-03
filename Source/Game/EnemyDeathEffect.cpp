#include "EnemyDeathEffect.h"
#include "../Graphics/SpriteRenderer.h"
#include "../Engine/Utilities.h"

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
}

void EnemyDeathEffect::Update(float deltaTime)
{
	headTransform.Rotation.z += headRotationZ * deltaTime;
	legTransform.Rotation.z += legRotationZ * deltaTime;

	headRotationZ = Lerp(headRotationZ, 0.0f, headEffectSpeed * deltaTime);
	legRotationZ = Lerp(legRotationZ, 0.0f, legEffectSpeed * deltaTime);

	headTransform.Position = Lerp(headTransform.Position, headTarget, headEffectSpeed * deltaTime);
	legTransform.Position = Lerp(legTransform.Position, legTarget, legEffectSpeed * deltaTime);
}

void EnemyDeathEffect::Draw(Camera* camera)
{
	headRenderer->Draw(camera);
	legRenderer->Draw(camera);
}
