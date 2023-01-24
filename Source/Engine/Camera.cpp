#include "Camera.h"
#include <glm/gtc/matrix_transform.hpp>
#include "../Graphics/Renderer.h"

Camera::Camera(const glm::vec3& position, const glm::vec3& front, const glm::vec3& up) :
	position(position), front(front), up(up)
{
	viewMatrix = glm::lookAt(position, position + front, up);
	projectionMatrix = glm::perspective(glm::radians(FOV), (float)Renderer::GetWindowWidth() / (float)Renderer::GetWindowHeight(), nearClip, farClip);
}

void Camera::Update(float deltaTime)
{
	viewMatrix = glm::lookAt(position, position + front, up);
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