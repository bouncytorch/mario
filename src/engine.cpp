#include "engine.h"
#include <SDL2/SDL_render.h>
#include "SDL3/SDL_events.h"
#include "SDL3/SDL_pixels.h"
#include "SDL3/SDL_rect.h"
#include "SDL3/SDL_render.h"
#include "SDL3/SDL_surface.h"
#include "SDL3/SDL_timer.h"
#include "SDL3/SDL_video.h"
#include "SDL3/SDL_init.h"
#include "logger.h"
#include <cmath>
#include "imgui.h"
#include "backends/imgui_impl_sdl3.h"
#include "backends/imgui_impl_sdlrenderer3.h"

bool Engine::init() 
{
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
    
    m_viewport.texture = SDL_CreateTexture(m_renderer, SDL_PIXELFORMAT_RGB24, SDL_TEXTUREACCESS_TARGET, 256, 240);
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
    
    // IMGUI_CHECKVERSION();
    ImGui::CreateContext();
    ImGuiIO& io = ImGui::GetIO();
    io.ConfigFlags |= ImGuiConfigFlags_NavEnableKeyboard;
    io.ConfigFlags |= ImGuiConfigFlags_NavEnableGamepad;
    ImGui::StyleColorsDark();
    // Setup Platform/Renderer backends
    ImGui_ImplSDL3_InitForSDLRenderer(m_window, m_renderer);
    ImGui_ImplSDLRenderer3_Init(m_renderer);
    
    m_viewport.resize(m_settings.resolution.width, m_settings.resolution.height);
    return true;
}

bool Engine::loop() 
{
    Uint64 start = SDL_GetPerformanceCounter();

    if ( !events() ) return false;
    render(start);

    return true;
}

bool Engine::events() 
{
    while( SDL_PollEvent(&m_event) ) 
    {
        ImGui_ImplSDL3_ProcessEvent(&m_event);
        switch (m_event.type) {
            case SDL_EVENT_WINDOW_CLOSE_REQUESTED:
            case SDL_EVENT_QUIT: 
                logger::log(); // just so it looks better in console
                return false;
            case SDL_EVENT_WINDOW_RESIZED: 
                m_viewport.resize(m_event.window.data1, m_event.window.data2);
                logger::logInfo("EVENTS: Window resized to ", m_event.window.data1, 'x', m_event.window.data2, " Viewport resized to ", m_viewport.rect.w, 'x', m_viewport.rect.h);
                break;
        }
    }
    
    return true;
}

void Engine::render(Uint64& start) 
{
    SDL_RenderClear( m_renderer );

    ImGui_ImplSDLRenderer3_NewFrame();
    ImGui_ImplSDL3_NewFrame();
    ImGui::NewFrame();
    ImGui::Begin("Hello, world!");
    ImGui::End();

    ImGui::Render();

    // draw the following onto the viewport texture
    SDL_SetRenderTarget(m_renderer, m_viewport.texture);

    // draw background color
    // SDL_SetRenderDrawColor(m_renderer, stage->bg.r, stage->bg.g, stage->bg.b, 255);
    // SDL_RenderFillRect( m_renderer, NULL );
    // SDL_SetRenderDrawColor(m_renderer, 0, 0, 0, 255);

    // reset render target
    SDL_SetRenderTarget(m_renderer, NULL);
    SDL_RenderTexture(m_renderer, m_viewport.texture, NULL, &m_viewport.rect);
    
    ImGui_ImplSDLRenderer3_RenderDrawData(ImGui::GetDrawData(), m_renderer);
    SDL_RenderPresent( m_renderer );

    // cap frame to fps
    Uint64 end = SDL_GetPerformanceCounter();
    float elapsed = (end - start) / (float) SDL_GetPerformanceFrequency();
    int delay = (int) (1000 / (m_settings.fps_max - 28)) - elapsed * 1000.0f;
    if (delay > 0) SDL_Delay(delay);
}

Engine::~Engine() 
{
    ImGui_ImplSDLRenderer3_Shutdown();
    ImGui_ImplSDL3_Shutdown();
    ImGui::DestroyContext();
    SDL_Quit(); 
}

void Engine::Viewport::resize(unsigned short width, unsigned short height)
{
    float aspectRatio = (float) width / height;
    if (aspectRatio >= this->ratio) {
        this->rect.h = height;
        this->rect.w = ceilf(height * this->ratio);
        
        this->rect.y = 0;
        this->rect.x = ceilf((float) (width - this->rect.w) / 2);
    }
    else {
        this->rect.w = width;
        this->rect.h = ceilf(width / this->ratio);

        this->rect.x = 0;
        this->rect.y = ceilf((float) (height - this->rect.h) / 2);
    }
}