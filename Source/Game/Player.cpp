#include "Player.h"

#include "../Engine/Input.h"
#include "../Engine/Utilities.h"
#include "../Engine/Audio.h"
#include "../Engine/BoxCollider.h"

#include "../Graphics/SpriteRenderer.h"
#include "../Graphics/PostProcessor.h"
#include "../Graphics/Renderer.h"

#include <imgui.h>

Player::Player(Camera* camera) : camera(camera)
{
	playerRenderer = new SpriteRenderer("player1.png", &transform);
	eyeRenderer = new SpriteRenderer("playerEyes.png", &eyeTransform);

	controlEssence = new ControlEssence(&transform, eyeRenderer);
	excitementEssence = new ExcitementEssence(&transform, eyeRenderer, camera);

	activeEssence = controlEssence;

	collider = new BoxCollider((GameObject*)this, glm::vec2(1.0f, 1.0f));
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
	}
	else
	{
		walkAnimTimer = 0.0f;
		cameraBopTimer = 0.0f;

		transform.Rotation.z = Lerp(transform.Rotation.z, 0.0f, walkResetSpeed * deltaTime);
		cameraBop = Lerp(cameraBop, 0.0f, walkResetSpeed * deltaTime);
		eyeTransform.Rotation.z = transform.Rotation.z;
	}

	if(Input::GetKey(Keycode::R))
	{
		if(!switched)
		{
			switched = true;
			Camera::ApplyScreenshake(0.35f, 0.125f, glm::vec3(1.0f, 1.0f, 1.0f));
			Audio::PlaySound("essenceSwitch.wav");

			if(activeEssence == controlEssence)
			{
				activeEssence = excitementEssence;
				excitementEssence->Activate();
			}
			else
			{
				activeEssence = controlEssence;
				controlEssence->Activate();
			}
		}
	}
	else
	{
		switched = false;
	}

	camera->FOV = Lerp(camera->FOV, activeEssence->FOV, FOVLerpSpeed * deltaTime);

	// Eye tracking //
	float mouseX = Input::GetMousePosition().x;
	float mouseY = Input::GetMousePosition().y;
	float screenWidth = Renderer::GetWindowWidth();
	float screenHeight = Renderer::GetWindowHeight();

	float ndcX = (mouseX / screenWidth) * 2 - 1.0f;
	float ndcY = (mouseY / screenHeight) * 2 - 1.0f;

	glm::vec2 screenPos = glm::normalize(glm::vec2(ndcX, ndcY));
	float offsetX = eyeFollowMax * screenPos.x;
	float offsetY = eyeFollowMax * -screenPos.y;

	glm::vec3 eoffset = eyeOffset;
	if(horizontalInput < 0.0f)
	{
		eoffset.x = -eoffset.x;
	}

	glm::vec3 eyePos = eoffset + glm::vec3(offsetX, offsetY, 0.0f);

	eyeTransform.Position = transform.Position + eyePos;

	activeEssence->Update(deltaTime, v);
}

void Player::Draw(Camera* camera)
{
	playerRenderer->Draw(camera);
	eyeRenderer->Draw(camera);

	activeEssence->Draw(camera);

	playerRenderer->Color = glm::vec4(1.0f, 0.0f, 0.0f, 1.0f);
}

void Player::ImGuiDraw()
{
	ImGui::Begin("User Settings");
	ImGui::DragFloat("eyeFollowMax", &eyeFollowMax, 0.01f);
	ImGui::End();
}

void Player::OnCollision(const std::string& tag)
{
	playerRenderer->Color = glm::vec4(0.0f, 1.0f, 0.0f, 1.0f);
}