#include "Player.h"

#include "../Engine/Input.h"
#include "../Engine/Utilities.h"
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

	camera->position.x = Lerp(camera->position.x, transform.Position.x, cameraFollowSpeed * deltaTime);
	camera->position.y = Lerp(camera->position.y, transform.Position.y, cameraFollowSpeed * deltaTime);
	camera->position.z = cameraOffset;

	playerRenderer->Update(deltaTime);

	if(Input::GetKey(Keycode::R))
	{
		if(!switched)
		{
			inEssence = !inEssence;
			switched = true;
		}
	}
	else
	{
		switched = false;
	}

	lastDeltaTime = deltaTime;

	if(inEssence)
	{
		emissionTimer += deltaTime;
		eyeRenderer->Emission = Lerp(minEmission, maxEmission, (sinf(emissionTimer) + 1.0f) * 0.5f);
		eyeRenderer->Color = essenceColor;
		PostProcessor::chromaticAberrationCenterStrength = Lerp(PostProcessor::chromaticAberrationCenterStrength, maxChromaticAberration, boomEffectSpeed * deltaTime);
	}
	else
	{
		eyeRenderer->Emission = 0.0f;
		eyeRenderer->Color = glm::vec3(1.0f);
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