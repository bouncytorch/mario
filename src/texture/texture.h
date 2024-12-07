#include "SDL3/SDL_render.h"

class Texture {
public:
    void move(short x = 0, short y = 0);
    void draw();
    SDL_FRect getRect();

    static Texture* load(SDL_Renderer* renderer, const char* filename);
private:
    Texture(const char* filepath, SDL_Renderer* renderer, SDL_Texture* texture, SDL_FRect rect);
    const char* filepath;
    SDL_Renderer* renderer;
    SDL_Texture* texture;
    SDL_FRect rect;
};