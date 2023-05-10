#include "console_renderer.hpp"
#include "math/functions.hpp" 
#include "math/vector2.hpp"
#include <algorithm>

ConsoleRenderer::ConsoleRenderer(Vector2s viewport):
	BaseRenderer(viewport)
{}

void ConsoleRenderer::Render(const Scene& scene, const Camera& camera, RenderMode mode)const {
	puts("Final Image: ");

	for (int y = m_Viewport.y; y >= 0; y--) {
		for (int x = 0; x < m_Viewport.x; x++) {
			Ray3f ray = GenRay({x, y}, camera);

			std::optional<HitResult> result = TraceRay(ray, scene);

			switch (mode) {
			case RenderMode::Color:
				putchar(result.has_value() ? ClosestHit(*result, scene) : Miss());
				break;
			case RenderMode::Intersection:
				putchar(result.has_value() ? '#' : ' ');
				break;
			case RenderMode::Distance:
				result.has_value() ? printf("%2.1f ", result->Distance) : printf("null ");
				break;
			}
		}

		putchar('\n');
	}
}

char ConsoleRenderer::Miss()const{
	return ' ';
}

char ConsoleRenderer::ClosestHit(HitResult hit, const Scene &scene)const{
	Vector3f light_to_object_direction = Math::Normalize(scene.PointLight.Position - hit.Position);

	float diffuse = std::max(Math::Dot(hit.Normal, light_to_object_direction), 0.f);

	const char colors[] = ".*#0@";
	int colors_count = lengthof(colors) - 1;

	int index = Math::Clamp<int>(diffuse * 4, 0, colors_count - 1);

	return colors[index];
}
