#include "SDL_render.h"

class Object {
public:
    void move(short x = 0, short y = 0);
    void draw();
    SDL_Rect getRect();

    static Object* load(SDL_Renderer* renderer, const char* filename);
private:
    Object(const char* filepath, SDL_Renderer* renderer, SDL_Texture* texture, SDL_Rect rect);
    const char* filepath;
    SDL_Renderer* renderer;
    SDL_Texture* texture;
    SDL_Rect rect;
};