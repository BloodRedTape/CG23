project(CG23)

set(gtest_force_shared_crt ON)
add_subdirectory(libs/googletest)

add_executable(CG23
	"sources/main.cpp"
	"tests/core/math/vector3.cpp"
 "tests/core/math/sphere.cpp")

target_include_directories(CG23 PUBLIC "sources")

target_link_libraries(CG23 PRIVATE gtest)

target_compile_features(CG23 PRIVATE cxx_std_17)

