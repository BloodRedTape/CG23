#pragma once

#include "core/math/hittable.hpp"
#include "core/math/vector3.hpp"
#include "core/math/functions.hpp"

class Sphere : public Hittable {
private:
	Vector3f m_Origin;
	float m_Radius;
public:
	Sphere(Vector3f origin, float radius):
		m_Origin(origin),
		m_Radius(radius)
	{}

	std::optional<HitResult> Hit(const Ray3f& ray)const override {

		using namespace Math;

		Vector3f k = ray.Origin() - m_Origin;

		float a = Dot(ray.Direction(), ray.Direction());
		float b = 2 * Dot(ray.Direction(), k);
		float c = Dot(k, k) - m_Radius * m_Radius;
	
		const float discriminant = b * b - 4 * a * c;

		if (discriminant < 0){
			return {};
		}
	
		float x1 = (-b + Sqrt(discriminant)) / (2.f * a);
		float x2 = (-b - Sqrt(discriminant)) / (2.f * a);

		Vector3f point1 = ray.At(x1);
		Vector3f point2 = ray.At(x2);
	
		float distance1 = (point1 - ray.Origin()).Length();
		float distance2 = (point2 - ray.Origin()).Length();
	
		if (distance1 < distance2){
			return {{ point1, point1 - m_Origin}};
		} else {
			return {{ point2, point2 - m_Origin}};
		}
	}
};