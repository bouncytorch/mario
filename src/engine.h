#pragma once
#include "texture/texture.h"
#include "SDL3/SDL_render.h"
#include "SDL3/SDL_events.h"
#include <SDL3/SDL_init.h>
#include <SDL3/SDL_video.h>
#include <string>

class Engine 
{
public:
    struct Settings 
    {
        unsigned short fps_max = 165;
        struct {
            unsigned short width = 256;
            unsigned short height = 240;
        } viewport;
        struct {
            std::string name;
            unsigned short width = 512;
            unsigned short height = 480;
            SDL_WindowFlags flags = SDL_WINDOW_RESIZABLE;
        } window;

        operator bool() const;
    };

public:
    Engine(Settings);
    Engine();
    ~Engine();
    operator bool() const;

    bool loop();
private:
    const bool c_init = false;
    Settings m_settings;
    
    SDL_Event m_event;
    SDL_Window* m_window = nullptr;
    SDL_Renderer* m_renderer = nullptr;

    struct Viewport {
        float ratio;
        std::optional<Texture> texture;
        
        void resize(unsigned short, unsigned short);
    } m_viewport = {
        (float)m_settings.viewport.width / m_settings.viewport.height
    };

private:
    bool events();
    void physics();
    void render(uint64_t& start);
};
