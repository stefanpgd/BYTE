#include "ExcitementEssence.h"

#include "../../Engine/Input.h"
#include "../../Engine/Utilities.h"
#include "../../Graphics/Renderer.h"

ExcitementEssence::ExcitementEssence(Transform* playerTransform, SpriteRenderer* eyeRenderer)
{
	this->playerTransform = playerTransform;
	this->eyeRenderer = eyeRenderer;

	FOV = 60.0f;
	essenceColor = glm::vec3(1.0f, 0.22f, 0.0f);
	eyeEmissionStrength = 10.0f;
}

void ExcitementEssence::Update(float deltaTime, glm::vec2 directionalInput)
{
	Essence::Update(deltaTime, directionalInput);

	float mouseX = Input::GetMousePosition().x;
	float mouseY = Input::GetMousePosition().y;
	float screenWidth = Renderer::GetWindowWidth();
	float screenHeight = Renderer::GetWindowHeight();

	float ndcX = (mouseX / screenWidth) * 2 - 1.0f;
	float ndcY = (mouseY / screenHeight) * 2 - 1.0f;

	glm::vec3 screenPos = glm::normalize(glm::vec3(ndcX, -ndcY, 0.0f));

	handOffsetLeft = screenPos * aimHandDistance;
	handTransform.Position = playerTransform->Position + handOffsetLeft;

	handBopTimer += handBopSpeed * deltaTime;
	idleHandOffset.x = directionalInput.x > 0 ? idleHandX : -idleHandX;
	idleHandOffset.y = handYOffset + cosf(handBopTimer) * handBopIdle;

	handOffsetRight = Lerp(handOffsetRight, idleHandOffset, 6.0f * deltaTime);
}

void ExcitementEssence::Draw(Camera* camera)
{
	handRenderer->Draw(camera);

	handTransform.Position = playerTransform->Position + handOffsetRight;
	handRenderer->Draw(camera);
}
