#include <iostream>
#include <vector>
#include <cstdlib>
#include <ctime>

using namespace std;

class TicTacToe {
private:
    char board[3][3]{};
    char currentPlayer;
    vector<pair<int, int>> playerMoves;
    vector<pair<int, int>> computerMoves;

public:
    TicTacToe() {
        resetBoard();
        currentPlayer = 'X'; // Player always starts the game
    }

    void resetBoard() {
        for (auto & i : board) {
            for (char & j : i) {
                j = ' ';
            }
        }
    }

    void printBoard() const {
        // Print the board
        cout << "   |   |   " << endl;
        for (int i = 0; i < 3; ++i) {
            cout << " " << board[i][0] << " | " << board[i][1] << " | " << board[i][2] << endl;
            if (i < 2)
                cout << "---|---|---" << endl;
        }
        cout << "   |   |   " << endl;

        // Print previous moves
        cout << "Player's moves (X): ";
        for (const auto& move : playerMoves) {
            cout << "(" << move.first + 1 << ", " << move.second + 1 << ") ";
        }
        cout << endl;

        cout << "Computer's moves (O): ";
        for (const auto& move : computerMoves) {
            cout << "(" << move.first + 1 << ", " << move.second + 1 << ") ";
        }
        cout << endl;
    }

    bool playerMove(int row, int col) {
        if (row < 0 || row >= 3 || col < 0 || col >= 3 || board[row][col] != ' ')
            return false;
        board[row][col] = currentPlayer;
        playerMoves.emplace_back(row, col);
        return true;
    }

    void switchPlayer() {
        currentPlayer = (currentPlayer == 'X') ? 'O' : 'X';
    }

    [[nodiscard]] char getCurrentPlayer() const {
        return currentPlayer;
    }

    [[nodiscard]] bool isBoardFull() const {
        for (auto i : board) {
            for (int j = 0; j < 3; ++j) {
                if (i[j] == ' ')
                    return false;
            }
        }
        return true;
    }

    [[nodiscard]] char checkWinner() const {
        // Check rows
        for (auto i : board) {
            if (i[0] == i[1] && i[0] == i[2] && i[0] != ' ')
                return i[0];
        }

        // Check columns
        for (int i = 0; i < 3; ++i) {
            if (board[0][i] == board[1][i] && board[0][i] == board[2][i] && board[0][i] != ' ')
                return board[0][i];
        }

        // Check diagonals
        if (board[0][0] == board[1][1] && board[0][0] == board[2][2] && board[0][0] != ' ')
            return board[0][0];
        if (board[0][2] == board[1][1] && board[0][2] == board[2][0] && board[0][2] != ' ')
            return board[0][2];

        return ' ';
    }

    void computerMoveNormal() {
        // Check for winning moves
        for (int i = 0; i < 3; ++i) {
            for (int j = 0; j < 3; ++j) {
                if (board[i][j] == ' ') {
                    board[i][j] = currentPlayer;
                    if (checkWinner() == currentPlayer) {
                        computerMoves.emplace_back(i, j);
                        return;
                    }
                    board[i][j] = ' '; // Undo the move
                }
            }
        }

        // Check for blocking opponent's winning moves
        char opponent = (currentPlayer == 'X') ? 'O' : 'X';
        for (int i = 0; i < 3; ++i) {
            for (int j = 0; j < 3; ++j) {
                if (board[i][j] == ' ') {
                    board[i][j] = opponent;
                    if (checkWinner() == opponent) {
                        board[i][j] = currentPlayer;
                        computerMoves.emplace_back(i, j);
                        return;
                    }
                    board[i][j] = ' '; // Undo the move
                }
            }
        }

        // If no winning or blocking moves, make a random move
        srand(time(nullptr));
        int x, y;
        do {
            x = rand() % 3;
            y = rand() % 3;
        } while (board[x][y] != ' ');

        board[x][y] = currentPlayer;
        computerMoves.emplace_back(x, y);
    }

    void computerMoveHard() {
        int bestScore = -1000;
        pair<int, int> bestMove;
        for (int i = 0; i < 3; ++i) {
            for (int j = 0; j < 3; ++j) {
                if (board[i][j] == ' ') {
                    board[i][j] = currentPlayer;
                    int score = minimax(board, 0, false, -1000, 1000);
                    board[i][j] = ' ';
                    if (score > bestScore) {
                        bestScore = score;
                        bestMove = {i, j};
                    }
                }
            }
        }
        board[bestMove.first][bestMove.second] = currentPlayer;
        computerMoves.emplace_back(bestMove);
    }

