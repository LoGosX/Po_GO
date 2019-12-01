#pragma once
#include "GameState.h"
#include <iostream>

GameState::GameState(int s, int player, GameState* previous, Move move_here) 
    : _board(s), _current_player(player), _previous_gs(previous), _move_here(move_here)
    { _computeMoves(); }
GameState::GameState(const Board& board, int player, GameState* previous, Move move_here) 
    : _board(board), _current_player(player), _previous_gs(previous), _move_here(move_here)
    { _computeMoves(); }

const Board& GameState::getBoard() const {
    return _board;
}

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
                if(!(_previous_gs && _previous_gs->_board == b)){
                    Move m{
                        false, r, c, _current_player
                    };
                    _next_game_states.emplace_back(
                        m, nullptr
                    );
                }
                b = _board;
            }
        }   
    }
    if(!(_move_here.pass && _previous_gs && _previous_gs->_move_here.pass)){
        Move m{true, -1, -1, -1};
        _next_game_states.emplace_back(m, nullptr);
    }
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
    GameState* gs = new GameState(b, (_current_player + 1) % 2, this, m);
    if(_previous_gs != nullptr /*not the main root*/ && m.pass && gs->_move_here.pass)
        gs->_terminal = true;
    _n_uninitialized_children -= 1;

    return gs;
}

std::vector<Move> GameState::getPossibleMoves() {
    if(_move_here.pass && _previous_gs && _previous_gs->_move_here.pass)
        return {};
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

int GameState::getCurrentPlayer() const {
    return _current_player;
}

Move GameState::getMoveHere() const {
    return _move_here;
}