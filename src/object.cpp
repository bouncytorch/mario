#include "object.h"
#include "SDL_image.h"
#include "SDL_rect.h"
#include "SDL_render.h"
#include "logger.h"

Object* Object::load(SDL_Renderer* renderer, SDL_Rect& viewport, const char* filepath) 
{
    SDL_Texture* texture = IMG_LoadTexture(renderer, filepath);
    if ( !texture ) {
        logger::logErr("Texture \"", filepath, "\" failed to load. Error: ", SDL_GetError());
        return NULL;
    }

    SDL_Rect rect = { 0, 0 };
    SDL_QueryTexture(texture, NULL, NULL, &rect.w, &rect.h);

    logger::logInfo("Object \"", filepath, "\" loaded. Width: ", rect.w, " Height: ", rect.h);
    return new Object(renderer, texture, rect, viewport);
}

Object::Object(SDL_Renderer* renderer, SDL_Texture* texture, SDL_Rect rect, SDL_Rect& viewport)
: renderer( renderer ), texture( texture ), rect( rect ), viewport( viewport )
{};

void Object::draw() 
{
    SDL_IntersectRect(&rect, &viewport, &rect);
    SDL_RenderCopy(renderer, texture, NULL, &rect);
}

void Object::move(short x, short y) {}