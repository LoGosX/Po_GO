#pragma once
#include <vector>
#include "Board.h"
#include "Move.h"

class GameState
{
    Board _board;
    int _current_player;
    GameState* _previous_gs {nullptr};
    std::vector<std::pair<Move, GameState*>> _next_game_states; 
    GameState* _newGameStateFromMove(Move move);
public:
    /**
     * @brief Get all posible moves from current state of the game
     * 
     * @return std::vector<Move> Container of all possible moves from current state
     */
    std::vector<Move> getPossibleMoves();

    /**
     * @brief Creates new GameState representing game after performing given move
     * 
     * @param move Move to perform
     * @return GameState* GameState after performing move
     */
    GameState* makeMove(Move move); 
    
    /**
     * @brief Get the prevoius state of the game
     * 
     * @return GameState* representing game state one move into the past
     */
    GameState* getPreviousGameState();
};