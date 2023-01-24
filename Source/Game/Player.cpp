#include "Player.h"

#include "../Graphics/Model.h"
#include "../Graphics/ShaderProgram.h"
#include "../Graphics/Texture.h"

Player::Player()
{
	model = new Model("Quad/Quad.gltf", &transform);
	shader = new ShaderProgram("color.vert", "sprite.frag");

	texture = new Texture("Cat.png", TextureType::Albedo, true, GL_REPEAT, GL_NEAREST);
}

void Player::Update(float deltaTime)
{

}

void Player::Draw(Camera* camera)
{
	shader->Bind();
	texture->Bind(shader);
	model->Draw(shader, camera);
}