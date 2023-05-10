#pragma once

#include <memory>
#include <vector>
#include "primitives/hittable.hpp"
#include "render/light.hpp"
#include "graphics/color.hpp"

using HittableRef = std::unique_ptr<Hittable>;

struct Scene {
	std::vector<HittableRef> Objects;
	std::vector<Light> PointLights;
	Color Sky = Color::Blue;
};