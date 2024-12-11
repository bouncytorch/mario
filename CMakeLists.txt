cmake_minimum_required(VERSION 3.25)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR})
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR})

project("sdlario" LANGUAGES C CXX)
set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

set(SDL_SHARED ON)
set(SDL_STATIC OFF)
set(SDL_TESTS OFF)
set(SDL_TEST_LIBRARY OFF)
if (APPLE)
    enable_language(OBJC)
endif()

option(SDLARIO_VENDORED "Use SDL3 provided in ./third-party" ON)
if(SDLARIO_VENDORED)
    add_subdirectory("third-party/SDL3" SYSTEM)
	add_subdirectory("third-party/SDL3_image" SYSTEM)
else()
    find_package("SDL3" REQUIRED CONFIG REQUIRED COMPONENTS "SDL3-shared")
    find_package("SDL3_image" REQUIRED CONFIG REQUIRED COMPONENTS "SDL3_image-shared")
endif()

file(GLOB_RECURSE SDLARIO_SOURCES "src/*.cpp" "src/*.h")
add_executable(${PROJECT_NAME} ${SDLARIO_SOURCES})
target_link_libraries(${PROJECT_NAME} SDL3::SDL3 SDL3_image::SDL3_image)

# stole this 
if (PROJECT_IS_TOP_LEVEL AND UNIX)
    execute_process(
        COMMAND ${CMAKE_COMMAND} -E create_symlink
            ${CMAKE_BINARY_DIR}/compile_commands.json
            ${CMAKE_CURRENT_SOURCE_DIR}/compile_commands.json
    )
endif()
