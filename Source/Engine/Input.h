#pragma once
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>

enum class Keycode
{
	A = GLFW_KEY_A,
	B = GLFW_KEY_B,
	C = GLFW_KEY_C,
	D = GLFW_KEY_D,
	E = GLFW_KEY_E,
	F = GLFW_KEY_F,
	G = GLFW_KEY_G,
	H = GLFW_KEY_H,
	I = GLFW_KEY_I,
	J = GLFW_KEY_J,
	K = GLFW_KEY_K,
	L = GLFW_KEY_L,
	M = GLFW_KEY_M,
	N = GLFW_KEY_N,
	O = GLFW_KEY_O,
	P = GLFW_KEY_P,
	Q = GLFW_KEY_Q,
	R = GLFW_KEY_R,
	S = GLFW_KEY_S,
	T = GLFW_KEY_T,
	U = GLFW_KEY_U,
	V = GLFW_KEY_V,
	W = GLFW_KEY_W,
	X = GLFW_KEY_X,
	Y = GLFW_KEY_Y,
	Z = GLFW_KEY_Z
};

class Input
{
public:
	// Retrieve input values //
	static bool GetKey(Keycode key);
	static bool GetMouseButton(int i);
	static glm::vec2 GetMousePosition();

	// Functionality over controls // 
	static void LockCursor(bool lock);

private:
	static void Initialize(GLFWwindow* window);
	
	static void InputMouseCallback(GLFWwindow* window, double x, double y);

	static inline GLFWwindow* window;
	static inline glm::vec2 lastMousePosition;

	friend class Engine;
};