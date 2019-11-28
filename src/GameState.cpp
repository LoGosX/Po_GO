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
                //check for board repetition
                if(!(getPreviousGameState() && getPreviousGameState()->getPreviousGameState() 
                    && getPreviousGameState()->getPreviousGameState()->_board == b)) {
                    Move m{
                        false, r, c, _current_player
                    };
                    _next_game_states.emplace_back(
                        m, nullptr
                    );
                    b = _board;
                }
            }
        }   
    }
    Move m{true, -1, -1, -1};
    _next_game_states.emplace_back(m, nullptr);
    _n_uninitialized_children = _next_game_states.size();
    if(_n_uninitialized_children == 0)
        _terminal = true;
}

Move GameState::getMoveToState() const {
    return _move_here;
}

GameState* GameState::_gameStateFromMove(Move m)
{
    Board b = _board;
    b.placeStone(m.row, m.col, m.color);
    GameState* gs = new GameState(b);
    gs->_current_player = (_current_player + 1) % 2;
    gs->_previous_gs = this;
    gs->_move_here = m;
    if(_previous_gs != nullptr /*not the main root*/ && m.pass && gs->_move_here.pass)
        gs->_terminal = true;
    _n_uninitialized_children -= 1;

    return gs;
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
            if(x.second == nullptr)
                x.second = _gameStateFromMove(x.first);
            return x.second;
        }
    }   
    return nullptr;
}

GameState* GameState::getPreviousGameState() const {
    return _previous_gs;
}