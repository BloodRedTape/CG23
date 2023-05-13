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
#include "utils/args.hpp"
#include "utils/error.hpp"
#include <windows.h>

int main(int argc, const char **argv) {
	std::string obj_path;
	std::string img_path;

	if (!IsDebuggerPresent()) {
		if (argc == 1)
			return Error("Provide --source and --output arguments");

		ArgParse arg_parse[] = {
		{
			"source",
			obj_path
        },
		{
			"output",
			img_path
		}
		};

		int arg_parse_fail = Parse(arg_parse, argc - 1, argv + 1);

		if (arg_parse_fail != -1)
			return Error("Arg % is empty", arg_parse[arg_parse_fail].Name);

		if (!obj_path.size())
			return Error("provide --source argument");

		if (!img_path.size())
			return Error("provide --output argument");
	} else {
		obj_path = "../../../resources/cow.obj";
		img_path = "result.bmp";
	}
	 
	auto cow = ObjLoader().Load(obj_path, Vector3f(), Vector3f(-90, 0, 90));

	if(!cow.IsValue())
		return Error("Can't load % model", obj_path);

	//scene.Objects.push_back(std::make_unique<Sphere>(Vector3f{0, 0, 0}, 0.8f));
	//scene.Objects.push_back(std::make_unique<Sphere>(Vector3f{0, 1, 0}, 0.5f));

	Scene scene;
	scene.Sky = Color::While;
	scene.Objects.push_back(std::make_unique<Plane>(Vector3f(0, -0.3f, 0), Vector3f::Up() ));
	scene.Objects.push_back(std::make_unique<Mesh>(std::move(cow.Value()) ));

	Camera camera{
		-Vector3f::Forward() * 2.f + Vector3f::Up() * 0.1f,
		Vector3f(0, 0, 0),
		70.f
	};

	ImageRenderer renderer({1280, 1280});

	Clock clock;
	size_t samples = 10;
	size_t bounces = 5;
	Image image = renderer.Render(scene, camera, samples, bounces);
	std::cout << "Trace took: " << clock.GetElapsedTime() << std::endl;

	if(image.SaveImageTo(img_path))
		system(("start " + img_path).c_str());
	else
		return Error("Can't save image to %", img_path);
}