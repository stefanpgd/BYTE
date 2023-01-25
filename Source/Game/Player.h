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

	Transform eyeTransform;

	Camera* camera;

	// Audio //
	float walkSoundTimer = 0.0f;
	float walkSoundDelay = 0.25f;

	// State //
	bool inEssence = true;
	float boomEffectSpeed = 4.4f;
	float maxChromaticAberration = 0.66f;
	bool switched = false;
	float normalFOV = 45.0f;
	float inEssenceFOV = 60.0f;
	float FOVLerpSpeed = 5.0f;

	// Movement //
	float movementSpeed = 5.0f;
	float horizontalInput = 0.0f;
	float verticalInput = 0.0f;
	float inputReponse = 8.0f;

	// Camera // 
	float cameraFollowSpeed = 6.0f;
	float cameraOffset = 20.0f;

	// Eyes //
	glm::vec3 eyeOffset = glm::vec3(-0.08f, 0.38f, 0.1f);
	float eyeScale = 0.075f;
	float leftEyeOffset = 0.36f;
	float rightEyeOffset = 0.51f;
	float rightEyeFlipped = 0.16f;

	glm::vec3 essenceColor = glm::vec3(1.0f, 0.22f, 0.0f);
	float colorLerpSpeed = 10.5f;
	float emissionSpeed = 6.5f;
	float maxEmission = 10.0f;

	// Functionality // 
	float lastDeltaTime = 0.0f;
};