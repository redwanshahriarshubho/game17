#ifndef AI_H
#define AI_H

#include "board.h"

class AI {
private:
    char aiPlayer;
    char humanPlayer;

    int minimax(Board& board, int depth, bool isMax, int alpha, int beta);
    int evaluate(const Board& board) const;

public:
    AI(char ai = 'O', char human = 'X');
    std::pair<int, int> findBestMove(Board& board);
};

#endif
