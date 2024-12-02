// #include "logger.h"
#include "engine.h"
#include <SDL2/SDL_timer.h>

int main() {
    Engine engine;
    if ( !engine.init() ) return 1;
    while ( engine.loop() ) { SDL_Delay(10); };
}