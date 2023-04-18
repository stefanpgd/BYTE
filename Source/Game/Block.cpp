#include "Block.h"

#include "Graphics/SpriteRenderer.h"
#include "Engine/Utilities.h"
#include "Engine/BoxCollider.h"

Block::Block()
{
	transform.Scale = glm::vec3(4.05f, 2.0f, 1.0f);

	collider = new BoxCollider(this, glm::vec2(2.0f, 1.0f), "block");
	collider->IsStatic = true;

	sprite = new SpriteRenderer("block.png", &transform);
	sprite->Color = glm::vec4(Random01(), Random01(), Random01(), 1.0f);
	emission = RandomInRange(0.8f, 5.2f);
	speed = RandomInRange(0.8f, 1.2f);

	glowTimer += RandomInRange(0.0f, 25.0f);
}

void Block::Update(float deltaTime)
{
	glowTimer += deltaTime * speed;

	sprite->Emission = abs(cos(glowTimer)) * emission;
}

void Block::Draw(Camera* camera)
{
	sprite->Draw(camera);
}

void Block::OnDestroy()
{
	collider->Remove();
}