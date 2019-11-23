#pragma once
#include "RenderSystem.h"
#include <memory>
#include "Board.h"

class GameState;

class Engine
{
    std::unique_ptr<RenderSystem> _render_system;
    std::unique_ptr<Board> board;
    GameState* current_gs;
    void update();
    int _current_player {0}; //0 - black, 1 - white
public:

    Engine();

    /**
     * @brief Starts the engine
     * 
     */
    void run();

    bool tryPlaceStone(int row, int col);

    int getCurrentPlayer() const;


    std::vector<std::pair<int,int>> getBlackStonesPositions() const;
    std::vector<std::pair<int,int>> getWhiteStonesPositions() const;
};