#pragma once

#include "render/base_renderer.hpp"
#include "graphics/image.hpp"

enum class DebugRenderMode {
	Color,
	Normal,
	Depth
};

class ImageRenderer: public BaseRenderer{
public:
	ImageRenderer(Vector2s viewport);

	Image Render(const Scene& scene, const Camera& camera, DebugRenderMode mode)const;
private:

	Color Miss()const;

	Color ClosestHit(HitResult hit, const Scene &scene, DebugRenderMode mode)const;
};