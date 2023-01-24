#include "SpriteRenderer.h"

#include "../Engine/Transform.h"
#include "../Graphics/Model.h"
#include "../Graphics/ShaderProgram.h"
#include "../Graphics/Texture.h"

SpriteRenderer::SpriteRenderer(const std::string& fileName, Transform* transform, unsigned int framesInTexture, float framesPerSecond) : 
	framesInTexture(framesInTexture), FramesPerSecond(framesPerSecond)
{
	quad = new Model("Quad/Quad.gltf", transform);
	shaderProgram = new ShaderProgram("color.vert", "sprite.frag");
	texture = new Texture(fileName, TextureType::Albedo, true, GL_REPEAT, GL_NEAREST);
}

void SpriteRenderer::Update(float deltaTime)
{
	if(framesInTexture > 1 && !PauseAnimation)
	{
		animationTimer += FramesPerSecond * deltaTime;

		if(hasAnimationStride)
		{
			if(animationTimer > 1.0f)
			{
				animationTimer = 0.0f;
				currentFrame++;

				if(currentFrame > animationEnd)
				{
					currentFrame = animationStart;
				}
			}
		}
		else
		{
			currentFrame = int(animationTimer) % framesInTexture;
		}
	}
}

void SpriteRenderer::Draw(Camera* camera)
{
	shaderProgram->Bind();
	shaderProgram->SetInt("framesInTexture", framesInTexture);
	shaderProgram->SetInt("currentFrame", currentFrame);
	shaderProgram->SetBool("flipX", FlipX);
	shaderProgram->SetBool("flipY", FlipY);

	texture->Bind(shaderProgram);

	quad->Draw(shaderProgram, camera);
}

void SpriteRenderer::SetAnimationStride(unsigned int startFrame, unsigned int endFrame, float framesPerSecond)
{
	hasAnimationStride = true;

	if(animationStart != startFrame && animationEnd != endFrame)
	{
		currentFrame = startFrame;
		animationTimer = 0.0f;
	}

	animationStart = startFrame;
	animationEnd = endFrame;
	FramesPerSecond = framesPerSecond;
}