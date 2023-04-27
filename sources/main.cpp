#include <cstdio>

#include "gtest\gtest.h"

#include "render/console_renderer.hpp"
#include "math/sphere.hpp"
#include "math/plane.hpp"

int main() {
	RUN_ALL_TESTS();


	Scene scene;
	scene.Objects.push_back(std::make_unique<Sphere>(Vector3f{0, 0, 0}, 1.f));
	scene.Objects.push_back(std::make_unique<Sphere>(Vector3f{0, 1, 0}, 0.5f));
	scene.Objects.push_back(std::make_unique<Plane>(Vector3f(0, -0.5f, 0), Vector3f::Up() ));

	scene.PointLight = Light{{ -2.f, 1.f, 1.5}};

	Camera camera{
		-Vector3f::Forward() * 3.f + Vector3f::Up() * 0.1f,
		70.f
	};

	ConsoleRenderer renderer({30, 30});

	renderer.Render(scene, camera, RenderMode::Color);
}