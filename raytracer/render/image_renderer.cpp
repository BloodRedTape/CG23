#include "image_renderer.hpp"
#include "utils/int_iterator.hpp"
#include <algorithm>
#include <execution>
	
ImageRenderer::ImageRenderer(Vector2s viewport):
	BaseRenderer(viewport)
{}

Image ImageRenderer::Render(const Scene& scene, const Camera& camera)const{
	Image image(m_Viewport.x, m_Viewport.y);

	std::for_each(std::execution::par, IntIterator<int>(0), IntIterator<int>(m_Viewport.y), [&](int y) {
		for (int x = 0; x < m_Viewport.x; x++) {
			Ray3f ray = GenRay({ x, y }, camera);

			std::optional<HitResult> result = TraceRay(ray, scene);

			//flip vertically because image has inverted coordinates
			image.Get(x, m_Viewport.y - y - 1) = result.has_value() ? ClosestHit(*result, scene) : Miss();
		}
	});

	return image;
}

Color ImageRenderer::Miss()const{
	return Color(30, 120, 255, 255);
}

Color ImageRenderer::ClosestHit(HitResult hit, const Scene& scene)const{
	using namespace Math;
	Vector3f light_to_object_direction = Normalize(scene.PointLight.Position - hit.Position);

	float diffuse = std::max(Math::Dot(hit.Normal, light_to_object_direction), 0.f);

	return Color(
		(u8)(255 * diffuse),
		(u8)(255 * diffuse),
		(u8)(255 * diffuse),
		255
	);
}