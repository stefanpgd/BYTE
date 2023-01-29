#pragma once
#include "Essence.h"

class ExcitementEssence : public Essence
{
public:
	ExcitementEssence(Transform* playerTransform, SpriteRenderer* eyeRenderer);

	virtual void Update(float deltaTime, glm::vec2 directionalInput) override;
	virtual void Draw(Camera* camera) override;

private:

};