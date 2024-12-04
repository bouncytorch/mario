# sdlario
a platformer game written as a cpp practice piece

## Prerequisites
this project uses **premake5** as it's build system. you can download pre-build binaries on the [official website.](https://premake.github.io/download)
you are also required to have **SDL2** preinstalled. this is a temporary measure until i bundle it with the project

## Building
```
git clone https://github.com/bouncytorch/mario
cd mario
```
all further os-specific commands assume you're in the repo directory. they also assume premake5 binary is located somewhere on your PATH
### Linux
```
premake5 gmake2
make
```
### Windows
generate a visual studio solution using the following command:
```
premake5 vs2022 # or specify the version yourself
```
and then build inside the IDE
### OSX
generate an xcode4 project using the following command:
```
premake5 xcode4
```
and then build inside the IDE
