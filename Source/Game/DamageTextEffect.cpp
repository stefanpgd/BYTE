#include "Game/DamageTextEffect.h"

#include "Engine/Utilities.h"
#include "Graphics/TextRenderer.h"

DamageTextEffect::DamageTextEffect(unsigned int damage, glm::vec3 position)
{
	transform.Position = position;
	transform.Position.y += 0.5f;
	transform.Position.z += 0.2f;
	transform.Scale = glm::vec3((damage * bigNumDecrease) * baseScale);
	
	textMoveSpeed = damage * baseMovementSpeed;

	float randomAngle = RandomInRange(-maxMoveAngle, maxMoveAngle);
	float rad = glm::radians(90.0f + randomAngle);
	textMoveDir.x = cosf(rad);
	textMoveDir.y = sinf(rad);
	textMoveDir.z = 3.0f;

	textRenderer = new TextRenderer(std::to_string(damage), &transform);
}

void DamageTextEffect::Update(float deltaTime)
{
	effectLifeTime -= deltaTime;
	transform.Position += textMoveDir * textMoveSpeed * deltaTime;

	transform.Scale = Lerp(transform.Scale, glm::vec3(0.0f), deltaTime * 2.5f);

	if(effectLifeTime < 0.0f)
	{
		DeleteGameObject();
	}
}

void DamageTextEffect::Draw(Camera* camera)
{
	textRenderer->Draw(camera);
}
