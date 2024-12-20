# sdlario
a platformer game written as a cpp practice piece

## Prerequisites
this project uses **cmake** as it's build system.
this project includes source files for **SFML**, which (on linux) depend upon the following packages (taken from [SFML Docs](https://www.sfml-dev.org/tutorials/3.0/getting-started/cmake/)):

> On Ubuntu or other Debian-based OSes, that can be done with the commands below. A similar process will be required for non-Debian Linux distributions like Fedora.
>```
>sudo apt update
>sudo apt install \
>     libxrandr-dev \
>     libxcursor-dev \
>     libudev-dev \
>     libflac-dev \
>     libvorbis-dev \ 
>     libgl1-mesa-dev \
>     libegl1-mesa-dev \
>     libdrm-dev \
>     libgbm-dev
>```

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