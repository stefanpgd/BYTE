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
	glm::vec3 walkHandOffset = glm::vec3(-0.34, 0.41f, 0.1);

	float swingAngle = 0.0f;
	float swingSpeed = 10.0f;
	float swingAngleMax = 0.33f;
	float swingRadius = 0.54f;
	float defaultAngle = 4.3f;
	float animSwitchSpeed = 6.0f;
	float swingDelay = 3.36f;
	float armDistance = -0.17f;

	// Idle Hand Animation //
	glm::vec3 idleHandOffset = glm::vec3(-0.425, 0.0f, 0.1);
	float handYOffset = -0.075f;
	float handBopIdle = 0.02f;
	float handBopTimer = 0.0f;
	float handBopSpeed = 4.4f;
	float otherHandDelay = 0.65f;
};