#include "precomp.h"
#include "abstractHittable.h"
#include "metal.h"

namespace Tmpl8 {
	metal::metal(const vec3& color, float passFuzz)
	{
		fuzz = passFuzz;
		if (fuzz > 1) fuzz = 1;
		m_color = color;
	}

	bool metal::scatterRay(const ray& r_in, hitRecordStruct& hitRecord, vec3& attenuation, ray& scatteredRay)
	{
		vec3 reflectDir = (r_in.m_direction * hitRecord.scaling).normalized();
		m_reflectedRay = reflectRay(reflectDir, hitRecord.normal);
		scatteredRay = ray(hitRecord.point, m_reflectedRay + fuzz * hitRecord.scaling * randomInUnitSphere());
		attenuation = m_color;
		return ((dot(scatteredRay.m_direction, hitRecord.normal)) > 0);

	}
}