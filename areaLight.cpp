#include "precomp.h"
#include "abstractHittable.h"
#include "areaLight.h"

namespace Tmpl8 {
	areaLight::areaLight(vec3 min, vec3 max, vec3 color, float intensity)
	{
		m_minimum = min;
		m_maximum = max;
		m_color = color;
		m_intensity = intensity;
	}

	vec3 areaLight::Attenuation(const float& rSquared, hitRecordStruct& hitRecord, const vec3& angleIncidence)
	{
		float divideByRSquared = 1.f / rSquared;
		return (m_color * m_intensity) * divideByRSquared * fmaxf(angleIncidence.dot(hitRecord.normal), 0);
	}

	vec3 areaLight::getPosition()
	{
		return randomvec3InRange2(m_minimum, m_maximum);
		//I use this function in every sample. An area light is basically an area that fully consists of point lights. 
		//The pointLight getPosition function returns the same position every time, but the area light getPosition function
		//returns a different position every time. Over the course of many samples, this will produce soft shadows around
		//the parts that are not illuminated by all of the possible positions. 
		
		/*vec3 randomvec3InRange2(vec3 min, vec3 max)
		{
			return vec3(randomFloatInRange(min.x, max.x), randomFloatInRange(min.y, max.y), randomFloatInRange(min.z, max.z));
		}*/
	}

}