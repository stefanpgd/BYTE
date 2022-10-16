#pragma once

namespace Tmpl8 {
	class aabb
	{
	public:
		aabb();
		aabb(const vec3& min, const vec3& max);
		float getSurfaceArea(const aabb& box);
		bool hit(const ray& r, float smallestT, float biggestT) const;

		vec3 m_maximum;
		vec3 m_minimum;
	};

	int getLongestAxis(const aabb& box);
	int getShortestAxis(const aabb& box);
	float getCost(const float& areaLeft, const float& nLeft, const float& areaRight, const float& nRight);
	aabb boxBox(const aabb& box1, const aabb& box2);

};
