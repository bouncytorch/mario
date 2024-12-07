#include "engine.h"

int main( int argc, char *argv[] ) 
{
    Engine engine;
    if ( !engine.init() ) return 1;
    while ( engine.loop() );

    return 0;
}

int WinMain( int argc, char *argv[] ) 
{
    Engine engine;
    if ( !engine.init() ) return 1;
    while ( engine.loop() );

    return 0;
}