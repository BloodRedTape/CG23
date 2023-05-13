#pragma once

#include <vector>
#include <algorithm>
#include "math/aabb3.hpp"
#include "math/ray.hpp"
#include "primitives/hittable.hpp"
#include "primitives/triangle.hpp"

inline AABB3f MakeBoundingBoxFor(const std::vector<Triangle>& triangles) {
	if(!triangles.size())
		return {{}, {}};

	AABB3f box = triangles.front().MakeBoundingBox();

	for (const auto& triangle: triangles) {
		box += triangle.MakeBoundingBox();
	}

	return box;
}

struct BVHLeaf : Hittable {
	std::vector<Triangle> Triangles;
	const AABB3f BoundingBox;

	BVHLeaf(std::vector<Triangle> triangles) :
		Triangles(std::move(triangles)),
		BoundingBox(MakeBoundingBoxFor(Triangles)) 
	{}

	std::optional<HitResult> Hit(const Ray3f& ray, float t_min, float t_max)const override {
		if (!BoundingBox.Intersects(ray, t_min, t_max))
			return {};

		std::optional<HitResult> closest_hit;

		for (const Triangle& triangle : Triangles) {
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
};


struct BVHNode: Hittable{
	std::vector<HittableRef> Children;
	const AABB3f BoundingBox;

	BVHNode(std::vector<Triangle> triangles, size_t depth = 10):
		BoundingBox(MakeBoundingBoxFor(triangles))
	{

		size_t max_dim = MaxIndex(BoundingBox.Size().Data);

		AABB3f left = BoundingBox.CutHalfBy(max_dim);

		std::vector<Triangle> left_triangles;
		std::vector<Triangle> right_triangles;

		for (const auto& triangle : triangles) {
			Vector3f centroid = triangle.MakeCentroid();

			if (left.Inside(centroid))
				left_triangles.push_back(triangle);
			else
				right_triangles.push_back(triangle);
		}

		constexpr auto Treshold = 10;

		if(left_triangles.size() < Treshold || !depth)
			Children.push_back(std::make_unique<BVHLeaf>(std::move(left_triangles)));
		else
			Children.push_back(std::make_unique<BVHNode>(std::move(left_triangles), depth - 1));

		if(right_triangles.size() < Treshold || !depth)
			Children.push_back(std::make_unique<BVHLeaf>(std::move(right_triangles)));
		else
			Children.push_back(std::make_unique<BVHNode>(std::move(right_triangles), depth - 1));
	}

	std::optional<HitResult> Hit(const Ray3f& ray, float t_min, float t_max)const override {
		if(!BoundingBox.Intersects(ray, t_min, t_max))
			return {};

		std::optional<HitResult> closest_hit;

		for (const HittableRef& hittable: Children) {
			std::optional<HitResult> hit = hittable->Hit(ray, t_min, t_max);

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
};


