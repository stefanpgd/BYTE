#include "ExcitementEssence.h"

#include "../../Engine/Input.h"
#include "../../Engine/Audio.h"
#include "../../Engine/Utilities.h"
#include "../../Graphics/Renderer.h"
#include "../../Engine/Camera.h"
#include "../Bullet.h"
#include <imgui.h>

ExcitementEssence::ExcitementEssence(Transform* playerTransform, SpriteRenderer* eyeRenderer, Camera* camera)
{
	this->camera = camera;
	this->playerTransform = playerTransform;
	this->eyeRenderer = eyeRenderer;

	FOV = 55.0f;
	essenceColor = glm::vec3(1.0f, 0.22f, 0.0f);
	eyeEmissionStrength = 10.0f;
}

void ExcitementEssence::Update(float deltaTime, glm::vec2 directionalInput)
{
	Essence::Update(deltaTime, directionalInput);

	glm::vec3 camRay = glm::normalize(camera->ScreenToWorldPoint());
	camRay.y = -camRay.y;

	handOffsetLeft = camRay * aimHandDistance;
	handTransform.Position = playerTransform->Position + handOffsetLeft;

	handBopTimer += handBopSpeed * deltaTime;
	idleHandOffset.x = directionalInput.x > 0 ? idleHandX : -idleHandX;
	idleHandOffset.y = handYOffset + cosf(handBopTimer) * handBopIdle;

	handOffsetRight = Lerp(handOffsetRight, idleHandOffset, 6.0f * deltaTime);

	delayTimer -= deltaTime;

	if(Input::GetMouseButton(0))
	{
		if(delayTimer <= 0.0f)
		{
			Bullet* bullet = new Bullet(camRay, 25, 1.2f, 0.20f);
			bullet->transform.Position = handTransform.Position;
			bullet->Color = essenceColor;
			bullet->Emission = 0.5f;
			delayTimer = delayPerShot;

			Audio::PlaySound("shoot.wav");
			Camera::ApplyScreenshake(0.15f, 0.1f, -camRay);
		}
	}
}

void ExcitementEssence::Draw(Camera* camera)
{
	handRenderer->Draw(camera);

	handTransform.Position = playerTransform->Position + handOffsetRight;
	handRenderer->Draw(camera);
}
