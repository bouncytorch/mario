# sdlario
a platformer game written as a cpp practice piece

## Prerequisites
this project uses **cmake** as it's build system.
this project includes source files for **SDL3** and **SDL3_image**, which (on linux) depend upon the following packages (taken from [SDL3 Docs](https://wiki.libsdl.org/SDL3/README/linux)):

> Ubuntu 18.04, all available features enabled:
>```
>sudo apt-get install build-essential git make \
>pkg-config cmake ninja-build gnome-desktop-testing libasound2-dev libpulse-dev \
>libaudio-dev libjack-dev libsndio-dev libx11-dev libxext-dev \
>libxrandr-dev libxcursor-dev libxfixes-dev libxi-dev libxss-dev \
>libxkbcommon-dev libdrm-dev libgbm-dev libgl1-mesa-dev libgles2-mesa-dev \
>libegl1-mesa-dev libdbus-1-dev libibus-1.0-dev libudev-dev fcitx-libs-dev 
>```
>Ubuntu 22.04+ can also add `libpipewire-0.3-dev libwayland-dev libdecor-0-dev liburing-dev` to that command line.

>Fedora 35, all available features enabled:
>```
>sudo yum install gcc git-core make cmake \
>alsa-lib-devel pulseaudio-libs-devel nas-devel pipewire-devel \
>libX11-devel libXext-devel libXrandr-devel libXcursor-devel libXfixes-devel \
>libXi-devel libXScrnSaver-devel dbus-devel ibus-devel fcitx-devel \
>systemd-devel mesa-libGL-devel libxkbcommon-devel mesa-libGLES-devel \
>mesa-libEGL-devel vulkan-devel wayland-devel wayland-protocols-devel \
>libdrm-devel mesa-libgbm-devel libusb-devel libdecor-devel \
>pipewire-jack-audio-connection-kit-devel
>```
>Fedora 39+ can also add `liburing-devel` to that command line.

SDL also provides specifics in regards to your own platform of choice in their [README](https://wiki.libsdl.org/SDL3/README/FrontPage).
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