#pragma once
#include <vector>
#include "Board.h"
#include "Move.h"


class MCTSAlg;

class GameState
{
    friend class MCTSAlg;

    Board _board;
    int _current_player {0};
    GameState* _previous_gs {nullptr};
    std::vector<std::pair<Move, GameState*>> _next_game_states;
    int _n_uninitialized_children {0};
    bool _terminal{false};
    void _computeMoves();
    GameState* _gameStateFromMove(Move m);
    Move _move_here;
    int _n_visits{0};
    int _mcts_value{0};
public:
    GameState(int board_size, int player, GameState* previous);
    GameState(const Board& board, int player, GameState* previous);

    /**
     * @brief Get the Board object
     * 
     * @return const Board& 
     */
    const Board& getBoard() const;

    /**
     * @brief Get the move that led to this GameState
     * 
     * @return Move 
     */
    Move getMoveToState() const;

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
     * @return GameState* GameState after performing move, nullptr if move is not possible
     */
    GameState* afterMove(Move move); 
    
    /**
     * @brief Get the prevoius state of the game
     * 
     * @return GameState* representing game state one move into the past
     */
    GameState* getPreviousGameState() const;

    /**
     * @brief Get one of next game states at random
     * 
     * @return std::pair<Move, GameState*> mode and game state after this move
     */
    std::pair<Move, GameState*> getRandomTransition();

    /**
     * @brief Get the Current Player
     * 
     * @return int (0 - black, 1 - white)
     */
    int getCurrentPlayer() const;

    /**
     * @brief Get the move that led to this game state
     * 
     * @return Move 
     */
    Move getMoveHere() const;
    
};