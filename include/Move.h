#pragma once

struct Move
{
   /** @brief Was the move a pass */
    bool pass {false};
    /** @brief Row of placed stone */
    int row {0};
    /** @brief Column of placed stone */
    int col {0};
    /** @brief Color of the stone. 0 - black, 1 - white */
    int color {0};

    bool operator == (const Move& m) const {
        return pass && m.pass || (row == m.row && col == m.col && color == m.color); 
    }
};
