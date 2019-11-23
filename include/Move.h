#pragma once

struct Move
{
   /** @brief Was the move a pass */
    bool pass;
    /** @brief Row of placed stone */
    int row;
    /** @brief Column of placed stone */
    int col;
    /** @brief Color of the stone. 0 - black, 1 - white */
    int color;

    bool operator == (const Move& m) const {
        return pass && m.pass || (row == m.row && col == m.col && color == m.color); 
    }
};
