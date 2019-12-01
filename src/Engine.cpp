#include <iostream>
#include "Engine.h"
#include "GameState.h"

Engine::Engine()
{
    _board_size = 9;
    _width = 1200;
    _height = 800;
    _render_system.reset(new RenderSystem (this, _width, _height, "XD"));
    _render_system->initGraphicalBoard(_board_size, _height, _height);
   
}

void Engine::restart() {
    board.reset(new Board(_board_size));
    if(!current_gs)
    {
        delete current_gs;
        current_gs = nullptr;
    }
    current_gs = new GameState(_board_size);
    _current_player = 0;
}

void Engine::run()
{
    restart();
    while (_render_system->isWindowOpen())
    {
        _render_system->handleInput();
        _render_system->clear();
        _render_system->draw();
        _render_system->display();
    }
}

bool Engine::tryPlaceStone(int r, int c)
{
    int res = board->placeStone(r, c, _current_player);
    if(res != -1)
    {
        std::cout << "Captured " << res << " stones!" << std::endl;
        _current_player = (_current_player + 1) % 2;
        return true;
    }
    return false;
}

int Engine::getCurrentPlayer() const { return _current_player; }

template<typename T>
std::vector<std::pair<int,int>> getPieces(T& board, CELL piece)
{
    std::vector<std::pair<int,int>> rv;
    for(int r = 0; r < board.getSize(); r++)
    {
        for(int c = 0; c < board.getSize(); c++)
        {
            if(board.getCellContent(r,c) == piece)
                rv.emplace_back(r,c);
        }
    }
    return rv;
}

std::vector<std::pair<int,int>> Engine::getBlackStonesPositions() const{
    return getPieces(*board.get(), CELL::BLACK_STONE);
}
std::vector<std::pair<int,int>> Engine::getWhiteStonesPositions() const{
    return getPieces(*board.get(), CELL::WHITE_STONE);
}