#include "engine.h"
#include <SDL3/SDL_main.h>

int main() 
{
    Engine engine({ 1, { 1000, 500 } });
    if ( !engine.init() ) return 1;
    while ( engine.loop() );

    return 0;
}

int WinMain( int argc, char *argv[] ) 
{
    return main();
}