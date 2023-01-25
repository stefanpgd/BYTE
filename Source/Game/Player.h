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

	// State //
	bool inEssence = true;
	float boomEffectSpeed = 3.4f;
	float maxChromaticAberration = 0.35f;
	bool switched = false;

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
	float minEmission = 3.5f;
	float maxEmission = 10.0f;
	float emissionTimer = 0.0f;
	float emissionSpeed = 1.2f;

	// Functionality // 
	float lastDeltaTime = 0.0f;
};