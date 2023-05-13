#pragma once

#include <optional>
#include <memory>
#include "math/vector3.hpp"
#include "math/ray.hpp"

struct MaterialProperties {
	Vector3f Color{1.f};
	float Roughness = 1.f;
};

struct HitResult {
	Vector3f Position;
	Vector3f Normal;
	float Distance;

	MaterialProperties Material;
};

struct Hittable{
	virtual std::optional<HitResult> Hit(const Ray3f &ray, float t_min, float t_max)const = 0;
};

using HittableRef = std::unique_ptr<Hittable>;
