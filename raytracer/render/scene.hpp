#pragma once

#include <memory>
#include <vector>
#include "primitives/hittable.hpp"
#include "render/light.hpp"

using HittableRef = std::unique_ptr<Hittable>;

struct Scene {
	std::vector<HittableRef> Objects;
	Light PointLight;
};