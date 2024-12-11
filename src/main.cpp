#include "engine.h"
#include <SDL3/SDL_main.h>

int main(int argc, char **argv) 
{
    Engine engine((Engine::Settings) { 165, { 1000, 500 } });
    if ( !engine.init() ) return 1;
    while ( engine.loop() );

    return 0;
}