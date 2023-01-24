#include "Player.h"

#include "../Graphics/Model.h"
#include "../Graphics/ShaderProgram.h"
#include "../Graphics/Texture.h"

#include "../Engine/Input.h"
#include "../Engine/Utilities.h"

Player::Player()
{
	model = new Model("Quad/Quad.gltf", &transform);
	shader = new ShaderProgram("color.vert", "sprite.frag");

	texture = new Texture("Cat.png", TextureType::Albedo, true, GL_REPEAT, GL_NEAREST);
}

void Player::Update(float deltaTime)
{
	horizontalInput = Lerp(horizontalInput, Input::GetKey(Keycode::D) - Input::GetKey(Keycode::A), inputReponse * deltaTime);
	verticalInput = Lerp(verticalInput, Input::GetKey(Keycode::W) - Input::GetKey(Keycode::S), inputReponse * deltaTime);

	transform.Position.x += horizontalInput * movementSpeed * deltaTime;
	transform.Position.y += verticalInput * movementSpeed * deltaTime;
}

void Player::Draw(Camera* camera)
{
	shader->Bind();
	texture->Bind(shader);
	model->Draw(shader, camera);
}