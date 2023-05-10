#include <cstdio>
#include <iostream>

#include "render/image_renderer.hpp"
#include "primitives/sphere.hpp"
#include "primitives/plane.hpp"
#include "graphics/image.hpp"
#include "utils/clock.hpp"
#include "primitives/mesh.hpp"
#include "render/obj_loader.hpp"
#include "math/transform.hpp"

int main() {

	

	auto cow = ObjLoader().Load("../../../resources/cow.obj",Vector3f(), Vector3f(-90, 0, 90));

	assert(cow.IsValue());

	Scene scene;
	//scene.Objects.push_back(std::make_unique<Sphere>(Vector3f{0, 0, 0}, 0.8f));
	//scene.Objects.push_back(std::make_unique<Sphere>(Vector3f{0, 1, 0}, 0.5f));
	scene.Objects.push_back(std::make_unique<Plane>(Vector3f(0, -0.5f, 0), Vector3f::Up() ));
	scene.Objects.push_back(std::make_unique<Mesh>(std::move(cow.Value()) ));

	scene.PointLight = Light{{ -2.f, 1.f, 1.5}};

	Camera camera{
		-Vector3f::Forward() * 2.f + Vector3f::Up() * 0.1f,
		Vector3f(0, 0, 0),
		70.f
	};

	ImageRenderer renderer({500, 500});

	Clock clock;
	Image image = renderer.Render(scene, camera, DebugRenderMode::Color);
	std::cout << "Trace took: " << clock.GetElapsedTime() << std::endl;

	if(image.SaveImageTo("result.bmp"))
		system("start result.bmp");
	else
		puts("Can't save file");
}