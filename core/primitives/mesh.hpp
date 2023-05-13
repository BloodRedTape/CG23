#pragma once

#include <vector>
#include "primitives/triangle.hpp"
#include "primitives/hittable.hpp"
#include "primitives/bvh_tree.hpp"


class Mesh: public Hittable{
	const size_t m_TrianglesCount;
	BVHNode m_BVHTree;
public:
	Mesh(std::vector<Triangle> triangles):
		m_TrianglesCount(triangles.size()),
		m_BVHTree(std::move(triangles))
	{}

	std::optional<HitResult> Hit(const Ray3f& ray, float t_min, float t_max)const override {
		return m_BVHTree.Hit(ray, t_min, t_max);
	}

	size_t Triangles()const {
		return m_TrianglesCount;
	}
};
