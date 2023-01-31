#include "ControlEssence.h"
#include "../../Engine/Utilities.h"
#include "../../Engine/Camera.h"
#include <imgui.h>

ControlEssence::ControlEssence(Transform* playerTransform, SpriteRenderer* eyeRenderer)
{
	this->playerTransform = playerTransform;
	this->eyeRenderer = eyeRenderer;

	FOV = 45.0f;
	essenceColor = glm::vec4(1.0f, 1.0f, 1.0f, 1.0f);
	eyeEmissionStrength = 0.0f;
}

void ControlEssence::Update(float deltaTime, glm::vec2 directionalInput)
{
	Essence::Update(deltaTime, directionalInput);

	if(glm::length(directionalInput) > 0.2f)
	{
		swingAngle += swingSpeed * deltaTime;

		float angle = cosf(swingAngle) * swingAngleMax;
		float x = cosf(defaultAngle + angle) * swingRadius;
		float y = sinf(defaultAngle + angle) * swingRadius;

		glm::vec3 armOffset = walkHandOffset + glm::vec3(x, y, 0.0f);
		armOffset.x = -armOffset.x + armDistance;
		handOffset.z = -0.1f;

		handOffset = armOffset;
	}
	else
	{
		swingAngle = 1.5f;
		handBopTimer += handBopSpeed * deltaTime;
		idleHandOffset.y = handYOffset + cosf(handBopTimer) * handBopIdle;

		handOffset = Lerp(handOffset, idleHandOffset, animSwitchSpeed * deltaTime);
	}

	handTransform.Position = playerTransform->Position + handOffset;

	lastInput = directionalInput;
}

void ControlEssence::Draw(Camera* camera)
{
	if(glm::length(lastInput) > 0.2f)
	{
		handRenderer->Draw(camera);

		float angle = cosf(swingAngle + swingDelay) * swingAngleMax;
		float x = cosf(defaultAngle + angle) * swingRadius;
		float y = sinf(defaultAngle + angle) * swingRadius;

		glm::vec3 armOffset = walkHandOffset + glm::vec3(x, y, 0.0f);
		handOffset = armOffset;
		handOffset.x -= armDistance;

		handTransform.Position = playerTransform->Position + handOffset;
		handRenderer->Draw(camera);
	}
	else
	{
		handRenderer->Draw(camera);
		leftHand = handOffset;
		leftHand.x = -leftHand.x;
		leftHand.y = handYOffset + cosf(handBopTimer + otherHandDelay) * handBopIdle;

		handTransform.Position = playerTransform->Position + leftHand;
		handRenderer->Draw(camera);
	}
}
