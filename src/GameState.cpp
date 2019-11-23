#pragma once
#include "GameState.h"

GameState::GameState(int s) : _board(s) { _computeMoves(); }
GameState::GameState(const Board& board) : _board(board) { _computeMoves(); }

void GameState::_computeMoves()
{
    Board b = _board;
    for(int r = 0; r < _board.getSize(); r++)
    {
        for(int c = 0; c < _board.getSize(); c++)
        {
            if(b.placeStone(r, c, _current_player) != -1)
            {
                Move m{
                    false, r, c, _current_player
                };
                _next_game_states.emplace_back(
                    m, nullptr
                );
            }
        }   
    }
    Move m{true, -1, -1, -1};
    _next_game_states.emplace_back(m, nullptr);
    _n_uninitialized_children = _next_game_states.size();
    if(_n_uninitialized_children == 0)
        _terminal = true;
}

std::vector<Move> GameState::getPossibleMoves() {
    std::vector<Move> moves;
    for(const auto& x : _next_game_states)
        moves.push_back(x.first);
    return moves;
}

GameState* GameState::afterMove(Move move) {
    for(int i = 0; i < _next_game_states.size(); i++)
    {
        auto& x = _next_game_states[i];
        if(x.first == move)
        {
            return x.second;
        }
    }   
    return nullptr;
}

GameState* GameState::getPreviousGameState() const {
    return _previous_gs;
}