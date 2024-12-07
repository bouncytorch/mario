#include "object.h"
#include "SDL_image.h"
#include "SDL_rect.h"
#include "SDL_render.h"
#include "logger.h"

Object* Object::load(SDL_Renderer* renderer, const char* filepath) 
{
    SDL_Texture* texture = IMG_LoadTexture(renderer, filepath);
    if ( !texture ) {
        logger::logErr("Texture \"", filepath, "\" failed to load. Error: ", SDL_GetError());
        return NULL;
    }

    SDL_Rect rect = { 0, 0 };
    SDL_QueryTexture(texture, NULL, NULL, &rect.w, &rect.h);
    logger::logInfo("Object \"", filepath, "\" loaded. Width: ", rect.w, " Height: ", rect.h);
    return new Object(filepath, renderer, texture, rect);
}

Object::Object(const char* filepath, SDL_Renderer* renderer, SDL_Texture* texture, SDL_Rect rect)
: filepath(filepath), renderer( renderer ), texture( texture ), rect( rect )
{};

void Object::draw() 
{
    SDL_RenderCopy(renderer, texture, NULL, &rect);
}

void Object::move(short x, short y) 
{
    rect.x += x; rect.y += y;
    logger::logInfo("Object ", filepath, " moved to x:", rect.x, " y:", rect.y);
}

SDL_Rect Object::getRect() { return rect; }