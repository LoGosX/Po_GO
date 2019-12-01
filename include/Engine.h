#pragma once
#include "RenderSystem.h"
#include <memory>
#include "Board.h"

class GameState;

class Engine
{
    std::unique_ptr<RenderSystem> _render_system;
    GameState* current_gs;
    void update();
    int _board_size;
    int _width;
    int _height;
    const char * _save_file {"save.txt"};

    void _load();
public:

    /**
     * @brief restarts the game
     * 
     */
    void restart();

    Engine(int,int,int);

    /**
     * @brief Starts the engine
     * 
     */
    void run();

    /**
     * @brief Goes back to game state two moves into the past
     * 
     */
    void goBackOneMove();

    bool tryPlaceStone(int row, int col);

    int getCurrentPlayer() const;


    std::vector<std::pair<int,int>> getBlackStonesPositions() const;
    std::vector<std::pair<int,int>> getWhiteStonesPositions() const;

    std::pair<int,int> getScores() const;
};