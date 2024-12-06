#include "engine.h"
#include "SDL.h"
#include "logger.h"
#include <cmath>

bool Engine::init() 
{
    if ( SDL_Init(SDL_INIT_VIDEO | SDL_INIT_EVENTS) ) 
    {
        logger::logErr("Failed to initialize SDL. Error: ", SDL_GetError());
        return false;
    }

    window = SDL_CreateWindow("SDLario", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, 640, 480, SDL_WINDOW_HIDDEN | SDL_WINDOW_RESIZABLE);
    if ( !window ) 
    {
        logger::logErr("Failed to create window. Error: ", SDL_GetError());
        return false;
    }

    renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
    if ( !renderer ) 
    {
        logger::logErr("Failed to create renderer. Error: ", SDL_GetError());
        return false;
    }

    temp = Object::load(renderer, viewport, "world.bmp");

    SDL_ShowWindow(window);
    return true;
}

bool Engine::loop() 
{
    Uint64 start = SDL_GetPerformanceCounter();

    if ( !events() ) return false;
    render();

    delay(start);
    return true;
}

void Engine::delay(Uint64& start) {
    Uint64 end = SDL_GetPerformanceCounter();
    float elapsed = (end - start) / (float) SDL_GetPerformanceFrequency();
    int delay = (int) (1000 / (settings.fps_max - 28)) - elapsed * 1000.0f;
    if (delay > 0) SDL_Delay(delay);
}

bool Engine::events() {
    while( SDL_PollEvent(&event) ) 
        switch (event.type) {
            case SDL_QUIT: 
                logger::log(); // just so it looks better in console
                return false;
            case SDL_WINDOWEVENT: switch (event.window.event) {
                case SDL_WINDOWEVENT_CLOSE: return false;
                case SDL_WINDOWEVENT_RESIZED:
                    logger::logInfo("EVENTS: Window resized to ", event.window.data1, 'x', event.window.data2);
                    resizeViewport(event.window.data1, event.window.data2);
                    break;
            }
        }

    return true;
}

void Engine::render() {
    SDL_RenderClear( renderer );

    // settings background
    SDL_SetRenderDrawColor(renderer, map->background >> 16, (map->background >> 8) & 0xFF, map->background & 0xFF, 255);
    SDL_RenderFillRect( renderer, &viewport );
    SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
    temp->draw();

    SDL_RenderPresent( renderer );
}

void Engine::resizeViewport(unsigned short width, unsigned short height) 
{
    float aspectRatio = (float) width / height;
    if (aspectRatio >= viewportRatio) {
        viewport.h = height;
        viewport.w = ceilf(height * viewportRatio);
        
        viewport.y = 0;
        viewport.x = ceilf((float) (width - viewport.w) / 2);
    }
    else {
        viewport.w = width;
        viewport.h = ceilf(width / viewportRatio);

        viewport.x = 0;
        viewport.y = ceilf((float) (height - viewport.h) / 2);
    }
}

Engine::~Engine() { 
    SDL_Quit(); 
}