#pragma once
#include "GameObject.h"

class SpriteRenderer;

class Player : public GameObject
{
public:
	Player(Camera* camera);

	virtual void Update(float deltaTime) override;
	virtual void Draw(Camera* camera) override;

	virtual void ImGuiDraw() override;

private:
	SpriteRenderer* playerRenderer;
	SpriteRenderer* eyeRenderer;
	SpriteRenderer* handRenderer;

	Transform eyeTransform;

	Camera* camera;

	// Audio //
	float walkSoundTimer = 0.0f;
	float walkSoundDelay = 0.25f;

	// State //
	bool inEssence = true;
	float boomEffectSpeed = 8.5f;
	float maxChromaticAberration = 0.50f;
	bool switched = false;
	float normalFOV = 45.0f;
	float inEssenceFOV = 60.0f;
	float FOVLerpSpeed = 5.0f;

	float timeInEssence = 0.0f;
	float impactDuration = 0.4f;
	float impactMultiplier = 4.5f;

	// Movement //
	float movementSpeed = 5.0f;
	float horizontalInput = 0.0f;
	float verticalInput = 0.0f;
	float inputReponse = 8.0f;

	float walkAnimTimer = 0.0f;
	float walkAnimAngle = 12.5f;
	float walkAnimSpeed = 15.0f;
	float walkResetSpeed = 12.0f;

	float cameraBopTimer = 0.0f;
	float cameraBopSpeed = 12.0f;
	float cameraBop = 0.0f;
	float cameraBopStrength = 0.075f;

	// Camera // 
	float cameraFollowSpeed = 6.0f;
	float cameraOffset = 20.0f;

	// Eyes //
	glm::vec3 eyeOffset = glm::vec3(0.0f, 0.0f, 0.01f);
	float leftEyeOffset = 0.36f;
	float rightEyeOffset = 0.51f;
	float rightEyeFlipped = 0.16f;

	glm::vec3 essenceColor = glm::vec3(1.0f, 0.22f, 0.0f);
	float colorLerpSpeed = 10.5f;
	float emissionSpeed = 6.5f;
	float maxEmission = 10.0f;

	// Functionality // 
	float lastDeltaTime = 0.0f;

	// Hands //
	Transform handTransform;
	float handScale = 1.0f / 8.0f;
	glm::vec3 handOffset = glm::vec3(0.85, 0.0f, 0.1);
	float handYOffset = -0.15f;
	float handBopIdle = 0.04f;
	float handBopTimer = 0.0f;
	float handBopSpeed = 4.4f;
	float otherHandDelay = 0.65f;
};