#pragma once

#include <cmath>
#include <limits>
#include <memory>

namespace Tmpl8
{
	// Usings

	using std::shared_ptr;
	using std::make_shared;
	using std::sqrt;

	// Constants

	const float infinity = std::numeric_limits<float>::infinity();
	const float pi = 3.1415926535897932385f;
	const float numberE = 2.7182818284590452353602874713527f;
	const float dividedByPI = 1 / pi;

	const float refractDiamond = 2.408f;
	const float refractGlass = 1.51f;
	const float refractCrownGlass = 1.61f;
	const float refractFlashedGlass = 1.88f;
	const float refractIce = 1.309f;
	const float refractPerspex = 1.49f;
	const float refractQuarts = 1.54f;
	const float refractCalciumFluoride = 1.432f;
	const float refractAcryl = 1.487f;
	const float refractCalcite = 1.65f;

	// Utility Functions

	float randomFloat();

	float seededRandomFloat(int* seed);

	float randomFloatInRange(float min, float max);

	vec3 randomvec3();

	vec3 randomvec3InRange(float min, float max);

	vec3 randomvec3InRange2(vec3 min, vec3 max);

	vec3 randomInUnitSphere();

	vec3 randomUnitVector();

	vec3 randomInUnitHemisphere(vec3* normalVector);

	vec3 randomInUnitDisk();

	vec3 reflectRay(vec3& directionVector, vec3& normalVector);

	vec3 refractRay(vec3& uv, vec3& normal, float etaDividedByEta);

	bool nearZero(vec3* vector);

	float floatClamp(float value, float min, float max);

	float degreesToRadians(float degrees);

}