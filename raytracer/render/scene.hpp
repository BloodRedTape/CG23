#pragma once

#include <memory>
#include <vector>
#include "primitives/hittable.hpp"
#include "render/light.hpp"
#include "graphics/color.hpp"
#include "graphics/image.hpp"


struct Scene {
	std::vector<HittableRef> Objects;
	Color SkyFallbackColor = Color::While;
	Image SkySphericalMap;

	Color SampleSkyColor(Vector3f direction)const;
};