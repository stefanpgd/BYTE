#include "ExcitementEssence.h"

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
}

void ExcitementEssence::Draw(Camera* camera)
{
}
