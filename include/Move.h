#pragma once

struct Move
{
    /** @brief Which player made a move. 0 - black, 1 - white */
    int moving_player;
    /** @brief Was the move a pass */
    bool pass;
    /** @brief Row of placed stone */
    int row;
    /** @brief Column of placed stone */
    int col;
    /** @brief Color of the stone. 0 - black, 1 - white */
    int color;
};