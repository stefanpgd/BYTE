#pragma once
namespace Tmpl8 {
	class ray
	{
	public:
		ray();
		ray(const vec3& origin, const vec3& direction);
		vec3 returnOrigin();
		vec3 returnDirection();
		vec3 calculatePoint(const float& t) const;

		vec3 m_origin;
		vec3 m_direction;

	};
};
