#include "MCTSAlg.h"
#include "GameState.h"

constexpr float EXPLORATION_CONSTANT = 2;

float MCTSAlg::_uctScore(GameState* gs)
{   
   //return gs->_mcts_value / (float)gs->_n_visits + sqrtf(EXPLORATION_CONSTANT * log(gs->_previous_gs->_n_visits / ((float)gs->_n_visits))));
    return 0;
}

GameState* MCTSAlg::_selection() {
	return nullptr;
}

GameState* MCTSAlg::_expansion() {
    return nullptr;
}

void MCTSAlg::_backpropagation() {

}

int MCTSAlg::_rollout(GameState* gs) {
    return 0;
}

void MCTSAlg::run(int n_epochs) {

}