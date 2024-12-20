#include "engine.h"
#include "logger.h"
#include <SFML/Graphics/Color.hpp>
#include <SFML/Graphics/Drawable.hpp>

// // SETTINGS
// Engine::Settings::operator bool() const
// {
//     return fps_max
//         && window.height  && window.width
//         && viewport.width && viewport.height;
// }

// // VIEWPORT
// void Engine::Viewport::resize(unsigned short width, unsigned short height)
// {
//     float aspectRatio = (float) width / height;
//     if (aspectRatio >= ratio) {
//         texture->projection.w = height * ratio;
//         texture->projection.h = height;
//         texture->projection.x = (width - texture->projection.w) / 2;
//         texture->projection.y = 0;
//     }
//     else {
//         texture->projection.w = width;
//         texture->projection.h = width / ratio;
//         texture->projection.x = 0;
//         texture->projection.y = (height - texture->projection.h) / 2;
//     }
// }

Engine::Engine(Settings settings)
: m_settings(settings)
{
    m_window.setFramerateLimit(m_settings.fps_max);
}

void Engine::run() 
{
    while (m_window.isOpen())
    {
        if ( !events() ) break;
        physics();
        render();
    }
}

bool Engine::events() 
{
    return true;
}

void Engine::physics() 
{

}

void Engine::render() 
{
    m_window.clear(sf::Color::Black);

    m_window.display();
}