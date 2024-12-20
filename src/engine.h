#pragma once
#include <SFML/Graphics/RenderWindow.hpp>
#include <SFML/Graphics/View.hpp>
#include <SFML/System/String.hpp>
#include <SFML/Window/VideoMode.hpp>
#include <SFML/Window/WindowEnums.hpp>

class Engine
{
public:
    struct Settings 
    {
        uint16_t fps_max = 165;
        struct {
            uint16_t width  = 256;
            uint16_t height = 240;
        } viewport;
        struct {
            sf::String name = "non-distinct super plumber";
            uint16_t   width  = 512;
            uint16_t   height = 480;
            sf::State  state  = sf::State::Windowed;
        } window;
    };
public:
    Engine(Settings);
    Engine() = default;

    void run();
private:
    Settings m_settings;
    sf::View m_viewport;
    sf::RenderWindow m_window = { 
        sf::VideoMode({ m_settings.window.width, m_settings.window.height }), 
        m_settings.window.name 
    };
private:
    bool events();
    void physics();
    void render();
};

// class Engine 
// {
// public:
//     

// public:
//     Engine(Settings);
//     Engine();
//     ~Engine();
//     operator bool() const;

//     bool loop();
// private:
//     Settings m_settings;
    
//     SDL_Event     m_event;
//     SDL_Window*   m_window = nullptr;
//     SDL_Renderer* m_renderer = nullptr;

//     uint32_t m_desiredNSPerFrame = 1000000000 / m_settings.fps_max;
//     struct Viewport {
//         float ratio;
//         std::optional<Texture> texture;
        
//         void resize(unsigned short, unsigned short);
//     } m_viewport = {
//         (float) m_settings.viewport.width / m_settings.viewport.height
//     };

// private:
// };
