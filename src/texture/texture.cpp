#include "texture.h"
#include <SDL3/SDL_error.h>
#include <SDL3/SDL_pixels.h>
#include <SDL3/SDL_rect.h>
#include <SDL3/SDL_render.h>
#include <SDL3_image/SDL_image.h>
#include <filesystem>
#include <optional>
#include "../logger.h"

std::optional<Texture> Texture::create(SDL_Renderer* renderer, float width, float height, std::optional<SDL_FRect> projection, std::optional<SDL_FRect> crop)
{
    SDL_Texture* texture = SDL_CreateTexture(renderer, SDL_PIXELFORMAT_RGB24, SDL_TEXTUREACCESS_TARGET, width, height);
    if (!texture)
    {
        LOGERROR("[TEXTURE] Couldn't create texture. Error: ", SDL_GetError());
        return {};
    }
    
    return Texture(
        texture, 
        projection.value_or((SDL_FRect) { 0, 0, width, height }), 
        crop.value_or((SDL_FRect) { 0, 0, width, height })
    );
}

std::optional<Texture> Texture::create(SDL_Renderer* renderer, std::filesystem::path path, std::optional<SDL_FRect> projection, std::optional<SDL_FRect> crop)
{
    SDL_Texture* texture = IMG_LoadTexture(renderer, path.c_str());
    if (!texture)
    {
        LOGERROR("[TEXTURE] Couldn't load texture. Error: ", SDL_GetError());
        return {};
    }

    return Texture(
        texture, 
        projection.value_or((SDL_FRect) { 0, 0, (float)texture->w, (float)texture->h }), 
        crop.value_or((SDL_FRect) { 0, 0, (float)texture->w, (float)texture->h })
    );
}

Texture::Texture(SDL_Texture* texture, SDL_FRect proj, SDL_FRect crop)
: m_texture(texture, SDL_DestroyTexture), m_projection(proj), m_crop(crop)
{}

void Texture::target(SDL_Renderer* renderer) const
{
    SDL_SetRenderTarget(renderer, m_texture.get()); 
}

void Texture::draw(SDL_Renderer* renderer) const
{
    SDL_RenderTexture(renderer, m_texture.get(), &m_crop, &m_projection); 
}

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
    m_crop = { 
        x.value_or(m_crop.x), 
        y.value_or(m_crop.y), 
        width.value_or(m_crop.w), 
        height.value_or(m_projection.h) 
    };
} 