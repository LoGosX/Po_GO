#include "GameStateSaver.h"
#include "GameState.h"
#include <fstream>
#include <string>
#include <vector>
#include <iostream>

template<typename ...Args>
std::string concatenate(Args... args) {
    return ((std::to_string(args) + ' ') + ...);
}

void GameStateSaver::save(GameState* g, const char * path){
    std::ofstream file(path, std::ios::trunc);
    std::vector<std::string> turns;
    int size = g->getBoard().getSize();
    while(g->getPreviousGameState() != nullptr /* not root */)
    {
        Move m = g->getMoveHere();
        turns.push_back(concatenate(m.row, m.col, m.color, m.pass));
        g = g->getPreviousGameState();
    }
    file << size << '\n';
    for(auto begin = turns.rbegin(); begin != turns.rend(); begin++)
        file << *begin << '\n';
    file.close();
}


GameState* GameStateSaver::restore(const char * path){
    std::fstream file(path);
    GameState* g = nullptr;
    if(file.good()){
        int size, row, column, color, pass;
        file >> size;

        g = new GameState(size, 0, nullptr, {0, -1, -1, -1});
        while(file >> row >> column >> color >> pass) {
            //std::cerr << concatenate(row, column, color, pass) << std::endl;
            Move m {pass, row, column, color};
            g = g->afterMove(m);
        }
        file.close();
    }
    return g;
}