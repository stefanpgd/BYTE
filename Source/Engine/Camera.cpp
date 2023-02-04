#include "Engine/Camera.h"
#include "Engine/Utilities.h"
#include "Engine/Input.h"
#include "Graphics/Renderer.h"

#include <glm/gtc/matrix_transform.hpp>

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
		glm::vec3 shake = glm::vec3(
			RandomInRange(-screenshakeStrength, screenshakeStrength),
			RandomInRange(-screenshakeStrength, screenshakeStrength),
			RandomInRange(-screenshakeStrength, screenshakeStrength));

		shake *= shakeDirection;
		position += shake;
	}

	viewMatrix = glm::lookAt(position, position + Front, Up);
	projectionMatrix = glm::perspective(glm::radians(FOV), (float)Renderer::GetWindowWidth() / (float)Renderer::GetWindowHeight(), nearClip, farClip);
	viewProjectionMatrix = projectionMatrix * viewMatrix;
}

glm::vec3 Camera::ScreenToWorldPoint()
{
	glm::vec2 mouse = Input::GetMousePosition();

	float screenWidth = Renderer::GetWindowWidth();
	float screenHeight = Renderer::GetWindowHeight();

	float ndcX = (mouse.x / screenWidth) * 2 - 1.0f;
	float ndcY = (mouse.y / screenHeight) * 2 - 1.0f;
	
	glm::vec4 rayClip = glm::vec4(ndcX, ndcY, 0.0f, 0.0f);
	glm::vec4 rayEye = glm::inverse(projectionMatrix) * rayClip;

	rayEye.z = 0.0f;
	rayEye.w = 0.0f;
	glm::vec3 rayWorld = glm::vec3(glm::inverse(viewMatrix) * rayEye);
	return rayWorld;
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

void Camera::ApplyScreenshake(float duration, float magnitude, const glm::vec3& direction)
{
	screenshakeTimer = duration;
	screenshakeStrength = magnitude;
	shakeDirection = direction;
}