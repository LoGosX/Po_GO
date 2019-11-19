#pragma once
#include "RenderSystem.h"
#include <memory>
#include "GameState.h"
#include "Board.h"

class Engine
{
    std::unique_ptr<RenderSystem> _render_system;
    std::unique_ptr<Board> board;
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