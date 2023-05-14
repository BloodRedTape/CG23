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

struct RenderSettings {
	Vector2s Resolution;
	size_t Samples;
	size_t Bounces;
};

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

	MaterialProperties gold;
	gold.Roughness = 1;
	gold.Color = Color(101, 148, 68, 255);

	MaterialProperties rough_metal;
	rough_metal.Roughness = 0.2;
	rough_metal.Color = Color(200, 200, 200, 255);

	MaterialProperties metal;
	metal.Roughness = 0;
	metal.Color = Color(200, 200, 200, 255);

	MaterialProperties red_plastic;
	red_plastic.Color = Color(61, 152, 255, 255);

	Color nice_blue(51, 102, 232, 255);
	Color nice_red(255, 74, 61, 255);

	MaterialProperties blue_light_mat;
	blue_light_mat.Color = Color::Black;
	blue_light_mat.EmissionColor = nice_blue;
	blue_light_mat.EmissionStrength = 3.f;

	MaterialProperties red_light_mat;
	red_light_mat.Color = Color::Black;
	red_light_mat.EmissionColor = nice_red;
	red_light_mat.EmissionStrength = 3.f;

	MaterialProperties yellow_light_mat;
	yellow_light_mat.Color = Color::Black;
	yellow_light_mat.EmissionColor = Color(245, 229, 86, 255);
	yellow_light_mat.EmissionStrength = 3.f;

	

	Scene scene;
	bool is_night = true;
	scene.Sky = is_night ? Color(14, 56, 74, 255) : Color(115, 227, 250, 255);
	scene.Objects.push_back(std::make_unique<Plane>(Vector3f(0, -0.3f, 0), Vector3f::Up(), gold));

	cow.Value().SetMaterial(red_plastic);
	scene.Objects.push_back(std::make_unique<Mesh>(std::move(cow.Value()) ));

	scene.Objects.push_back(std::make_unique<Sphere>(Vector3f{ -0.4f, 1.f, 0.8f}, 0.3f, yellow_light_mat));
	scene.Objects.push_back(std::make_unique<Sphere>(Vector3f{ -0.4f, 1.f, -0.8f}, 0.3f, red_light_mat));

	scene.Objects.push_back(std::make_unique<Sphere>(Vector3f{ -0.4f, 0, -0.9f}, 0.5f, metal));
	scene.Objects.push_back(std::make_unique<Sphere>(Vector3f{ -0.4f, 0, 0.9f}, 0.5f, rough_metal));
	//scene.Objects.push_back(std::make_unique<Sphere>(Vector3f{ -0.4f, 1.f, 0.8f}, 0.5f, blue_light_mat));

	Camera camera{
		-Vector3f::Forward() * 2.f + Vector3f::Up() * 0.1f,
		Vector3f(0, 0, 0),
		70.f
	};
#define NICE

	RenderSettings settings;
#ifdef NICE
	settings.Resolution = {1920, 1920};
	settings.Samples = 100;
	settings.Bounces = 10;
#else
	settings.Resolution = {800, 800};
	settings.Samples = 10;
	settings.Bounces = 5;
#endif

	ImageRenderer renderer(settings.Resolution);

	Clock clock;
	Image image = renderer.Render(scene, camera, settings.Samples, settings.Bounces);
	std::cout << "Trace took: " << clock.GetElapsedTime() << std::endl;

	if(image.SaveImageTo(img_path))
		system(("start " + img_path).c_str());
	else
		return Error("Can't save image to %", img_path);
}