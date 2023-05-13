#pragma once

#include <vector>
#include "primitives/triangle.hpp"
#include "primitives/hittable.hpp"
#include "primitives/bvh_tree.hpp"


class Mesh: public Hittable{
	const size_t m_TrianglesCount;
	BVHNode m_BVHTree;
	MaterialProperties m_Material;
public:
	Mesh(std::vector<Triangle> triangles):
		m_TrianglesCount(triangles.size()),
		m_BVHTree(std::move(triangles))
	{}

	std::optional<HitResult> Hit(const Ray3f& ray, float t_min, float t_max)const override {
		auto result = m_BVHTree.Hit(ray, t_min, t_max);
		if(result)
			result->Material = m_Material;
		return result;
	}

	size_t Triangles()const {
		return m_TrianglesCount;
	}

	void SetMaterial(MaterialProperties mat) {
		m_Material = mat;
	}
};
