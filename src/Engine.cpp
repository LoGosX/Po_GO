#include <iostream>
#include "Engine.h"
#include "GameState.h"
#include "GameStateSaver.h"

Engine::Engine(int width, int height, int size)
{
    _board_size = size;
    _width = width;
    _height = height;
    _render_system.reset(new RenderSystem (this, _width, _height, "XD"));
}

void Engine::restart() {
    if(!current_gs)
    {
        GameStateSaver().save(current_gs, _save_file);
        delete current_gs;
        current_gs = nullptr;
    }
    current_gs = new GameState(_board_size, 0, nullptr, {0, -1, -1, -1});

    _render_system->initGraphicalBoard(_board_size, _height, _height);
}

void Engine::_load() {
    
    current_gs = GameStateSaver().restore(_save_file);
    if(!current_gs)
        current_gs = new GameState(_board_size, 0, nullptr, {0,-1,-1,-1});
    _render_system->initGraphicalBoard(current_gs->getBoard().getSize(), _height, _height);
}

void Engine::goBackOneMove() {
    auto gs = current_gs->getPreviousGameState();
    if(gs)
        current_gs = gs;
}

void Engine::run()
{   
    //std::cerr << "load()" << std::endl;
    _load();
    while (_render_system->isWindowOpen())
    {
        //std::cerr << "handleInput()" << std::endl;
        _render_system->handleInput();
        //std::cerr << "clear()" << std::endl;
        _render_system->clear();
        //std::cerr << "draw()" << std::endl;
        _render_system->draw();
        //std::cerr << "display()" << std::endl;
        _render_system->display();
    }
    //std::cerr << "save()" << std::endl;
    GameStateSaver().save(current_gs, _save_file);
}

bool Engine::tryPlaceStone(int r, int c)
{
    int res;
    bool result = false;
    auto moves = current_gs->getPossibleMoves();
    Move move;
    for(auto m : moves) {
        if(!m.pass && m.row == r && m.col == c && m.color == getCurrentPlayer())
        {
            result = true;
            move = m;
            break;
        }
    }
    if(result)
    {
        current_gs = current_gs->afterMove(move);
        return true;
    }
    return false;
}

int Engine::getCurrentPlayer() const { return current_gs->getCurrentPlayer(); }

template<typename T>
std::vector<std::pair<int,int>> getPieces(T board, CELL piece)
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
    return getPieces(current_gs->getBoard(), CELL::BLACK_STONE);
}
std::vector<std::pair<int,int>> Engine::getWhiteStonesPositions() const{
    return getPieces(current_gs->getBoard(), CELL::WHITE_STONE);
}

std::pair<int,int> Engine::getScores() const{
    return current_gs->getBoard().getPoints();
}

void Engine::passTurn() {
    Move m;
    m.pass = true;
    for(auto move : current_gs->getPossibleMoves())
    {
        if(move.pass){
            current_gs = current_gs->afterMove(move);
            break;
        }
    }   
}