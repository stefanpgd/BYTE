#include "ControlEssence.h"
#include "../../Engine/Utilities.h"
#include "../../Engine/Camera.h"
#include "../../Engine/Input.h"
#include "../../Engine/Audio.h"
#include "../../Engine/BoxCollider.h"

#include <imgui.h>

ControlEssence::ControlEssence(Transform* playerTransform, SpriteRenderer* eyeRenderer, Camera* camera)
{
	this->camera = camera;
	this->playerTransform = playerTransform;
	this->eyeRenderer = eyeRenderer;

	leftHandCollider = new BoxCollider(glm::vec3(0.0f), glm::vec2(0.17f, 0.17f), "fist");
	leftHandCollider->IsStatic = false;
	leftHandCollider->IsActive = false;

	rightHandCollider = new BoxCollider(glm::vec3(0.0f), glm::vec2(0.17f, 0.17f), "fist");
	rightHandCollider->IsStatic = false;
	rightHandCollider->IsActive = false;

	FOV = 45.0f;
	essenceColor = glm::vec4(1.0f, 1.0f, 1.0f, 1.0f);
	eyeEmissionStrength = 0.0f;
}

void ControlEssence::Update(float deltaTime, glm::vec2 directionalInput)
{
	Essence::Update(deltaTime, directionalInput);

	punchTimer += deltaTime;
	handBopTimer += handBopSpeed * deltaTime;

	if(Input::GetMouseButton(0))
	{
		isActive = true;

		if(punchTimer > punchCooldown)
		{
			punchTimer = 0.0f;

			glm::vec3 camRay = glm::normalize(camera->ScreenToWorldPoint());
			camRay.y = -camRay.y;

			Camera::ApplyScreenshake(0.1f, 0.07f, -camRay);

			if(nextHandIsRight)
			{
				Audio::PlaySound("punch1.wav");
				rightHandPunching = true;
				rightHandCollider->IsActive = true;
				targetRightHand = playerTransform->Position + camRay * punchDistance;
			}
			else
			{
				Audio::PlaySound("punch2.wav");
				leftHandPunching = true;
				leftHandCollider->IsActive = true;
				targetLeftHand = playerTransform->Position + camRay * punchDistance;
			}

			nextHandIsRight = !nextHandIsRight;
		}
	}
	else
	{
		isActive = false;
	}

	if(leftHandPunching)
	{
		punchLeftTimer += deltaTime;
		leftHandTransform.Position = Lerp(leftHandTransform.Position, targetLeftHand, punchSpeed * deltaTime);
		leftHandTransform.Scale = Lerp(leftHandTransform.Scale, glm::vec3(punchHandScale), punchSpeed * deltaTime);

		leftHandCollider->Position = leftHandTransform.Position;

		if(punchLeftTimer > punchDuration)
		{
			punchLeftTimer = 0.0f;
			leftHandPunching = false;
		}
	}
	else
	{
		leftHandCollider->IsActive = false;
		idleHandOffset.y = handYOffset + cosf(handBopTimer) * handBopIdle;

		glm::vec3 target = playerTransform->Position + idleHandOffset;
		leftHandTransform.Position = Lerp(leftHandTransform.Position, target, stateSwitchSpeed * deltaTime);
		leftHandTransform.Scale = Lerp(leftHandTransform.Scale, glm::vec3(handScale), punchSpeed * deltaTime);
	}

	if(rightHandPunching)
	{
		punchRightTimer += deltaTime;
		rightHandTransform.Position = Lerp(rightHandTransform.Position, targetRightHand, punchSpeed * deltaTime);
		rightHandTransform.Scale = Lerp(rightHandTransform.Scale, glm::vec3(punchHandScale), punchSpeed * deltaTime);

		rightHandCollider->Position = rightHandTransform.Position;

		if(punchRightTimer > punchDuration)
		{
			punchRightTimer = 0.0f;
			rightHandPunching = false;
		}
	}
	else
	{
		rightHandCollider->IsActive = false;
		idleHandOffset.y = handYOffset + cosf(handBopTimer + otherHandDelay) * handBopIdle;

		glm::vec3 target = idleHandOffset;
		target.x = -target.x;
		target += playerTransform->Position;

		rightHandTransform.Position = Lerp(rightHandTransform.Position, target, stateSwitchSpeed * deltaTime);
		rightHandTransform.Scale = Lerp(rightHandTransform.Scale, glm::vec3(handScale), punchSpeed * deltaTime);
	}
}

void ControlEssence::LeftHandDraw(Camera* camera)
{
	leftHandRenderer->Draw(camera);
}

void ControlEssence::RightHandDraw(Camera* camera)
{
	rightHandRenderer->Draw(camera);
}