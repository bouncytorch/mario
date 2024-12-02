#include <SDL2/SDL.h>
#include <SDL2/SDL_surface.h>

class Engine {
public:
    bool init(unsigned int width, unsigned int height);
    bool loop();
    void resizeViewport(int width, int height);
    ~Engine();
private:
    SDL_Window* window;
    SDL_Renderer* renderer;
    SDL_Surface* surface;

    SDL_Rect viewport;
    float viewportRatio = 1.33333;

    SDL_Event event;
};