#include "texture.h"
#include <SDL3/SDL_error.h>
#include <SDL3/SDL_pixels.h>
#include <SDL3/SDL_rect.h>
#include <SDL3/SDL_render.h>
#include <SDL3_image/SDL_image.h>
#include <filesystem>
#include "../logger.h"

Texture::Texture(SDL_Renderer*& renderer, float width, float height, std::optional<SDL_FRect> projection, std::optional<SDL_FRect> crop)
: m_renderer(renderer),
    m_projection(projection.value_or((SDL_FRect) { 0, 0, width, height })), 
    m_crop(crop.value_or((SDL_FRect) { 0, 0, width, height })),
    m_texture(SDL_CreateTexture(renderer, SDL_PIXELFORMAT_RGB24, SDL_TEXTUREACCESS_TARGET, width, height))
{
    if (!m_texture)
    {
        LOGWARN("[TEXTURE] Couldn't create texture. Error: ", SDL_GetError());
    }
}

Texture::Texture(SDL_Renderer*& renderer, std::filesystem::path path, std::optional<SDL_FRect> projection, std::optional<SDL_FRect> crop)
: m_renderer(renderer),
    m_texture(IMG_LoadTexture(renderer, path.c_str()))
{
    if (!m_texture)
    {
        LOGWARN("[TEXTURE] Couldn't create texture. Error: ", SDL_GetError());
    }
}

Texture::operator bool() const
{
    return m_texture;
}

Texture::~Texture()
{ SDL_DestroyTexture(m_texture); }

void Texture::target() const
{ SDL_SetRenderTarget(m_renderer, m_texture); }

void Texture::draw() const
{ SDL_RenderTexture(m_renderer, m_texture, &m_crop, &m_projection); }

SDL_FRect Texture::projection() const
{ return m_projection; }

void Texture::projection(std::optional<float> width, std::optional<float> height, std::optional<float> x, std::optional<float> y)
{ 
    m_projection = { 
        x.value_or(m_projection.x), 
        y.value_or(m_projection.y), 
        width.value_or(m_projection.w), 
        height.value_or(m_projection.h) 
    };
} 

SDL_FRect Texture::crop() const
{ return m_crop; }

void Texture::crop(std::optional<float> width, std::optional<float> height, std::optional<float> x, std::optional<float> y)
{ 
    m_projection = { 
        x.value_or(m_projection.x), 
        y.value_or(m_projection.y), 
        width.value_or(m_projection.w), 
        height.value_or(m_projection.h) 
    };
} 