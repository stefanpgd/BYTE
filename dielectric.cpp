#include "precomp.h"
#include "abstractHittable.h"
#include "dielectric.h"

namespace Tmpl8 {
	dielectric::dielectric(float refractionIndex)
	{
		m_refractionIndex = refractionIndex;
		
	}

	vec3 dielectric::beer(const float& distance)
	{
		//Density of glass is 2-4% 
		//return vec3(1.f, 1.f, 1.f);
		float density = randomFloatInRange(0.02f, 0.04f);
		return vec3(expf(-density * distance));
	}

	float dielectric::Schlick(const float& theta, const float& refIdx)
	{
		//1 here is the refractionIndex of air, so that makes sense.
		//Normally r0 supposed to be (refIdx1 - refIdx2) / (refIdx1 + refIdx2)
		float r0 = (1 - refIdx) / (1 + refIdx);
		r0 = r0 * r0;
		float minusThetaSquared = (1 - theta) * (1 - theta);
		return r0 + (1 - r0) * minusThetaSquared * (1 - theta);
	}

	float dielectric::Fresnel(const float& cosT, const float& n1, const float& n2)
	{
		float etaDividedByEta = n1 / n2;
		float cosI = sqrtf(fabs(1.f - (etaDividedByEta * etaDividedByEta) * (1.f - cosT * cosT)));

		return 0.5f * (((n1 * cosI - n2 * cosT) / (n1 * cosI + n2 * cosT)) * ((n1 * cosI - n2 * cosT) / (n1 * cosI + n2 * cosT))) +
			(((n1 * cosT - n2 * cosI) / (n1 * cosT + n2 * cosI)) * ((n1 * cosT - n2 * cosI) / (n1 * cosT + n2 * cosI)));
	}

	bool dielectric::scatterRay(const ray& r_in, hitRecordStruct& hitRecord, vec3& attenuation, ray& scatteredRay)
	{

		attenuation.x = 1.f;
		attenuation.y = 1.f;
		attenuation.z = 1.f;

		//You only want to calculate Beer's law with the ray inside of the sphere
		if (!hitRecord.frontFace)
		{
			//A new ray is cast from the first point of intersection, so this gets the distance within the dielectric. 
			float travelDistance = sqrtf((hitRecord.point - r_in.m_origin).sqrLentgh());
			attenuation *= beer(travelDistance);
		}

		float refractionRatio = hitRecord.frontFace ? (1.0f / m_refractionIndex) : m_refractionIndex;
		//	__debugbreak(); 
		vec3 unitDirection = r_in.m_direction.normalized();
		//-unit direction here, otherwise the cosine will always be negative. 
		float cosTheta = fmin(dot(-unitDirection, hitRecord.normal), 1.0f);
		float sinTheta = sqrtf(1.0f - cosTheta * cosTheta);

		bool cannotRefract = refractionRatio * sinTheta > 1.f;
		vec3 direction;

		//Probability theory. If something reflects 36% of the light, that's the same as shooting 10000 rays, of which 3600 fully reflect and the rest doesn't reflect, and taking the average of that. 
		if (cannotRefract || Fresnel(cosTheta, refractionRatio, 1.f) > randomFloat())
		{
			direction = reflectRay(unitDirection, hitRecord.normal);
		}
		else
		{
			direction = refractRay(unitDirection, hitRecord.normal, refractionRatio);
		}
		scatteredRay = ray(hitRecord.point, direction);
		return true;
	}
};