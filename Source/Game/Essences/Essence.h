#pragma once
#include <glm/glm.hpp>
#include "../../Engine/Transform.h"
#include "../../Engine/Camera.h"
#include "../../Graphics/SpriteRenderer.h"

class SpriteRenderer;

class Essence
{
public:
	Essence();

	void Activate();

	virtual void Update(float deltaTime, glm::vec2 directionalInput);
	virtual void Draw(Camera* camera) = 0;

	float FOV;

protected:
	glm::vec3 essenceColor;
	float eyeEmissionStrength = 0.0f;

	float eyeColorLerpSpeed = 10.5f;
	float eyeEmissionSpeed = 6.5f;

	Transform handTransform;
	Transform* playerTransform;

	SpriteRenderer* handRenderer;
	SpriteRenderer* eyeRenderer;

	float handScale = 1.0f / 8.0f;

	// Switch Effect //
	float timeInEssence = 100.0f;
	float boomEffectSpeed = 8.5f;
	float maxChromaticAberration = 0.50f;
	float impactDuration = 0.4f;
	float impactMultiplier = 4.5f;
};