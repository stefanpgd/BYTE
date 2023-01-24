#pragma once
#include "GameObject.h"

class Model;
class ShaderProgram;
class Texture;

class Player : public GameObject
{
public:
	Player();

	virtual void Update(float deltaTime) override;
	virtual void Draw(Camera* camera) override;

private:
	Model* model;
	ShaderProgram* shader;
	Texture* texture;
};