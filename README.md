# sdlario
a platformer game written as a cpp practice piece

## Prerequisites
this project uses **cmake** as it's build system.
you are also required to have **SDL2** preinstalled. this is a temporary measure until i bundle it with the project

## Building
```
git clone https://github.com/bouncytorch/mario
cd mario
mkdir build
cd build
cmake ..
# or, for release builds
cmake .. -DCMAKE_BUILD_TYPE=Release
```