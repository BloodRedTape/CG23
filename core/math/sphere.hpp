#pragma once

#include "math/hittable.hpp"
#include "math/vector3.hpp"
#include "math/functions.hpp"

class Sphere : public Hittable {
private:
	Vector3f m_Origin;
	float m_Radius;
public:
	Sphere(Vector3f origin, float radius):
		m_Origin(origin),
		m_Radius(radius)
	{}

	std::optional<HitResult> Hit(const Ray3f& ray, float t_min, float t_max)const override {
		using namespace Math;

		Vector3f k = ray.Origin() - m_Origin;

		float a = Dot(ray.Direction(), ray.Direction());
		float b = 2 * Dot(ray.Direction(), k);
		float c = Dot(k, k) - m_Radius * m_Radius;
	
		const float discriminant = b * b - 4 * a * c;

		if (discriminant < 0){
			return {};
		}

		float root = (-b - Sqrt(discriminant)) / 2.f * a;
		if (root < t_min || t_max < root) {
			root = (-b + Sqrt(discriminant)) / 2.f * a;
			if (root < t_min || t_max < root)
				return {};
		}

		return {{ray.At(root), ray.At(root) - m_Origin, root}};
	}
};