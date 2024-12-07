#include "texture.h"
#include "SDL3_image/SDL_image.h"
#include "SDL3/SDL_rect.h"
#include "SDL3/SDL_render.h"
#include "logger.h"

TextureObject* TextureObject::load(SDL_Renderer* renderer, const char* filepath) 
{
    SDL_Texture* texture = IMG_LoadTexture(renderer, filepath);
    if ( !texture ) {
        logger::logErr("Texture \"", filepath, "\" failed to load. Error: ", SDL_GetError());
        return NULL;
    }

    SDL_FRect rect = { 0, 0, (float)texture->w, (float)texture->h };
    logger::logInfo("Object \"", filepath, "\" loaded. Width: ", rect.w, " Height: ", rect.h);
    return new TextureObject(filepath, renderer, texture, rect);
}

TextureObject::TextureObject(const char* filepath, SDL_Renderer* renderer, SDL_Texture* texture, SDL_FRect rect)
: filepath(filepath), renderer( renderer ), texture( texture ), rect( rect )
{};

void TextureObject::draw() 
{
    SDL_RenderTexture(renderer, texture, NULL, &rect);
}

void TextureObject::move(short x, short y) 
{
    rect.x += x; rect.y += y;
    logger::logInfo("Object ", filepath, " moved to x:", rect.x, " y:", rect.y);
}

SDL_FRect TextureObject::getRect() { return rect; }