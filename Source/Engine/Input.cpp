#include "Engine/Input.h"

void Input::Initialize(GLFWwindow* w)
{
	window = w;
	glfwSetCursorPosCallback(window, Input::InputMouseCallback);
}

void Input::LockCursor(bool lock)
{
	int state = lock ? GLFW_CURSOR_DISABLED : GLFW_CURSOR_DISABLED;
	glfwSetInputMode(window, GLFW_CURSOR, state);
}

void Input::InputMouseCallback(GLFWwindow* window, double x, double y)
{
	lastMousePosition.x = x;
	lastMousePosition.y = y;
}

bool Input::GetKey(Keycode key)
{
	return glfwGetKey(window, (int)key) == GLFW_PRESS;
}

bool Input::GetMouseButton(int i)
{
	return glfwGetMouseButton(window, GLFW_MOUSE_BUTTON_1 + i) == GLFW_PRESS;
}

glm::vec2 Input::GetMousePosition()
{
	return lastMousePosition;
}