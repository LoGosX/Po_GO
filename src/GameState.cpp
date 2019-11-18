#pragma once
#include "GameState.h"


std::vector<Move> GameState::getPossibleMoves() const {
    return {};
}

GameState* GameState::makeMove(Move move) const {
    return nullptr;
}

GameState* GameState::getPreviousGameState() const {
    return _previous_gs;
}