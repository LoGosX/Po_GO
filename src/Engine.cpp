#include <iostream>
#include "Engine.h"
#include "GameState.h"

Engine::Engine()
{
    int board_size = 9;
    _render_system.reset(new RenderSystem (this, 1600, 1600, "XD"));
    _render_system->initGraphicalBoard(board_size, 1600, 1600);
    board.reset(new Board(board_size));
    current_gs = new GameState(board_size);
}

void Engine::run()
{
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