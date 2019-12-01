#pragma once

class GameState;

class GameStateSaver {

public:
    
    /**
     * @brief Saves the game from the beginning to the current state
     * 
     * @param current_game_state Current game state
     * @param file File where to store game history
     */
    void save(GameState* current_game_state, const char* file);
    
    /**
     * @brief Loads game history from given file and returns last game state
     * 
     * @param file File to load history from
     * @return GameState* last game state in the history
     */
    GameState* restore(const char* file);
};