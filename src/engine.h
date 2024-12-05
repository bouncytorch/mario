#pragma once
#include <SDL.h>

class Engine 
{
public:
    struct Settings {
        unsigned short fps_max;
    };

    bool init();
    bool loop();
    ~Engine();
private:
    Settings settings = { 165 };

    SDL_Window* window;
    SDL_Renderer* renderer;
    SDL_Surface* surface;

    SDL_Surface* temp;
    SDL_Rect viewport = { 0, 0, 640, 480 };
    float viewportRatio = 1.33333;

    SDL_Event event;

    // main loop events
    void events();
    void physics();
    void render();

    // misc helper functions
    void delay(Uint64& start);
    void resizeViewport(unsigned short width, unsigned short height);
};
