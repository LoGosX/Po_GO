#pragma once
#include "RenderSystem.h"
#include <memory>
#include "Board.h"

class GameState;

class Engine
{
    std::unique_ptr<RenderSystem> _render_system;
    GameState* current_gs;
    int _board_size;
    int _width;
    int _height;
    const char * _save_file {"save.txt"};
    bool _initialized {false};

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

    /**
     * @brief Checks if 
     * 
     * @param row 
     * @param col 
     * @return true 
     * @return false 
     */
    bool tryPlaceStone(int row, int col);

    /**
     * @brief Passes turn
     * 
     */
    void passTurn();

    /**
     * @brief Gets the current player
     * 
     * @return int 0 - black, 1 - white
     */
    int getCurrentPlayer() const;


    std::vector<std::pair<int,int>> getBlackStonesPositions() const;
    std::vector<std::pair<int,int>> getWhiteStonesPositions() const;

    std::pair<int,int> getScores() const;
};