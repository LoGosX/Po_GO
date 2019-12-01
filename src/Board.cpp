#pragma once
#include "Board.h"
#include <stack>
#include <unordered_set>

Board::Board(int size)
{
    _board.resize(size, std::vector<CELL>(size, CELL::EMPTY));
};

int Board::placeStone(int row, int col, bool white)
{

    if (!_inBounds(row, col))
        return -1;
    if (_board[row][col] != CELL::EMPTY)
        return -1;
    _board[row][col] = (white ? CELL::WHITE_STONE : CELL::BLACK_STONE);
    int captures = _tryResolveCaptures(row, col);
    if (captures == -1)
        _board[row][col] = CELL::EMPTY;
    return captures;
}

bool Board::_inBounds(int r, int c) const
{
    return r >= 0 && r < _board.size() && c >= 0 && c < _board.size();
}

CELL Board::getCellContent(int r, int c) const
{
    if (!_inBounds(r, c))
        throw "Board position outside of the board!";
    return _board[r][c];
};

int toIndex(int r, int c, int s)
{
    return r * s + c;
}
std::pair<int, int> fromIndex(int i, int s)
{
    return {i / s, i % s};
}

std::vector<std::pair<int, int>> tryCapture(std::vector<std::vector<CELL>> &board, int r, int c)
{
    std::unordered_set<int> visited;
    if (r < 0 || c < 0 || r >= board.size() || c >= board.size())
        return {};
    CELL start_cell = board[r][c];
    int s = board.size();
    if (visited.count(toIndex(r, c, s) != 0))
        return {};
    std::unordered_set<int> to_capture;
    to_capture.emplace(toIndex(r, c, s));
    visited.emplace(toIndex(r, c, s));
    std::stack<std::pair<int, int>> stack;
    stack.emplace(r, c);
    while (!stack.empty())
    {
        auto t = stack.top();
        stack.pop();
        for (auto [dr, dc] : std::vector<std::pair<int, int>>{{0, 1}, {0, -1}, {1, 0}, {-1, 0}})
        {
            r = t.first + dr;
            c = t.second + dc;
            if (r >= 0 && c >= 0 && r < s && c < s)
            {
                if (board[r][c] == start_cell && visited.count(toIndex(r, c, s)) == 0)
                {
                    stack.emplace(r, c);
                    visited.emplace(toIndex(r, c, s));
                    to_capture.emplace(toIndex(r, c, s));
                }
                else if (board[r][c] == CELL::EMPTY)
                    return {};
            }
        }
    }
    std::vector<std::pair<int, int>> rv;
    for (auto i : to_capture)
    {
        auto [r, c] = fromIndex(i, s);
        rv.emplace_back(r, c);
    }
    return rv;
}

int Board::_tryResolveCaptures(int row, int col)
{
    int captures = 0;

    for (auto [dr, dc] : std::vector<std::pair<int, int>>{{0, 1}, {0, -1}, {1, 0}, {-1, 0}})
    {
        int r = row + dr;
        int c = col + dc;
        if (_inBounds(r, c) && _board[r][c] != CELL::EMPTY && _board[r][c] != _board[row][col])
        {
            auto capt = tryCapture(_board, row + dr, col + dc);
            for (auto [r, c] : capt)
                _board[r][c] = CELL::EMPTY;
            captures += capt.size();
        }
    }

    if (captures == 0 && tryCapture(_board, row, col).size() != 0)
        return -1;
    return captures;
}

int Board::getSize() const
{
    return _board.size();
}

bool Board::operator!=(const Board &other)
{
    return !operator==(other);
}

bool Board::operator==(const Board &other)
{
    for (int i = 0; i < _board.size(); i++)
    {
        for (int j = 0; j < _board.size(); j++)
        {
            if (_board[i][j] != other._board[i][j])
                return false;
        }
    }
    return true;
}

//(how much tile)
void process(std::vector<std::vector<int>> &positions, int start_r, int start_c)
{

    std::vector<std::pair<int, int>> x;
    x.emplace_back(start_r, start_c);
    bool white_neightbour = false;
    bool black_neightbour = false;
    std::stack<std::pair<int, int>> s;
    s.emplace(start_r, start_c);
    while (!s.empty())
    {
        auto [r, c] = s.top();
        s.pop();
        for (auto [dr, dc] : std::vector<std::pair<int, int>>{{-1, 0}, {1, 0}, {0, -1}, {0, 1}})
        {
            int nr = r + dr;
            int nc = c + dc;
            if (nr >= 0 && nr < positions.size() && nc >= 0 && nc < positions.size())
            {
                if (positions[nr][nc] == -2)
                {
                    x.emplace_back(nr, nc);
                    positions[nr][nc] = -1;
                    s.emplace(nr, nc);
                }
                else if (positions[nr][nc] == 0)
                    black_neightbour = true;
                else if (positions[nr][nc] == 1)
                    white_neightbour = true;
            }
        }
    }
    if (white_neightbour && !black_neightbour)
    {
        for (auto [r, c] : x)
        {
            positions[r][c] = 1;
        }
    }
    else if (!white_neightbour && black_neightbour)
    {
        for (auto [r, c] : x)
        {
            positions[r][c] = 0;
        }
    }
}

std::pair<int, int> Board::getPoints() const
{
    //-2 - not visited yet, -1 - nobody's terrority, 0 - black's terrority, 1 - white's terrority
    std::vector<std::vector<int>> checked_positions(_board.size(), std::vector<int>(_board.size(), -2));
    for (int r = 0; r < _board.size(); r++)
    {
        for (int c = 0; c < _board.size(); c++)
        {
            if (_board[r][c] == CELL::BLACK_STONE)
                checked_positions[r][c] = 0;
            else if (_board[r][c] == CELL::WHITE_STONE)
                checked_positions[r][c] = 1;
        }
    }
    for (int r = 0; r < _board.size(); r++)
    {
        for (int c = 0; c < _board.size(); c++)
        {
            if (checked_positions[r][c] == -2)
                process(checked_positions, r, c);
        }
    }

    int black_area = 0;
    int white_area = 0;
    for(int r = 0; r < checked_positions.size(); r++) {
        for (int c = 0; c < checked_positions.size(); c++)
        {
            if(checked_positions[r][c] == 0)
                black_area++;
            if(checked_positions[r][c] == 1)
                white_area++;
        }
    }
    return {black_area, white_area};
}