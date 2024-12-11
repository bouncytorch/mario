#include "engine.h"
#include <SDL3/SDL_init.h>
#include <SDL3/SDL_rect.h>
#include <SDL3/SDL_render.h>
#include <SDL3/SDL_timer.h>
#include <SDL3_image/SDL_image.h>
#include "logger.h"

Engine::Engine() {}

Engine::Engine(Engine::Settings settings)
: m_settings(settings)
{}

bool Engine::Settings::validate() const
{
    if (!this->fps_max) 
    {
        logger::logWarn("[Settings]: Max FPS invalid");
        return false;
    }

    if (!this->resolution.height || !this->resolution.width) 
    {
        logger::logWarn("[Settings]: Window size invalid");
        return false;
    }

    if (!this->viewport.width || !this->viewport.height)
    {
        logger::logWarn("[Settings]: Viewport size invalid");
        return false;
    }

    return true;
}

// TEMP!!!
SDL_Texture* wow;
// TEMP!!!
bool Engine::init() 
{
    if (!m_settings.validate())
    {
        logger::logErr("Invalid settings provided.");
        return false;
    }

    if ( !SDL_Init(SDL_INIT_VIDEO | SDL_INIT_EVENTS) ) 
    {
        logger::logErr("Failed to initialize SDL. Error: ", SDL_GetError());
        return false;
    }

    SDL_CreateWindowAndRenderer("SDLario", m_settings.resolution.width, m_settings.resolution.height, SDL_WINDOW_RESIZABLE, &m_window, &m_renderer);
    if ( !m_renderer || !m_window ) 
    {
        logger::logErr("Failed to create renderer. Error: ", SDL_GetError());
        return false;
    }   
    
    m_viewport.texture = SDL_CreateTexture(m_renderer, SDL_PIXELFORMAT_RGB24, SDL_TEXTUREACCESS_TARGET, m_settings.viewport.width, m_settings.viewport.height);
    if ( !m_viewport.texture )
    {
        logger::logErr("Failed to create viewport. Error: ", SDL_GetError());
        return false;
    }

    if ( !SDL_SetTextureScaleMode(m_viewport.texture, SDL_SCALEMODE_NEAREST) )
    {
        logger::logErr("Failed to set viewport scale to nearest. Error: ", SDL_GetError());
        return false;
    }

    // TEMP!!!
    wow = IMG_LoadTexture(m_renderer, "mario.bmp");
    // TEMP!!!

    m_viewport.resize(m_settings.resolution.width, m_settings.resolution.height);
    return true;
}

bool Engine::loop() 
{
    Uint64 start = SDL_GetPerformanceCounter();

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
                logger::log(); // just so it looks better in console
            case SDL_EVENT_WINDOW_CLOSE_REQUESTED:
                return false;
            case SDL_EVENT_WINDOW_RESIZED: 
                m_viewport.resize(m_event.window.data1, m_event.window.data2);
                logger::logInfo("EVENTS: Window resized to ", m_event.window.data1, 'x', m_event.window.data2, " Viewport resized to ", m_viewport.rect.w, 'x', m_viewport.rect.h);
                break;
        }
    }
    
    return true;
}

int dirx = 1, diry = 1;
SDL_FRect w = { 0, 60, 16, 16 };
void Engine::physics() 
{
    // TEMP!!!
    if (w.x + w.w-2 == m_settings.viewport.width) dirx = -1;
    else if (w.x == -2) dirx = 1;

    if (w.y + w.h == m_settings.viewport.height) diry = -1;
    else if (w.y == 0) diry = 1;

    w.x += dirx;
    w.y += diry;
    // TEMP!!!
}

void Engine::render(Uint64& start) 
{
    SDL_RenderClear( m_renderer );
    // draw the following onto the viewport texture
    SDL_SetRenderTarget(m_renderer, m_viewport.texture);

    // draw background color
    // TODO: HARDCODED FOR NOW. When stages are added, will draw stage bg color.
    SDL_SetRenderDrawColor(m_renderer, 0x5C, 0x94, 0xFC, 255);
    SDL_RenderFillRect( m_renderer, NULL );
    SDL_SetRenderDrawColor(m_renderer, 0, 0, 0, 255);

    //TEMP!!!
    SDL_RenderTexture(m_renderer, wow, NULL, &w);
    //TEMP!!!

    // reset render target
    SDL_SetRenderTarget(m_renderer, NULL);
    SDL_RenderTexture(m_renderer, m_viewport.texture, NULL, &m_viewport.rect);
    SDL_RenderPresent( m_renderer );

    // cap frame to fps
    Uint64 end = SDL_GetPerformanceCounter();
    float elapsed = (end - start) / (float) SDL_GetPerformanceFrequency();
    int delay = (int) (1000 / m_settings.fps_max) - elapsed * 1000.0f;
    if (delay > 0) SDL_Delay(delay);
}

Engine::~Engine() 
{
    SDL_Quit(); 
}

void Engine::Viewport::resize(unsigned short width, unsigned short height)
{
    float aspectRatio = (float) width / height;
    if (aspectRatio >= this->ratio) {
        this->rect.h = height;
        this->rect.w = (height * this->ratio);
        
        this->rect.y = 0;
        this->rect.x = (width - this->rect.w) / 2;
    }
    else {
        this->rect.w = width;
        this->rect.h = width / this->ratio;

        this->rect.x = 0;
        this->rect.y = (height - this->rect.h) / 2;
    }
}