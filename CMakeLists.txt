cmake_minimum_required(VERSION 3.25)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR})

project("platformer" LANGUAGES CXX)
set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

if (APPLE)
    set(CMAKE_OSX_ARCHITECTURES x86_64;arm64)
endif()

option(BUILD_SHARED_LIBS "Build shared libraries" OFF)

add_subdirectory("third-party/SFML-3.0.0-rc.2" SYSTEM)

file(GLOB_RECURSE SDLARIO_SOURCES "src/*.cpp" "src/*.h")
add_executable(${PROJECT_NAME} ${SDLARIO_SOURCES})
target_link_libraries(${PROJECT_NAME} PUBLIC sfml-graphics sfml-audio)

# stole this 
if (PROJECT_IS_TOP_LEVEL AND UNIX)
    execute_process(
        COMMAND ${CMAKE_COMMAND} -E create_symlink
            ${CMAKE_BINARY_DIR}/compile_commands.json
            ${CMAKE_CURRENT_SOURCE_DIR}/compile_commands.json
    )
endif()
