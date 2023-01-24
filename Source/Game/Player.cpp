#include "Player.h"

#include "../Engine/Input.h"
#include "../Engine/Utilities.h"
#include "../Graphics/SpriteRenderer.h"

Player::Player(Camera* camera) : camera(camera)
{
	spriteRenderer = new SpriteRenderer("enemySkeleton.png", &transform, 4);
}

void Player::Update(float deltaTime)
{
	horizontalInput = Lerp(horizontalInput, Input::GetKey(Keycode::D) - Input::GetKey(Keycode::A), inputReponse * deltaTime);
	verticalInput = Lerp(verticalInput, Input::GetKey(Keycode::W) - Input::GetKey(Keycode::S), inputReponse * deltaTime);

	transform.Position.x += horizontalInput * movementSpeed * deltaTime;
	transform.Position.y += verticalInput * movementSpeed * deltaTime;

	camera->position.x = Lerp(camera->position.x, transform.Position.x, cameraFollowSpeed * deltaTime);
	camera->position.y = Lerp(camera->position.y, transform.Position.y, cameraFollowSpeed * deltaTime);

	spriteRenderer->Update(deltaTime);
}

void Player::Draw(Camera* camera)
{
	spriteRenderer->Draw(camera);
}