#include "game.h"
#include <iostream>

Game::Game(char human, char ai) : humanPlayer(human), aiPlayer(ai), ai(ai, human) {}

void Game::play() {
    std::cout << "Welcome to Tic-Tac-Toe!\n";
    std::cout << "You are " << humanPlayer << " and AI is " << aiPlayer << "\n";
    std::cout << "Enter your moves as row and column numbers (0-2).\n";

    bool gameOver = false;
    bool humanTurn = true;

    while (!gameOver) {
        board.printBoard();

        if (humanTurn) {
            int row, col;
            std::cout << "Your turn. Enter row and column (0-2): ";
            std::cin >> row >> col;

            if (board.makeMove(row, col, humanPlayer)) {
                humanTurn = false;
            } else {
                std::cout << "Invalid move! Try again.\n";
            }
        } else {
            std::cout << "AI is thinking...\n";
            std::pair<int, int> bestMove = ai.findBestMove(board);
            board.makeMove(bestMove.first, bestMove.second, aiPlayer);
            std::cout << "AI placed " << aiPlayer << " at (" << bestMove.first << ", " << bestMove.second << ")\n";
            humanTurn = true;
        }

        char winner = board.checkWinner();
        if (winner != ' ') {
            board.printBoard();
            if (winner == humanPlayer) {
                std::cout << "Congratulations! You won!\n";
            } else {
                std::cout << "AI wins! Better luck next time.\n";
            }
            gameOver = true;
        } else if (!board.isMovesLeft()) {
            board.printBoard();
            std::cout << "It's a draw!\n";
            gameOver = true;
        }
    }
}
