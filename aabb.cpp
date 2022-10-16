#include "precomp.h"
#include "RayTracingUtilities.h"
#include "ray.h"
#include "aabb.h"

namespace Tmpl8 {

	aabb::aabb()
	{

	}

	aabb::aabb(const vec3& min, const vec3& max)
	{
		m_maximum = max;
		m_minimum = min;
	}

	float aabb::getSurfaceArea(const aabb& box)
	{
		vec3 area = box.m_maximum - box.m_minimum;
		return 2 * fabs(area.x * area.y) + 2 * fabs(area.x * area.z) + 2 * fabs(area.y * area.z);
	}

	bool aabb::hit(const ray& r, float smallestT, float biggestT) const
	{

		//Uses Andrew Kenslers implementation of the slab method. 
		//Slab: cutting your line up into pieces based on limits per axis. 
		vec3 dividedByDir;
		dividedByDir.x = 1 / r.m_direction.x;
		dividedByDir.y = 1 / r.m_direction.y;
		dividedByDir.z = 1 / r.m_direction.z;
		for (int i = 0; i < 3; i++)
		{
			//This is done so you can always compare in the same manner and don't need an else statement. 
			float lowerLimit = (m_minimum[i] - r.m_origin[i]) * dividedByDir[i];
			float upperLimit = (m_maximum[i] - r.m_origin[i]) * dividedByDir[i];
			if (dividedByDir[i] < 0.f) std::swap(lowerLimit, upperLimit);
			smallestT = lowerLimit > smallestT ? lowerLimit : smallestT;
			biggestT = upperLimit < biggestT ? upperLimit : biggestT;
			if (biggestT <= smallestT)	return false;
		}

		return true;
	}

	aabb boxBox(const aabb& box1, const aabb& box2)
	{
		vec3 min(fmin(box1.m_minimum.x, box2.m_minimum.x), fmin(box1.m_minimum.y, box2.m_minimum.y), fmin(box1.m_minimum.z, box2.m_minimum.z));
		vec3 max(fmax(box1.m_maximum.x, box2.m_maximum.x), fmax(box1.m_maximum.y, box2.m_maximum.y), fmax(box1.m_maximum.z, box2.m_maximum.z));
		return aabb(min, max);
	}

	int getLongestAxis(const aabb& box)
	{
		int longestAxis = 0;
		float previousAxisLength = 0.f;
		for (int i = 0; i < 3; i++)
		{
			float axisLength = fabs(box.m_maximum[i] - box.m_minimum[i]);
			if (axisLength > previousAxisLength) longestAxis = i;
			previousAxisLength = axisLength;
		}
		return longestAxis;
	}

	int getShortestAxis(const aabb& box)
	{
		int longestAxis = 0;
		float previousAxisLength = infinity;
		for (int i = 0; i < 3; i++)
		{
			float axisLength = fabs(box.m_maximum[i] - box.m_minimum[i]);
			if (axisLength < previousAxisLength) longestAxis = i;
			previousAxisLength = axisLength;
		}
		return longestAxis;
	}

	float getCost(const float& areaLeft, const float& nLeft, const float& areaRight, const float& nRight)
	{
		return areaLeft * nLeft + areaRight * nRight;
	}

};