    int minimax(char board[3][3], int depth, bool isMaximizingPlayer, int alpha, int beta) {
        char result = checkWinner();
        if (result != ' ') {
            if (result == 'X') return -10 + depth;
            else if (result == 'O') return 10 - depth;
            else return 0;
        }

        if (isBoardFull()) return 0;

        if (isMaximizingPlayer) {
            int maxScore = -1000;
            for (int i = 0; i < 3; ++i) {
                for (int j = 0; j < 3; ++j) {
                    if (board[i][j] == ' ') {
                        board[i][j] = 'O';
                        int score = minimax(board, depth + 1, false, alpha, beta);
                        maxScore = max(maxScore, score);
                        alpha = max(alpha, score);
                        board[i][j] = ' ';
                        if (beta <= alpha) break; // Pruning
                    }
                }
            }
            return maxScore;
        } else {
            int minScore = 1000;
            for (int i = 0; i < 3; ++i) {
                for (int j = 0; j < 3; ++j) {
                    if (board[i][j] == ' ') {
                        board[i][j] = 'X';
                        int score = minimax(board, depth + 1, true, alpha, beta);
                        minScore = min(minScore, score);
                        beta = min(beta, score);
                        board[i][j] = ' ';
                        if (beta <= alpha) break; // Pruning
                    }
                }
            }
            return minScore;
        }
    }
};

void printMenu() {
    cout << " _   _      _             _             \n"
            "| | (_)    | |           | |            \n"
            "| |_ _  ___| |_ __ _  ___| |_ ___   ___ \n"
            "| __| |/ __| __/ _` |/ __| __/ _ \\ / _ \\\n"
            "| |_| | (__| || (_| | (__| || (_) |  __/\n"
            " \\__|_|\\___|\\__\\__,_|\\___|\\__\\___/ \\___|\n"
            "\n"
            "\"============= Tic Tac Toe =============\"\n"
            "" << endl;
    cout << "1. Player VS. Computer" << endl;
    cout << "2. Quit" << endl;
    cout << "\n";
    cout << "Enter your choice: ";
}

void printDifficultyMenu() {
    cout << "\nChoose difficulty:" << endl;
    cout << "1. Normal" << endl;
    cout << "2. Hard (Minimax with alpha-beta pruning)" << endl;
    cout << "\nEnter your choice: ";
}

int main() {
    char choice;
    do {
        printMenu();
        cin >> choice;

        switch (choice) {
            case '1': {
                char difficultyChoice;
                do {
                    printDifficultyMenu();
                    cin >> difficultyChoice;
                    TicTacToe game;
                    int row, col;
                    char winner;
                    while (true) {
                        game.printBoard();
                        cout << "Current player: " << game.getCurrentPlayer() << endl;
                        if (game.getCurrentPlayer() == 'X') {
                            cout << "Enter row and column (1-3) for your move: ";
                            cin >> row >> col;
                            --row; --col;
                            if (game.playerMove(row, col)) {
                                winner = game.checkWinner();
                                if (winner != ' ' || game.isBoardFull()) break;
                                game.switchPlayer();
                            } else {
                                cout << "Invalid move! Try again." << endl;
                            }
                        } else {
                            if (difficultyChoice == '1') {
                                game.computerMoveNormal();
                            } else if (difficultyChoice == '2') {
                                game.computerMoveHard();
                            }
                            winner = game.checkWinner();
                            if (winner != ' ' || game.isBoardFull()) break;
                            game.switchPlayer();
                        }
                    }

                    game.printBoard();
                    if (winner == 'X') cout << "Congratulations! You win!" << endl;
                    else if (winner == 'O') cout << "Computer wins! Better luck next time!" << endl;
                    else cout << "It's a tie!\n"
                                 " |\\__/,|   (`\\\n"
                                 " |_ _  |.--.) )\n"
                                 " ( T   )     /\n"
                                 "(((^_(((/(((_/"<< endl;

                    cout << "Do you want to play again? (Y/N): ";
                    cin >> choice;
                } while (choice == 'Y' || choice == 'y');
                break;
            }
            case '2':
                cout << "Thanks for playing!" << endl;
                break;
            default:
                cout << "Invalid choice! Please try again." << endl;
        }
    } while (choice != '2');

    return 0;
}