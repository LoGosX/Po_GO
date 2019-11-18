#pragma once
#include "Board.h"

Board::Board(int size)
{
    _board.resize(size, std::vector<CELL>(size, CELL::EMPTY));
};
 
bool Board::placeStone(int row, int col, bool white) {
    if(!_tryPlaceStone(row, col, white))
        return false;
    if(!_tryResolveCaptures(row, col))
        return false;
    return true;
}

bool Board::_inBounds(int r, int c) const {
    return r >= 0 && r < _board.size() && c >= 0 && c < _board.size();
}

CELL Board::getCellContent(int r, int c) const {
    if(!_inBounds(r, c))
        throw "Board position outside of the board!";
    return _board[r][c];
};


bool Board::_tryPlaceStone(int row, int col, bool white_stone) {
    return false;
}

bool Board::_tryResolveCaptures(int row, int col) {
    return false;
}