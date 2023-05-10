#pragma once

#include <vector>
#include "primitives/triangle.hpp"
#include "primitives/hittable.hpp"

class Mesh: public Hittable{
	std::vector<Triangle> m_Triangles;
public:
	Mesh(std::vector<Triangle> triangles):
		m_Triangles(std::move(triangles))
	{}

	std::optional<HitResult> Hit(const Ray3f& ray, float t_min, float t_max)const override {
		std::optional<HitResult> closest_hit;

		for (const Triangle& triangle: m_Triangles) {
			std::optional<HitResult> hit = triangle.Hit(ray, t_min, t_max);

			if (hit.has_value()) {

				if (closest_hit.has_value()) {
					if (hit->Distance < closest_hit->Distance)
						closest_hit = hit;
				} else {
					closest_hit = hit;
				}
			}
		}

		return closest_hit;
	}

	size_t Triangles()const {
		return m_Triangles.size();
	}
};
