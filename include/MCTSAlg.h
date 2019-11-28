#pragma once

class GameState;

class MCTSAlg
{
    GameState* _curr_gs;
    
    GameState* _selection();
    GameState* _expansion(); 
    void _backpropagation();
    int _rollout(GameState* gs);
    float _uctScore(GameState* gs);
public:
    
    /**
     * @brief Run MCTS algorithm
     * 
     * @param n_epochs number of epochs to run MCTS on
     */
    void run(int n_epochs);

    /**
     * @brief Set the state from whichs MCTS alg will start
     * 
     * @param gs 
     */
    void setCurrentGameState(GameState* gs);
};  