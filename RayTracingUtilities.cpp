#include "precomp.h" 
#include "RayTracingUtilities.h"

namespace Tmpl8 {


	float randomFloat()
	{
		//random float in domain [0, 1>
		return rand() / (RAND_MAX + 1.0f);
	}

	float seededRandomFloat(int* seed)
	{
		//Returns a random float in domain [0, 1> 
		//Source: https://www.iquilezles.org/www/articles/sfrand/sfrand.htm
		union
		{
			float fres;
			unsigned int ires;
		};

		seed[0] *= 16807;
		ires = ((((unsigned int)seed[0]) >> 9) | 0x3f800000);
		return fres - 1.0f;
	}

	float randomFloatInRange(float min, float max)
	{
		//Uses the concept of linear interpolation. 
		return min + (max - min) * randomFloat();
	}

	vec3 randomvec3()
	{
		return vec3(randomFloat(), randomFloat(), randomFloat());
	}

	vec3 randomvec3InRange(float min, float max)
	{
		return vec3(randomFloatInRange(min, max), randomFloatInRange(min, max), randomFloatInRange(min, max));
	}

	vec3 randomvec3InRange2(vec3 min, vec3 max)
	{
		return vec3(randomFloatInRange(min.x, max.x), randomFloatInRange(min.y, max.y), randomFloatInRange(min.z, max.z));
	}

	vec3 randomInUnitSphere()
	{
		while (true)
		{
			vec3 randomvector = randomvec3InRange(-1, 1);
			if (randomvector.sqrLentgh() >= 1) continue;
			return randomvector;
		}
	}

	vec3 randomUnitVector()
	{
		return randomInUnitSphere().normalized();
	}

	vec3 randomInUnitHemisphere(vec3* normalVector)
	{
		vec3 randomvector = randomInUnitSphere();
		return (randomvector.dot(*normalVector) > 0.f) ? randomvector : -randomvector;
	}

	vec3 randomInUnitDisk()
	{
		vec3 randomVector = 1;
		while (randomVector.sqrLentgh() >= 1)
		{
			randomVector = vec3(randomFloatInRange(-1.f, 1.f), randomFloatInRange(-1.f, 1.f), 0);
		}
		return randomVector;

	}

	vec3 reflectRay(vec3& directionVector, vec3& normalVector)
	{
		return (directionVector - 2 * dot(directionVector, normalVector) * normalVector);
	}

	vec3 refractRay(vec3& uv, vec3& normal, float etaDividedByEta)
	{
		//Refraction code from http://www.cs.uu.nl/docs/vakken/magr/2019-2020/slides/lecture%2002%20-%20whitted.pdf
		float cosTheta = fmin(dot(-uv, normal), 1.0f);
		return etaDividedByEta * uv + normal * ((etaDividedByEta * cosTheta) - sqrtf(fabs(1.f - (etaDividedByEta * etaDividedByEta) * (1.f - cosTheta * cosTheta))));
	}

	float floatClamp(float value, float min, float max)
	{
		if (value < min) return min;
		if (value > max) return max;
		return value;
	}

	float degreesToRadians(float degrees)
	{
		//Saving a division
		return degrees * 0.00555555556f * PI;
	}
};