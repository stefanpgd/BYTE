#include "precomp.h"
#include "ray.h"

namespace Tmpl8 {
	ray::ray()
	{

	}

	ray::ray(const vec3& origin, const vec3& direction) : m_origin(origin), m_direction(direction.normalized())
	{

	}

	vec3 ray::returnOrigin()
	{
		return m_origin;
	}

	vec3 ray::returnDirection()
	{
		return m_direction;
	}

	vec3 ray::calculatePoint(const float& t) const
	{
		return m_origin + t * m_direction;
	}

};