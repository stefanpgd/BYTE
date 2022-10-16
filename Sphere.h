#pragma once



namespace Tmpl8 {
	class Sphere : public abstractHittable
	{
	public:
		Sphere(vec3 center, float radius, abstractMaterial* material);
		bool hit(const ray& r, hitRecordStruct& hitrecord, float smallestT, float biggestT) const;
		void boundingBox(aabb& box) const;
	private:
		vec3 m_center;
		float m_radius;
		float m_sqrRadius;
		float m_makeUnit;
		abstractMaterial* p_material;
	};

	static void GetSphereUV(float& u, float& v, const vec3& point);
};
