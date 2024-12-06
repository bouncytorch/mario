cmake_minimum_required(VERSION 3.11)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

project("sdlario" LANGUAGES C CXX)

set(FORCE_STATIC_VCRT OFF)
set(BUILD_SHARED_LIBS OFF)

set(SDL_LIBC ON)
set(SDL_VULKAN OFF)
set(SDL_SHARED OFF)
set(SDL_STATIC ON)

set(SDL_TESTS OFF)
set(SDL_TEST_LIBRARY OFF)

add_subdirectory("third-party/SDL2")
add_subdirectory("third-party/SDL2_image")

file(GLOB MY_SOURCES "src/*.cpp" "src/*.h")
add_executable("${PROJECT_NAME}" ${MY_SOURCES})

target_compile_features(${PROJECT_NAME} PRIVATE
  PRIVATE
    cxx_std_23
)

target_include_directories("${PROJECT_NAME}" 
PUBLIC 
"third-party/SDL2/include"
"third-party/SDL2_image/include")

target_link_libraries(${PROJECT_NAME}
    # PRIVATE $<TARGET_NAME_IF_EXISTS:SDL2::SDL2main>
    PRIVATE $<IF:$<TARGET_EXISTS:SDL2::SDL2>,SDL2::SDL2,SDL2::SDL2-static>
    SDL2_image
)
