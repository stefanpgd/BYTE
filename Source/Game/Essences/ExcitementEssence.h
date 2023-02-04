#pragma once
#include "Game/Essences/Essence.h"

class Camera;

class ExcitementEssence : public Essence
{
public:
	ExcitementEssence(Transform* playerTransform, SpriteRenderer* eyeRenderer, Camera* camera);

	virtual void Update(float deltaTime, glm::vec2 directionalInput) override;

private:
	virtual void LeftHandDraw(Camera* camera) override;
	virtual void RightHandDraw(Camera* camera) override;

	Camera* camera;

	// Left Hand //
	glm::vec3 handOffsetLeft;
	float aimHandDistance = 0.5;

	// Right Hand // 
	glm::vec3 handOffsetRight;
	glm::vec3 idleHandOffset = glm::vec3(-0.85, 0.0f, 0.1);
	float idleHandX = -0.425f;
	float handYOffset = -0.15f;
	float handBopIdle = 0.04f;
	float handBopTimer = 0.0f;
	float handBopSpeed = 4.4f;

	// Shooting //
	float delayPerShot = 0.08f;
	float delayTimer = 0.0f;
};