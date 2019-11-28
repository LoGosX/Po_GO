#pragma once
#include <vector>
#include "Board.h"
#include "Move.h"

class GameState;

class MCTSGameState
{
    GameState* _curr_gs;
    int _n_visits {0};
public:
};