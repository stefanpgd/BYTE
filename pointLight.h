#pragma once
#include "abstractLight.h"

namespace Tmpl8 {
	struct hitRecordStruct;
	class pointLight : public abstractLight
	{
	public:
		pointLight(const vec3& position, const vec3& color, const float& intensity);
		vec3 Attenuation(const float& rSquared, hitRecordStruct& hitRecord, const vec3& rc);
		vec3 getPosition();

	private:
		vec3 m_color;
		float m_intensity;
		vec3 m_position;
	};
};

