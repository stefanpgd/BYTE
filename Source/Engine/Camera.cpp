#include "Camera.h"
#include <glm/gtc/matrix_transform.hpp>
#include "../Graphics/Renderer.h"
#include "Utilities.h"

Camera::Camera(const glm::vec3& position, const glm::vec3& front, const glm::vec3& up) :
	Position(position), Front(front), Up(up)
{
	viewMatrix = glm::lookAt(position, position + front, up);
	projectionMatrix = glm::perspective(glm::radians(FOV), (float)Renderer::GetWindowWidth() / (float)Renderer::GetWindowHeight(), nearClip, farClip);
}

void Camera::Update(float deltaTime)
{
	glm::vec3 position = Position;

	if(screenshakeTimer > 0.0f)
	{
		screenshakeTimer -= deltaTime;
		position += glm::vec3(
			RandomInRange(-screenshakeStrength, screenshakeStrength), 
			RandomInRange(-screenshakeStrength, screenshakeStrength), 
			RandomInRange(-screenshakeStrength, screenshakeStrength));
	}

	viewMatrix = glm::lookAt(position, position + Front, Up);
	projectionMatrix = glm::perspective(glm::radians(FOV), (float)Renderer::GetWindowWidth() / (float)Renderer::GetWindowHeight(), nearClip, farClip);
	viewProjectionMatrix = projectionMatrix * viewMatrix;
}

glm::mat4& Camera::GetViewProjectionMatrix()
{
	return viewProjectionMatrix;
}

float Camera::GetNearClip()
{
	return nearClip;
}

float Camera::GetFarClip()
{
	return farClip;
}

void Camera::ApplyScreenshake(float duration, float magnitude)
{
	screenshakeTimer = duration;
	screenshakeStrength = magnitude;
}