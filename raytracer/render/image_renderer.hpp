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

	Image Render(const Scene& scene, const Camera& camera, DebugRenderMode mode, size_t samples)const;
private:

	Color Miss(const Scene &scene)const;

	Color ClosestHit(HitResult hit, const Scene &scene, DebugRenderMode mode)const;

	Vector3f AccumulateDiffuse(HitResult hit, const Scene& scene)const;

	float AccumulateShadow(HitResult hit, const Scene &scene)const;
};