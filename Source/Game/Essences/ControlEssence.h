#pragma once
#include "Game/Essences/Essence.h"

class BoxCollider;

class ControlEssence : public Essence
{
public:
	ControlEssence(Transform* playerTransform, SpriteRenderer* eyeRenderer, Camera* camera);

	virtual void Update(float deltaTime, glm::vec2 directionalInput) override;

private:
	virtual void LeftHandDraw(Camera* camera) override;
	virtual void RightHandDraw(Camera* camera) override;

	Camera* camera;

	// Punching //
	BoxCollider* leftHandCollider;
	BoxCollider* rightHandCollider;

	float punchTimer = 0.0f;
	float punchCooldown = 0.15f;
	float punchDistance = 0.85f;
	float punchSpeed = 22.0f;
	float punchLeftTimer = 0.0f;
	float punchRightTimer = 0.0f;
	float punchDuration = 0.13f;
	float punchHandScale = 0.18f;
	bool nextHandIsRight = true;
	bool leftHandPunching;
	bool rightHandPunching; 
	glm::vec3 targetRightHand;
	glm::vec3 targetLeftHand;

	// Idle Hand Animation //
	glm::vec3 idleHandOffset = glm::vec3(-0.425, 0.0f, 0.1);
	float handYOffset = -0.075f;
	float handBopIdle = 0.02f;
	float handBopTimer = 0.0f;
	float handBopSpeed = 4.4f;
	float otherHandDelay = 0.65f;
	float stateSwitchSpeed = 20.0f;
};