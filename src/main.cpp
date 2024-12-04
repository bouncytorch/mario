#include "engine.h"

int main() {
    Engine engine;
    if ( !engine.init() ) return 1;
    while ( engine.loop() );
}