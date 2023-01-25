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
	eyeRenderer = new SpriteRenderer("blank.png", &eyeTransform);

	eyeTransform.Scale = glm::vec3(eyeScale);
}

void Player::Update(float deltaTime)
{
	horizontalInput = Lerp(horizontalInput, Input::GetKey(Keycode::D) - Input::GetKey(Keycode::A), inputReponse * deltaTime);
	verticalInput = Lerp(verticalInput, Input::GetKey(Keycode::W) - Input::GetKey(Keycode::S), inputReponse * deltaTime);

	playerRenderer->FlipX = horizontalInput < 0;

	transform.Position.x += horizontalInput * movementSpeed * deltaTime;
	transform.Position.y += verticalInput * movementSpeed * deltaTime;

	camera->Position.x = Lerp(camera->Position.x, transform.Position.x, cameraFollowSpeed * deltaTime);
	camera->Position.y = Lerp(camera->Position.y, transform.Position.y, cameraFollowSpeed * deltaTime);
	camera->Position.z = cameraOffset;

	playerRenderer->Update(deltaTime);

	glm::vec2 v = glm::vec2(horizontalInput, verticalInput);
	if(glm::length(v) > 0.2f)
	{
		walkSoundTimer += deltaTime;

		if(walkSoundTimer > walkSoundDelay)
		{
			walkSoundTimer = 0.0f;
			Audio::PlaySound("walk.wav");
		}
	}

	if(Input::GetKey(Keycode::R))
	{
		if(!switched)
		{
			inEssence = !inEssence;
			switched = true;
			Camera::ApplyScreenshake(0.25f, 0.1f);
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
		camera->FOV = Lerp(camera->FOV, inEssenceFOV, FOVLerpSpeed * deltaTime);
		eyeRenderer->Emission = Lerp(eyeRenderer->Emission, maxEmission, emissionSpeed * deltaTime);
		eyeRenderer->Color = Lerp(eyeRenderer->Color, essenceColor, colorLerpSpeed * deltaTime);
		PostProcessor::chromaticAberrationCenterStrength = Lerp(PostProcessor::chromaticAberrationCenterStrength, maxChromaticAberration, boomEffectSpeed * deltaTime);
	}
	else
	{
		camera->FOV = Lerp(camera->FOV, normalFOV, FOVLerpSpeed * deltaTime);
		eyeRenderer->Emission = Lerp(eyeRenderer->Emission, 0.0f, emissionSpeed * deltaTime);
		eyeRenderer->Color = Lerp(eyeRenderer->Color, glm::vec3(1.0f), colorLerpSpeed * deltaTime);
		PostProcessor::chromaticAberrationCenterStrength = Lerp(PostProcessor::chromaticAberrationCenterStrength, 0.0f, boomEffectSpeed * deltaTime);
	}
}

void Player::Draw(Camera* camera)
{
	playerRenderer->Draw(camera);

	if(horizontalInput >= 0.0f)
	{
		eyeTransform.Position = transform.Position + eyeOffset;
		eyeRenderer->Draw(camera);

		glm::vec3 offsetRight = eyeOffset;
		offsetRight.x += rightEyeOffset;

		eyeTransform.Position = transform.Position + offsetRight;
		eyeRenderer->Draw(camera);
	}
	else
	{
		glm::vec3 offsetLeft = eyeOffset;
		offsetLeft.x -= leftEyeOffset;
		eyeTransform.Position = transform.Position + offsetLeft;
		eyeRenderer->Draw(camera);

		glm::vec3 offsetRight = eyeOffset;
		offsetRight.x += rightEyeFlipped;
		eyeTransform.Position = transform.Position + offsetRight;
		eyeRenderer->Draw(camera);
	}
}

void Player::ImGuiDraw()
{
	ImGui::Begin("Player");
	ImGui::End();
}