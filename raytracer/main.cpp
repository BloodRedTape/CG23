#include <cstdio>
#include <iostream>

#include "render/image_renderer.hpp"
#include "math/sphere.hpp"
#include "math/plane.hpp"
#include "graphics/image.hpp"
#include "utils/clock.hpp"

int main() {
	Scene scene;
	scene.Objects.push_back(std::make_unique<Sphere>(Vector3f{0, 0, 0}, 0.8f));
	scene.Objects.push_back(std::make_unique<Sphere>(Vector3f{0, 1, 0}, 0.5f));
	scene.Objects.push_back(std::make_unique<Plane>(Vector3f(0, -0.5f, 0), Vector3f::Up() ));

	scene.PointLight = Light{{ -2.f, 1.f, 1.5}};

	Camera camera{
		-Vector3f::Forward() * 3.f + Vector3f::Up() * 0.1f,
		70.f
	};

	ImageRenderer renderer({720, 720});

	Clock clock;
	Image image = renderer.Render(scene, camera);
	std::cout << "Trace took: " << clock.GetElapsedTime() << std::endl;

	if(image.SaveImageTo("result.bmp"))
		system("start result.bmp");
	else
		puts("Can't save file");
}