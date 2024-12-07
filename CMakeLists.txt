cmake_minimum_required(VERSION 3.11)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

project("sdlario" LANGUAGES C CXX)

set(SDL_LIBC ON)
set(SDL_VULKAN OFF)
set(SDL_SHARED ON)
set(SDL_STATIC OFF)

set(SDL_TESTS OFF)
set(SDL_TEST_LIBRARY OFF)
add_subdirectory("third-party/SDL3")
add_subdirectory("third-party/SDL3_image")

add_library(imgui
	third-party/imgui/imgui.cpp
	third-party/imgui/imgui_draw.cpp
	third-party/imgui/imgui_tables.cpp
	third-party/imgui/imgui_widgets.cpp
	third-party/imgui/backends/imgui_impl_sdl3.cpp
	third-party/imgui/backends/imgui_impl_sdlrenderer3.cpp
)
target_include_directories(imgui SYSTEM PUBLIC "third-party/SDL3/include" "third-party/imgui")
target_link_libraries(imgui PUBLIC SDL3::SDL3)

file(GLOB MY_SOURCES "src/*.cpp" "src/*.h")
add_executable(${PROJECT_NAME} ${MY_SOURCES})

target_compile_features(${PROJECT_NAME} PRIVATE cxx_std_23)
target_include_directories(${PROJECT_NAME}
	PUBLIC
	"third-party/SDL3/include"
	"third-party/SDL3_image/include"
	"third-party/imgui"
)
target_link_libraries(${PROJECT_NAME}
	PRIVATE SDL3::SDL3 SDL3_image::SDL3_image imgui
)


