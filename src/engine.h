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
        struct background { short r = 0x5C, g = 0x94, b = 0xFC; };
        background bg;
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

    float viewportWidth = 256;
    float viewportHeight = 240;
    SDL_Texture* viewportTexture;
    float viewportRatio = 1.066666666;
    SDL_Rect viewport = { 0, 0, 512, 480 };

    SDL_Event event;

    // main loop events
    bool events();
    void physics();
    void render();

    // misc helper functions
    void delay(Uint64& start);
    void resizeViewport(unsigned short width, unsigned short height);
};
