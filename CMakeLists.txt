cmake_minimum_required(VERSION 3.11)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

project("sdlario" LANGUAGES C CXX)

set(SDL_LIBC OFF)
set(SDL_VULKAN OFF)
set(SDL_SHARED ON)
set(SDL_STATIC OFF)

set(SDL_TESTS OFF)
set(SDL_TEST_LIBRARY OFF)

add_subdirectory("third-party/SDL2")
add_subdirectory("third-party/SDL2_image")
file(GLOB MY_SOURCES "src/*.cpp" "src/*.h")

add_executable(${PROJECT_NAME} ${MY_SOURCES})

target_compile_features(${PROJECT_NAME} PRIVATE cxx_std_23)

target_include_directories(${PROJECT_NAME}
PUBLIC 
"third-party/SDL2/include"
"third-party/SDL2_image/include")

target_link_libraries(${PROJECT_NAME}
  PRIVATE SDL2main
  PRIVATE SDL2
  PRIVATE SDL2_image
)

