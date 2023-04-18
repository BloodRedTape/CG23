#pragma once

#include <memory>
#include <vector>
#include "core/math/hittable.hpp"
#include "core/render/light.hpp"

using HittableRef = std::unique_ptr<Hittable>;

struct Scene {
	std::vector<HittableRef> Objects;
	Light PointLight;
};