// #include "logger.h"
#include "engine.h"
#include <SDL2/SDL_timer.h>

int main() {
    Engine engine;
    if ( !engine.init(640, 480) ) return 1;
    while ( engine.loop() );
}