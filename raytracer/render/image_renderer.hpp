#pragma once

#include "render/base_renderer.hpp"
#include "graphics/image.hpp"

class ImageRenderer: public BaseRenderer{
public:
	ImageRenderer(Vector2s viewport);

	Image Render(const Scene& scene, const Camera& camera)const;
private:

	Color Miss()const;

	Color ClosestHit(HitResult hit, const Scene &scene)const;
};