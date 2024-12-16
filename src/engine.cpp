#include "engine.h"
#include <SDL3/SDL_error.h>
#include <SDL3/SDL_init.h>
#include <SDL3/SDL_pixels.h>
#include <SDL3/SDL_rect.h>
#include <SDL3/SDL_render.h>
#include <SDL3/SDL_timer.h>
#include <SDL3/SDL_video.h>
#include <SDL3_image/SDL_image.h>
#include <optional>
#include "logger.h"

// SETTINGS
Engine::Settings::operator bool() const
{
    return this->fps_max
        && this->window.height && this->window.width
        && this->viewport.width && this->viewport.height;
}

// VIEWPORT
void Engine::Viewport::resize(unsigned short width, unsigned short height)
{
    float aspectRatio = (float) width / height;
    float w, h, x, y;
    if (aspectRatio >= ratio) {
        w = (height * ratio);
        h = height;
        x = (width - w) / 2;
        y = 0;
    }
    else {
        w = width;
        h = width / ratio;
        x = 0;
        y = (height - h) / 2;
    }

    texture->projection(w, h, x, y);
}

// ENGINE
Engine::Engine(Settings settings)
: m_settings(settings)
{
    if ( !m_settings )
    {
        LOGERROR("Invalid settings");
        return;
    }

    if ( !SDL_Init(SDL_INIT_VIDEO | SDL_INIT_AUDIO | SDL_INIT_EVENTS | SDL_INIT_GAMEPAD) ) 
    {
        LOGERROR("SDL initialization failed. Error: ", SDL_GetError());
        return;
    }

    m_window = SDL_CreateWindow(
        m_settings.window.name.c_str(), 
        m_settings.window.width, 
        m_settings.window.height, 
        m_settings.window.flags
    );
    if (!m_window)
    {
        LOGERROR("Failed to create window. Error: ", SDL_GetError());
        return;
    }

    m_renderer = SDL_CreateRenderer(m_window, nullptr);
    if (!m_renderer)
    {
        LOGERROR("Failed to create renderer. Error: ", SDL_GetError());
        return;
    }
    
    m_viewport.texture.emplace(m_renderer);
    if (!m_viewport.texture)
    {
        LOGERROR("Failed to create viewport texture. Error: ", SDL_GetError());
        return;
    }

    m_viewport.resize(m_settings.window.width, m_settings.window.height);
}

Engine::Engine()
: Engine((Settings) {})
{}

Engine::~Engine() 
{
    SDL_DestroyRenderer(m_renderer);
    SDL_DestroyWindow(m_window);
    SDL_Quit(); 
}

Engine::operator bool() const
{
    return m_window && m_renderer && m_viewport.texture;
}

bool Engine::loop() 
{
    uint64_t start = SDL_GetPerformanceCounter();

    if ( !events() ) return false;
    physics();
    render(start);

    return true;
}

bool Engine::events() 
{
    while( SDL_PollEvent(&m_event) ) 
    {
        switch (m_event.type) 
        {
            case SDL_EVENT_QUIT:
            case SDL_EVENT_WINDOW_CLOSE_REQUESTED:
                LOGINFO("Close requested");
                return false;
            case SDL_EVENT_WINDOW_RESIZED: 
                m_viewport.resize(m_event.window.data1, m_event.window.data2);
                LOGINFO("Window resized to ", m_event.window.data1, 'x', m_event.window.data2);
                break;
        }
    }

    return true;
}

void Engine::physics() 
{

}

void Engine::render(uint64_t& start) 
{
    SDL_RenderClear( m_renderer );
    // draw the following onto the viewport texture
    m_viewport.texture->target();

    // draw background color
    // TODO: HARDCODED FOR NOW. When stages are added, will draw stage bg color.
    SDL_SetRenderDrawColor(m_renderer, 0x5C, 0x94, 0xFC, 255);
    SDL_RenderFillRect( m_renderer, nullptr );
    SDL_SetRenderDrawColor(m_renderer, 0, 0, 0, 255);

    // reset render target and render viewport texture
    SDL_SetRenderTarget(m_renderer, nullptr);
    m_viewport.texture->draw();
    SDL_RenderPresent( m_renderer );

    // cap frame to fps
    double elapsed = (SDL_GetPerformanceCounter() - start) / (double) SDL_GetPerformanceFrequency();
    int delay = (int) (1000 / m_settings.fps_max) - elapsed * 1000.0f;
    if (delay > 0) SDL_Delay(delay);
    // LOGINFO("FPS: ", 1.0 / ((SDL_GetPerformanceCounter() - start) / (double) SDL_GetPerformanceFrequency()));
}