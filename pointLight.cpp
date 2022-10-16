#include "precomp.h"
#include "pointLight.h"
#include "abstractHittable.h"


namespace Tmpl8 {
	pointLight::pointLight(const vec3& position, const vec3& color, const float& intensity)
	{
		m_position = position;
		m_color = color;
		m_intensity = intensity;
	}

	vec3 pointLight::Attenuation(const float& rSquared, hitRecordStruct& hitRecord, const vec3& angleIncidence)
	{
		float divideByRSquared = 1 / rSquared;
		return (m_color * m_intensity) * divideByRSquared * fmaxf(angleIncidence.dot(hitRecord.normal), 0);
	}

	vec3 pointLight::getPosition()
	{
		return m_position;
	}
};