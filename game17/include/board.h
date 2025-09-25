#ifndef BOARD_H
#define BOARD_H

#include <vector>

class Board {
private:
    std::vector<std::vector<char>> board;

public:
    Board();
    void printBoard() const;
    bool isMovesLeft() const;
    char checkWinner() const;
    bool makeMove(int row, int col, char player);
    const std::vector<std::vector<char>>& getBoard() const;
    void reset();
};

#endif
