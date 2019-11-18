#pragma once

#include <vector>

enum class CELL {
    EMPTY,
    WHITE_STONE,
    BLACK_STONE
};

class Board
{
    std::vector<std::vector<CELL>> _board;
    int _n_strings;

    bool _tryPlaceStone(int row, int col, bool white_stone);
    bool _tryResolveCaptures(int row, int col);
    bool _inBounds(int r, int c) const;

public:
    /**
     * @brief Construct a new Board object
     * 
     * @param size Size of the board (board is a square with side length 'size')
     */
    Board(int size);

    /**
     * @brief places a given stone at the specified position
     * 
     * @param row Row to place the stone, where top row has number 0 going down up to size - 1
     * @param col Column to place the stone, where left-most column has number 0 going right up to size - 1
     * @param white_stone What stone to place (true - white stone, false - black stone)
     * @return true Successfully placed a stone
     * @return false Failed to place a stone (probably because of illegal move)
     */
    bool placeStone(int row, int col, bool white_stone);

    /**
     * @brief Get board content at the specified position
     * 
     * @param row From which row to take
     * @param col From which column to take
     * @return CELL Content of specified location on the board
     */
    CELL getCellContent(int row, int col) const;
};
