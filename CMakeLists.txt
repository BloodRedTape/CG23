cmake_minimum_required(VERSION 3.10)
project(CG23)

add_library(CG23Core STATIC
	"core/graphics/image.cpp" 
	"core/graphics/color.cpp"
	"core/graphics/image_io/ppm_image_writer.cpp" 
	"core/graphics/image_io/ppm_image_reader.cpp"
	"core/graphics/image_io/image_writer_factory.cpp" 
	"core/graphics/image_io/image_reader_factory.cpp"
	"core/graphics/image_io/bmp_image_writer.cpp"
	"core/graphics/image_io/bmp_image_reader.cpp"
)
target_include_directories(CG23Core PUBLIC "core")
target_compile_features(CG23Core PUBLIC cxx_std_17)


add_executable(CG23RayTracer
	"raytracer/main.cpp"
	"raytracer/render/base_renderer.cpp"
	"raytracer/render/console_renderer.cpp"
	"raytracer/render/image_renderer.cpp"
	"raytracer/render/obj_loader.cpp"
)
target_include_directories(CG23RayTracer PUBLIC "raytracer")
target_link_libraries(CG23RayTracer PRIVATE CG23Core)

add_executable(CG23Converter
	"converter/main.cpp"
)
target_link_libraries(CG23Converter PRIVATE CG23Core)

add_executable(CG23Tests
	"tests/main.cpp"
	"tests/math/sphere.cpp"
	"tests/math/vector3.cpp"
)
set(gtest_force_shared_crt ON)
add_subdirectory(libs/googletest)
target_link_libraries(CG23Tests PRIVATE gtest PRIVATE CG23Core)


