#include <SDL2/SDL.h>
#include <SDL2/SDL_surface.h>

class Engine {
public:
    bool init();
    bool loop();
    ~Engine();
private:
    SDL_Window* window;
    SDL_Renderer* renderer;
    SDL_Surface* surface;

    SDL_Rect viewport;
    float viewportRatio;

    SDL_Event event;
};