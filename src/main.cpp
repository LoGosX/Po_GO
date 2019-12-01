#include "Engine.h"
#include "Board.h"
#include <iostream>

int main(int argc, const char * argv[])
{
    int width = 1200, height = 800, size = 9;
    if(argc > 1) {
        width = std::atoi(argv[1]);
        height = std::atoi(argv[2]);
        size = std::atoi(argv[3]);
    }
    auto e = new Engine(width, height, size);
    e->run();
    delete e;
    return 0;
}