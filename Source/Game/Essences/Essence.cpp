#include "Essence.h"
#include "../../Graphics/SpriteRenderer.h"
#include "../../Engine/Utilities.h"
#include "../../Graphics/PostProcessor.h"

Essence::Essence()
{
	handRenderer = new SpriteRenderer("blank.png", &handTransform);
	handTransform.Scale = glm::vec3(handScale);
}

void Essence::Activate()
{
	timeInEssence = 0.0f;
}

void Essence::Update(float deltaTime, glm::vec2 directionalInput)
{
	if(timeInEssence < impactDuration)
	{
		timeInEssence += deltaTime;
		PostProcessor::chromaticAberrationCenterStrength = Lerp(PostProcessor::chromaticAberrationCenterStrength, maxChromaticAberration * impactMultiplier, boomEffectSpeed * impactMultiplier * deltaTime);
	}
	else
	{
		PostProcessor::chromaticAberrationCenterStrength = Lerp(PostProcessor::chromaticAberrationCenterStrength, 0.0f, boomEffectSpeed * deltaTime);
	}

	eyeRenderer->Emission = Lerp(eyeRenderer->Emission, eyeEmissionStrength, eyeEmissionSpeed * deltaTime);
	eyeRenderer->Color = Lerp(eyeRenderer->Color, essenceColor, eyeColorLerpSpeed * deltaTime);
}