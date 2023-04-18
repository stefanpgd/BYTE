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
	virtual void OnDestroy() override;

private:
	BoxCollider* collider;
	SpriteRenderer* sprite;

	float emission;
	float glowTimer = 0.0f;
	float speed;
};