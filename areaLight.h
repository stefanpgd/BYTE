#pragma once
#include "abstractLight.h"

namespace Tmpl8 {
	class areaLight :
		public abstractLight
	{
	public:
		areaLight(vec3 min, vec3 max, vec3 color, float intensity);
		vec3 Attenuation(const float& rSquared, hitRecordStruct& hitRecord, const vec3& rc);
		vec3 getPosition();
	private:
		vec3 m_minimum;
		vec3 m_maximum;
		vec3 m_color;
		float m_intensity;
	};
}