cmake_minimum_required(VERSION 3.11)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

project("sdlario" LANGUAGES C CXX)

file(GLOB MY_SOURCES "src/*.cpp" "src/*.h")
add_executable("${PROJECT_NAME}" ${MY_SOURCES})

add_subdirectory("third-party/SDL2")
target_include_directories("${PROJECT_NAME}" PUBLIC "third-party/SDL2/include")

target_link_libraries("${PROJECT_NAME}"
    PRIVATE 
    SDL2
)