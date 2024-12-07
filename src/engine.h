#pragma once
#include "SDL3/SDL_render.h"
#include "SDL3/SDL_events.h"

class Engine 
{
public:
    struct Settings {
        unsigned short fps_max;
        struct {
            unsigned short width;
            unsigned short height;
        } resolution;
    };

    // struct Stage {
    //     char background_r = 0x5C;
    //     char background_g = 0x94;
    //     char background_b = 0xFC;
    // };

    bool init();
    bool loop();
    ~Engine();
private:
    Settings m_settings = { 165, { 512, 480 } };

    // Stage* m_stage = new Stage();

    SDL_Event m_event;
    SDL_Window* m_window;
    SDL_Renderer* m_renderer;

    struct Viewport {
        unsigned short width = 256;
        unsigned short height = 240;
        float ratio = 1.066666666;
        SDL_Texture* texture;
        SDL_FRect rect = { 0, 0 };

        void resize(unsigned short width, unsigned short height);
    } m_viewport;

    // main loop events
    bool events();
    void physics();
    void render(Uint64& start);
};
