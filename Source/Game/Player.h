#pragma once
#include "GameObject.h"

#include "Essences/ControlEssence.h"

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
	ControlEssence* essence;

	// Audio //
	float walkSoundTimer = 0.0f;
	float walkSoundDelay = 0.25f;

	// State //
	bool inEssence = true;
	float boomEffectSpeed = 8.5f;
	float maxChromaticAberration = 0.50f;
	bool switched = false;
	float FOVLerpSpeed = 5.0f;

	float timeInEssence = 0.0f;
	float impactDuration = 0.4f;
	float impactMultiplier = 4.5f;

	// Movement //
	float movementSpeed = 7.2f;
	float horizontalInput = 0.0f;
	float verticalInput = 0.0f;
	float inputReponse = 6.5f;

	float walkAnimTimer = 0.0f;
	float walkAnimAngle = 4.0f;
	float walkAnimSpeed = 25.0f;
	float walkResetSpeed = 12.0f;

	float cameraBopTimer = 0.0f;
	float cameraBopSpeed = 12.0f;
	float cameraBop = 0.0f;
	float cameraBopStrength = 0.075f;

	// Camera // 
	float cameraFollowSpeed = 6.0f;
	float cameraOffset = 20.0f;

	// Eyes //
	glm::vec3 eyeOffset = glm::vec3(-0.06f, -0.06f, 0.01f);
	float eyeFollowMax = 0.06f;
	float leftEyeOffset = 0.36f;
	float rightEyeOffset = 0.51f;
	float rightEyeFlipped = 0.16f;

	//glm::vec3 essenceColor = glm::vec3(1.0f, 0.22f, 0.0f);
};