#pragma once
#include <cmath>
#include <glm/glm.hpp>

inline float Random01()
{
	return float(rand() / (RAND_MAX + 1.0));
}

inline float RandomInRange(float min, float max)
{
	return min + (max - min) * Random01();
}

inline int RandomInRange(int min, int max)
{
	return int(min + (max - min) * Random01());
}

inline float Lerp(float a, float b, float t)
{
	return a * (1.0f - t) + b * t;
}

inline glm::vec3 Lerp(glm::vec3 a, glm::vec3 b, float t)
{
	return a * (1.0f - t) + b * t;
}

inline glm::vec4 Lerp(glm::vec4 a, glm::vec4 b, float t)
{
	return a * (1.0f - t) + b * t;
}