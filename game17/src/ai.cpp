#include "ai.h"
#include <climits>
#include <algorithm>

AI::AI(char ai, char human) : aiPlayer(ai), humanPlayer(human) {}

int AI::evaluate(const Board& board) const {
    char winner = board.checkWinner();
    if (winner == aiPlayer) return +10;
    if (winner == humanPlayer) return -10;
    return 0; // Draw or game in progress
}

int AI::minimax(Board& board, int depth, bool isMax, int alpha, int beta) {
    int score = evaluate(board);

    // Terminal states
    if (score == 10) return score - depth; // AI wins
    if (score == -10) return score + depth; // Human wins
    if (!board.isMovesLeft()) return 0; // Draw

    // Maximizing player (AI)
    if (isMax) {
        int best = INT_MIN;
        for (int i = 0; i < 3; ++i) {
            for (int j = 0; j < 3; ++j) {
                if (board.getBoard()[i][j] == ' ') {
                    board.makeMove(i, j, aiPlayer);
                    best = std::max(best, minimax(board, depth + 1, !isMax, alpha, beta));
                    board.makeMove(i, j, ' '); // Undo move
                    
                    alpha = std::max(alpha, best);
                    if (beta <= alpha) return best; // Alpha-beta pruning
                }
            }
        }
        return best;
    }
    // Minimizing player (Human)
    else {
        int best = INT_MAX;
        for (int i = 0; i < 3; ++i) {
            for (int j = 0; j < 3; ++j) {
                if (board.getBoard()[i][j] == ' ') {
                    board.makeMove(i, j, humanPlayer);
                    best = std::min(best, minimax(board, depth + 1, !isMax, alpha, beta));
                    board.makeMove(i, j, ' '); // Undo move
                    
                    beta = std::min(beta, best);
                    if (beta <= alpha) return best; // Alpha-beta pruning
                }
            }
        }
        return best;
    }
}

std::pair<int, int> AI::findBestMove(Board& board) {
    int bestVal = INT_MIN;
    std::pair<int, int> bestMove = {-1, -1};
    int alpha = INT_MIN;
    int beta = INT_MAX;

    for (int i = 0; i < 3; ++i) {
        for (int j = 0; j < 3; ++j) {
            if (board.getBoard()[i][j] == ' ') {
                board.makeMove(i, j, aiPlayer);
                int moveVal = minimax(board, 0, false, alpha, beta);
                board.makeMove(i, j, ' '); // Undo move

                if (moveVal > bestVal) {
                    bestMove = {i, j};
                    bestVal = moveVal;
                }
                alpha = std::max(alpha, bestVal);
            }
        }
    }
    return bestMove;
}
