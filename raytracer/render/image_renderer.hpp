#pragma once

#include "render/base_renderer.hpp"
#include "graphics/image.hpp"

class ImageRenderer: public BaseRenderer{
public:
	ImageRenderer(Vector2s viewport);

	Image Render(const Scene& scene, const Camera& camera, size_t samples, size_t bounces)const;
private:

	Vector3f TracePath(const Ray3f &ray, const Scene &scene, size_t bounces_left)const;

};