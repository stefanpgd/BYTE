#pragma once
#include "Essence.h"

class ControlEssence : public Essence
{
public:
	ControlEssence(Transform* playerTransform, SpriteRenderer* eyeRenderer);

	virtual void Update(float deltaTime, glm::vec2 directionalInput) override;
	virtual void Draw(Camera* camera) override;

private:
	glm::vec3 handOffset;
	glm::vec3 leftHand;
	glm::vec2 lastInput;

	// Walking Hand Animation // 
	glm::vec3 walkHandOffset = glm::vec3(0.71, 0.26f, 0.1);

	float swingAngle = 0.0f;
	float swingSpeed = 10.0f;
	float swingAngleMax = 0.45f;
	float swingRadius = 0.5f;
	float defaultAngle = 5.0f;
	float animSwitchSpeed = 6.0f;
	float swingDelay = 7.8f;
	float armDistance = 0.2f;

	// Idle Hand Animation //
	glm::vec3 idleHandOffset = glm::vec3(-0.85, 0.0f, 0.1);
	float handYOffset = -0.15f;
	float handBopIdle = 0.04f;
	float handBopTimer = 0.0f;
	float handBopSpeed = 4.4f;
	float otherHandDelay = 0.65f;
};