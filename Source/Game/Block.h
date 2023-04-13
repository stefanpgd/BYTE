#pragma once
#include "GameSystems/GameObject.h"

class SpriteRenderer;
class BoxCollider;

class Block : public GameObject
{
public:
	Block();

	virtual void Update(float deltaTime) override;
	virtual void Draw(Camera* camera) override;

private:
	SpriteRenderer* sprite;
	BoxCollider* collider;

	float glowTimer = 0.0f;
	float emission;
	float speed;
};