#pragma once

namespace Tmpl8 {
	class Ellipsoid :
		public abstractHittable
	{
	public:

		Ellipsoid(vec3 center, vec3 EllipsoidScaling, float radius, abstractMaterial* material);

		bool hit(const ray& r, hitRecordStruct& hitrecord, float smallestT, float biggestT) const;
		void boundingBox(aabb& box) const;
	private:
		vec3 m_center;
		vec3 m_passedDimensions;
		float m_radius;
		vec3 m_scaled;
		vec3 m_sqrScaled;
		abstractMaterial* p_material;
		bool m_edge;
	};


};

