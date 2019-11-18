#pragma once
#include "GameState.h"


std::vector<Move> GameState::getPossibleMoves() {
    return {};
}

GameState* GameState::makeMove(Move move) {
    return this;
}

GameState* GameState::getPreviousGameState() {
    return _previous_gs;
}