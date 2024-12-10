#pragma once
#include "SDL3/SDL_render.h"
#include "SDL3/SDL_events.h"

class Engine 
{
public:
    struct Settings {        
        unsigned short fps_max = 165;
        struct {
            unsigned short width = 512;
            unsigned short height = 480;
        } resolution;
        struct {
            unsigned short width = 256;
            unsigned short height = 240;
        } viewport;

        bool validate() const;
    };

    Engine();
    Engine(Settings settings);
    ~Engine();

    bool init();
    bool loop();
private:
    SDL_Event m_event;
    SDL_Window* m_window;
    SDL_Renderer* m_renderer;

    const Settings m_settings;
    struct Viewport {
        float ratio;
        SDL_FRect rect;
        SDL_Texture* texture;

        void resize(unsigned short width, unsigned short height);
    } m_viewport = {
        (float)m_settings.viewport.width / m_settings.viewport.height,
        { 0, 0 }
    };

    // main loop events
    bool events();
    void physics();
    void render(Uint64& start);
};
