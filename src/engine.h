#pragma once
#include "SDL_render.h"
#include "SDL_events.h"
#include "object.h"

class Engine 
{
public:
    struct Settings {
        unsigned short fps_max;
    };

    struct Map {
        unsigned long background = 0x5C94FC;
    };

    bool init();
    bool loop();
    ~Engine();
private:
    //temp
    Object* temp;
    Map* map = new Map();

    Settings settings = { 165 };

    SDL_Window* window;
    SDL_Renderer* renderer;

    SDL_Texture* viewportT;
    float viewportRatio = 1.33333;
    SDL_Rect viewport = { 0, 0, 640, 480 };

    SDL_Event event;

    // main loop events
    bool events();
    void physics();
    void render();

    // misc helper functions
    void delay(Uint64& start);
    void resizeViewport(unsigned short width, unsigned short height);
};
