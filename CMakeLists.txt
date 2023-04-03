project(CG23)


add_executable(CG23
	"sources/main.cpp"
)

target_include_directories(CG23 PUBLIC "sources")

target_compile_features(CG23 PRIVATE cxx_std_17)

