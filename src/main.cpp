#include <iostream>
#include <SFML/Graphics.hpp>
#include "GraphicalBoard.h"

#include "RenderSystem.h"

int main()
{
    std::cout << 0 << std::endl;
    
    RenderSystem rs(nullptr, 800, 800, "XD");
    
    while (rs.isWindowOpen())
    {
        rs.handleInput();
        rs.clear();
        rs.draw();
        rs.display();
    }
    
    return 0;
}