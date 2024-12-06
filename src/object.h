#include "SDL_render.h"

class Object {
public:
    void move(short x, short y);
    void draw();
    static Object* load(SDL_Renderer* renderer, SDL_Rect& viewport, const char* filename);
private:
    Object(SDL_Renderer* renderer, SDL_Texture* texture, SDL_Rect rect, SDL_Rect& viewport);
    SDL_Renderer* renderer;
    SDL_Texture* texture;
    SDL_Rect rect;
    SDL_Rect& viewport;
};