#include "engine.h"
#include "logger.h"
#include <SDL.h>
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

    surface = SDL_GetWindowSurface(window);
    if ( !surface ) 
    {
        logger::logErr("Failed to load window surface. Error: ", SDL_GetError());
        return false;
    }

    SDL_ShowWindow(window);
    return true;
}

bool Engine::loop() 
{
    Uint64 start = SDL_GetPerformanceCounter();

    while( SDL_PollEvent(&event) ) 
        switch (event.type) {
            case SDL_QUIT: 
                logger::log(); // just so it looks better in console
                return false;
            case SDL_WINDOWEVENT: switch (event.window.event) {
                case SDL_WINDOWEVENT_CLOSE: return false;
                case SDL_WINDOWEVENT_RESIZED:
                    resizeViewport(event.window.data1, event.window.data2);
                    break;
            }
        }

    render();
    

    delay(start);
    return true;
}

void Engine::delay(Uint64& start) {
    Uint64 end = SDL_GetPerformanceCounter();
    float elapsed = (end - start) / (float)SDL_GetPerformanceFrequency();
    int delay = (int) (1000 / (settings.fps_max - 28)) - elapsed * 1000.0f;
    if (delay > 0) SDL_Delay(delay);
}

void Engine::render() {
    SDL_RenderClear( renderer );

    SDL_SetRenderDrawColor(renderer, 30, 30, 30, 255);
    SDL_RenderFillRect(renderer, &viewport);
    SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);

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