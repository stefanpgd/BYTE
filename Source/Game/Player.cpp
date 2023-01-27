#include "Player.h"

#include "../Engine/Input.h"
#include "../Engine/Utilities.h"
#include "../Engine/Audio.h"

#include "../Graphics/SpriteRenderer.h"
#include "../Graphics/PostProcessor.h"

#include <imgui.h>

Player::Player(Camera* camera) : camera(camera)
{
	playerRenderer = new SpriteRenderer("player1.png", &transform);
	eyeRenderer = new SpriteRenderer("playerEyes.png", &eyeTransform);
	handRenderer = new SpriteRenderer("blank.png", &handTransform);

	handTransform.Scale = glm::vec3(handScale);
}

void Player::Update(float deltaTime)
{
	horizontalInput = Lerp(horizontalInput, Input::GetKey(Keycode::D) - Input::GetKey(Keycode::A), inputReponse * deltaTime);
	verticalInput = Lerp(verticalInput, Input::GetKey(Keycode::W) - Input::GetKey(Keycode::S), inputReponse * deltaTime);

	playerRenderer->FlipX = horizontalInput < 0;
	eyeRenderer->FlipX = horizontalInput < 0;

	transform.Position.x += horizontalInput * movementSpeed * deltaTime;
	transform.Position.y += verticalInput * movementSpeed * deltaTime;

	camera->Position.x = Lerp(camera->Position.x, transform.Position.x, cameraFollowSpeed * deltaTime);
	camera->Position.y = Lerp(camera->Position.y, transform.Position.y + cameraBop, cameraFollowSpeed * deltaTime);
	camera->Position.z = cameraOffset;

	playerRenderer->Update(deltaTime);

	glm::vec2 v = glm::vec2(horizontalInput, verticalInput);
	if(glm::length(v) > 0.2f)
	{
		walkSoundTimer += deltaTime;
		cameraBopTimer += cameraBopSpeed * deltaTime;

		if(walkSoundTimer > walkSoundDelay)
		{
			walkSoundTimer = 0.0f;
			Audio::PlaySound("walk.wav");
		}

		transform.Rotation.z = cosf(walkAnimTimer) * walkAnimAngle;
		cameraBop = cosf(cameraBopTimer) * cameraBopStrength;

		eyeTransform.Rotation.z = transform.Rotation.z;
		walkAnimTimer += walkAnimSpeed * deltaTime;

		swingAngle += swingSpeed * deltaTime;

		float angle = cosf(swingAngle) * swingAngleMax;
		float x = cosf(defaultAngle + angle) * swingRadius;
		float y = sinf(defaultAngle + angle) * swingRadius;

		glm::vec3 armOffset = walkHandOffset + glm::vec3(x, y, 0.0f);
		armOffset.x = -armOffset.x + armDistance;
		handOffset = armOffset;
	}
	else
	{
		walkAnimTimer = 0.0f;
		cameraBopTimer = 0.0f;
		swingAngle = 1.5f;

		transform.Rotation.z = Lerp(transform.Rotation.z, 0.0f, walkResetSpeed * deltaTime);
		cameraBop = Lerp(cameraBop, 0.0f, walkResetSpeed * deltaTime);
		eyeTransform.Rotation.z = transform.Rotation.z;

		handBopTimer += handBopSpeed * deltaTime;
		idleHandOffset.y = handYOffset + cosf(handBopTimer) * handBopIdle;

		handOffset = Lerp(handOffset, idleHandOffset, animSwitchSpeed * deltaTime);
	}

	if(Input::GetKey(Keycode::R))
	{
		if(!switched)
		{
			inEssence = !inEssence;
			switched = true;
			Camera::ApplyScreenshake(0.35f, 0.125f);
			Audio::PlaySound("essenceSwitch.wav");
		}
	}
	else
	{
		switched = false;
	}

	lastDeltaTime = deltaTime;

	if(inEssence)
	{
		timeInEssence += deltaTime;

		camera->FOV = Lerp(camera->FOV, inEssenceFOV, FOVLerpSpeed * deltaTime);
		eyeRenderer->Emission = Lerp(eyeRenderer->Emission, maxEmission, emissionSpeed * deltaTime);
		eyeRenderer->Color = Lerp(eyeRenderer->Color, essenceColor, colorLerpSpeed * deltaTime);

		if(timeInEssence > impactDuration)
		{
			PostProcessor::chromaticAberrationCenterStrength = Lerp(PostProcessor::chromaticAberrationCenterStrength, 0.0f, boomEffectSpeed * deltaTime);
		}
		else
		{
			PostProcessor::chromaticAberrationCenterStrength = Lerp(PostProcessor::chromaticAberrationCenterStrength, maxChromaticAberration * impactMultiplier, boomEffectSpeed * impactMultiplier * deltaTime);
		}
	}
	else
	{
		timeInEssence = 0.0f;
		camera->FOV = Lerp(camera->FOV, normalFOV, FOVLerpSpeed * deltaTime);
		eyeRenderer->Emission = Lerp(eyeRenderer->Emission, 0.0f, emissionSpeed * deltaTime);
		eyeRenderer->Color = Lerp(eyeRenderer->Color, glm::vec3(1.0f), colorLerpSpeed * deltaTime);
		PostProcessor::chromaticAberrationCenterStrength = Lerp(PostProcessor::chromaticAberrationCenterStrength, 0.0f, boomEffectSpeed * deltaTime);
	}

	eyeTransform.Position = transform.Position + eyeOffset;
	handTransform.Position = transform.Position + handOffset;
}

void Player::Draw(Camera* camera)
{
	playerRenderer->Draw(camera);
	eyeRenderer->Draw(camera);
		
	handRenderer->Draw(camera);

	glm::vec2 v = glm::vec2(horizontalInput, verticalInput);
	if(glm::length(v) > 0.2f)
	{
		handRenderer->Draw(camera);

		float angle = cosf(swingAngle + swingDelay) * swingAngleMax;
		float x = cosf(defaultAngle + angle) * swingRadius;
		float y = sinf(defaultAngle + angle) * swingRadius;

		glm::vec3 armOffset = walkHandOffset + glm::vec3(x, y, 0.0f);
		handOffset = armOffset;
		handOffset.x -= armDistance;

		handTransform.Position = transform.Position + handOffset;
		handRenderer->Draw(camera);
	}
	else
	{
		handRenderer->Draw(camera);
		leftHand = handOffset;
		leftHand.x = -leftHand.x;
		leftHand.y = handYOffset + cosf(handBopTimer + otherHandDelay) * handBopIdle;

		handTransform.Position = transform.Position + leftHand;
		handRenderer->Draw(camera);
	}
}

void Player::ImGuiDraw()
{
	ImGui::Begin("User Settings");
	ImGui::DragFloat("swingSpeed", &swingSpeed, 0.01f);
	ImGui::DragFloat("defaultAngle", &defaultAngle, 0.01f);
	ImGui::DragFloat("swingRadius", &swingRadius, 0.01f);
	ImGui::End();
}