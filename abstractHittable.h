#pragma once
#include "precomp.h"
#include "ray.h"
#include "aabb.h"
#include "RayTracingUtilities.h"

namespace Tmpl8 {

	class abstractMaterial;
	struct hitRecordStruct
	{
		vec3 point = 0.f;
		vec3 normal = 0.f;
		vec3 scaling = (1.f, 1.f, 1.f);
		abstractMaterial* p_material;
		float t = 0.f;
		float u = 0.f;
		float v = 0.f;
		bool frontFace = false;

		inline void setFaceNormal(const ray& r, const vec3& outwardNormal)
		{
			frontFace = false;
			if (dot(r.m_direction, outwardNormal) < 0)
			{
				frontFace = true;
			}
			normal = frontFace ? outwardNormal : -outwardNormal;
		}
	};

	class abstractHittable
	{
		//Has to be public, can't be protected. 
	public:
		virtual ~abstractHittable() = default;
		virtual bool hit(const ray& r, hitRecordStruct& hitrecord, float smallestT, float biggestT) const = 0;
		virtual void boundingBox(aabb& box) const = 0;
	};
};