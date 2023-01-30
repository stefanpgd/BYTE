#pragma once
#include "Essence.h"

class Camera;

class ExcitementEssence : public Essence
{
public:
	ExcitementEssence(Transform* playerTransform, SpriteRenderer* eyeRenderer, Camera* camera);

	virtual void Update(float deltaTime, glm::vec2 directionalInput) override;
	virtual void Draw(Camera* camera) override;

private:
	Camera* camera;

	// Left Hand //
	glm::vec3 handOffsetLeft;
	float aimHandDistance = 1.0f;

	// Right Hand // 
	glm::vec3 handOffsetRight;
	glm::vec3 idleHandOffset = glm::vec3(-0.85, 0.0f, 0.1);
	float idleHandX = -0.85f;
	float handYOffset = -0.15f;
	float handBopIdle = 0.04f;
	float handBopTimer = 0.0f;
	float handBopSpeed = 4.4f;

	// Shooting //
	float delayPerShot = 0.08f;
	float delayTimer = 0.0f;
};