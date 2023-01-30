#pragma once
#include "GameObject.h"

#include "Essences/ControlEssence.h"
#include "Essences/ExcitementEssence.h"

class SpriteRenderer;
class BoxCollider;

class Player : public GameObject
{
public:
	Player(Camera* camera);

	virtual void Update(float deltaTime) override;
	virtual void Draw(Camera* camera) override;
	virtual void OnCollision(const std::string& tag) override;

	virtual void ImGuiDraw() override;

private:
	BoxCollider* collider;
	SpriteRenderer* playerRenderer;
	SpriteRenderer* eyeRenderer;

	Transform eyeTransform;

	Camera* camera;

	Essence* activeEssence;
	ControlEssence* controlEssence;
	ExcitementEssence* excitementEssence;

	// Audio //
	float walkSoundTimer = 0.0f;
	float walkSoundDelay = 0.25f;

	// Essence State/Switch //
	bool switched = false;
	float FOVLerpSpeed = 5.0f;

	// Movement //
	float movementSpeed = 7.2f;
	float horizontalInput = 0.0f;
	float verticalInput = 0.0f;
	float inputReponse = 6.5f;

	float walkAnimTimer = 0.0f;
	float walkAnimAngle = 4.0f;
	float walkAnimSpeed = 25.0f;
	float walkResetSpeed = 12.0f;

	// Camera // 
	float cameraFollowSpeed = 6.0f;
	float cameraOffset = 20.0f;

	float cameraBopTimer = 0.0f;
	float cameraBopSpeed = 12.0f;
	float cameraBop = 0.0f;
	float cameraBopStrength = 0.075f;

	// Eyes //
	glm::vec3 eyeOffset = glm::vec3(-0.06f, -0.06f, 0.01f);
	float eyeFollowMax = 0.06f;
};