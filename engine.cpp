#include "engine.h"
#include "logger.h"
#include <SDL2/SDL_events.h>
#include <SDL2/SDL_rect.h>
#include <SDL2/SDL_render.h>
#include <SDL2/SDL_surface.h>
#include <SDL2/SDL_video.h>
#include <cmath>

bool Engine::init() {
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

    renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
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

    viewport = { 0, 0, 320, 240 };
    viewportRatio = (float) viewport.w / viewport.h;

    SDL_ShowWindow(window);
    return true;
}

bool Engine::loop() {
    while( SDL_PollEvent(&event) ) 
        switch (event.type) {
            case SDL_QUIT: 
                logger::log(); // just so it looks better in console
                return false;
            case SDL_WINDOWEVENT: switch (event.window.event) {
                case SDL_WINDOWEVENT_CLOSE: return false;
                case SDL_WINDOWEVENT_RESIZED:
                    float aspectRatio = (float) event.window.data1 / event.window.data2;
                    logger::log(aspectRatio, " ", viewportRatio);
                    if (aspectRatio >= viewportRatio) {
                        viewport.h = event.window.data2;
                        viewport.w = ceilf(event.window.data2 * viewportRatio);
                        
                        viewport.y = 0;
                        viewport.x = ceilf((float) (event.window.data1 - viewport.w) / 2);
                    }
                    else {
                        viewport.w = event.window.data1;
                        viewport.h = ceilf(event.window.data1 / viewportRatio);

                        viewport.x = 0;
                        viewport.y = ceilf((float) (event.window.data2 - viewport.h) / 2);
                    }
                    break;
            }
        }
    
    SDL_RenderClear( renderer );

    SDL_SetRenderDrawColor(renderer, 30, 30, 30, 255);
    SDL_RenderFillRect(renderer, &viewport);
    SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);

    SDL_RenderPresent( renderer );

    return true;
}

Engine::~Engine() { SDL_Quit(); }