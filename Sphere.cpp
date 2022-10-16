#include "precomp.h"
#include "abstractHittable.h"
#include "RayTracingUtilities.h"
#include "Sphere.h"




namespace Tmpl8 {
	Sphere::Sphere(vec3 center, float radius, abstractMaterial* material) : m_center(center), m_radius(radius), p_material(material)
	{
		m_sqrRadius = radius * radius;
		m_makeUnit = 1.f / radius;
	}

	void Sphere::boundingBox(aabb& box) const
	{
		vec3 min = m_center - vec3(m_radius);
		vec3 max = m_center + vec3(m_radius);
		box = aabb(min, max);
	}

	static void GetSphereUV(float& u, float& v, const vec3& point)
	{
		//The point here is the normal, because you always want a point on the edge of the sphere. Getting the normal gives you the point of intersection, while making sure it's actually on the surface. 
		float theta = acosf(-point.y);
		float fi = atan2f(-point.z, point.x) + PI;

		u = fi * 0.5f * dividedByPI;
		v = theta * dividedByPI;
	}

	bool Sphere::hit(const ray& r, hitRecordStruct& hitrecord, float smallestT, float biggestT) const
	{
		//x^2 + y^2 + z^2 = r^2, so (x^2) + (y^2) + (z^2 - r^2) = 0 
		//Abc formula
		vec3 DistanceVector = r.m_origin - m_center;
		float halfB = dot(DistanceVector, r.m_direction);
		float c = DistanceVector.sqrLentgh() - m_sqrRadius;
		float discriminant = halfB * halfB - c;
		if (discriminant < 0)
		{
			return false;
		}

		//Abc formula, t determination. 
		float rootDiscriminant = (sqrtf(discriminant));
		float tDeterminant = (-halfB - rootDiscriminant);
		//These are min and max values, so if neither of these are true the thing has no solution.
		if (tDeterminant < smallestT || biggestT < tDeterminant)
		{
			tDeterminant = (-halfB + rootDiscriminant);
			if (tDeterminant < smallestT || biggestT < tDeterminant)
			{
				return false;
			}
		}

		hitrecord.t = tDeterminant;
		hitrecord.point = r.calculatePoint(hitrecord.t);
		hitrecord.scaling = vec3(1.f);

		vec3 outwardNormal = (hitrecord.point - m_center) * m_makeUnit;

		hitrecord.setFaceNormal(r, outwardNormal);
		hitrecord.p_material = p_material;
		GetSphereUV(hitrecord.u, hitrecord.v, outwardNormal);
		return true;
	}
};