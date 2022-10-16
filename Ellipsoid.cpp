#include "precomp.h"
#include "abstractHittable.h"
#include "RayTracingUtilities.h"
#include "Ellipsoid.h"

namespace Tmpl8 {
	Ellipsoid::Ellipsoid(vec3 center, vec3 EllipsoidScaling, float radius, abstractMaterial* material) : m_center(center), m_radius(radius), p_material(material)
	{

		m_edge = false;
		if (EllipsoidScaling[0] <= FLT_EPSILON || EllipsoidScaling[1] <= FLT_EPSILON || EllipsoidScaling[2] <= FLT_EPSILON || (radius <= FLT_EPSILON && radius >= -FLT_EPSILON))
		{
			m_edge = true;
		}
		else
		{
			m_passedDimensions = EllipsoidScaling;
			m_scaled.x = 1.f / (radius * EllipsoidScaling.x);
			m_scaled.y = 1.f / (radius * EllipsoidScaling.y);
			m_scaled.z = 1.f / (radius * EllipsoidScaling.z);
			m_sqrScaled = m_scaled * m_scaled;
		}
	}

	void Ellipsoid::boundingBox(aabb& box) const
	{
		vec3 min = m_center - vec3(m_radius * m_passedDimensions.x, m_radius * m_passedDimensions.y, m_radius * m_passedDimensions.z);
		vec3 max = m_center + vec3(m_radius * m_passedDimensions.x, m_radius * m_passedDimensions.y, m_radius * m_passedDimensions.z);
		box = aabb(min, max);
	}

	bool Ellipsoid::hit(const ray& r, hitRecordStruct& hitrecord, float smallestT, float biggestT) const
	{
		if (m_edge) return false;

		//Slightly different from ABC, but similar concept
		vec3 scaledDirection = r.m_direction * m_scaled;
		vec3 scaledDistance = (r.m_origin - m_center) * m_scaled;
		vec3 DistanceVector = r.m_origin - m_center;
		float a = dot(scaledDirection, scaledDirection);
		float halfB = dot(scaledDistance, scaledDirection);
		float c = dot(scaledDistance, scaledDistance) - 1.f;
		float discriminant = halfB * halfB - a * c;
		if (discriminant < 0)
		{
			return false;
		}

		float rootDiscriminant = (sqrtf(discriminant));
		float tDeterminant = (-halfB - rootDiscriminant) / a;

		if (tDeterminant < smallestT || biggestT < tDeterminant)
		{
			tDeterminant = (-halfB + rootDiscriminant) / a;
			if (tDeterminant < smallestT || biggestT < tDeterminant)
			{
				return false;
			}
		}

		hitrecord.t = tDeterminant;
		hitrecord.point = r.calculatePoint(hitrecord.t);

		//Calculus for the normal

		vec3 outwardNormal = ((hitrecord.point - m_center) * m_sqrScaled).normalized();

		hitrecord.setFaceNormal(r, outwardNormal);
		hitrecord.p_material = p_material;
		return true;
	}
};