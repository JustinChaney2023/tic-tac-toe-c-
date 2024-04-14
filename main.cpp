#include <iostream>
<<<<<<< Updated upstream
#include <string>
=======
#include <vector>
#include <cstdlib>
>>>>>>> Stashed changes
#include <ctime>

using namespace std;

<<<<<<< Updated upstream
// Define the board
char board[3][3] = {
    {' ', ' ', ' '},
    {' ', ' ', ' '},
    {' ', ' ', ' '}
};

// Define constants for players
const char PLAYER = 'X';
const char COMPUTER = 'O';
char currentPlayer = PLAYER;

// Function declarations
void printBoard();
int checkFreeSpaces();
void playerMove();
void computerMove();
char checkWinner();
void printWinner(char);

int main()
{
    char winner;

    // Main game loop
    for (int i = 0; i < 9; i++)
    {
        printBoard();

        // Alternate between player and computer moves
        if (currentPlayer == PLAYER)
        {
            playerMove();
            winner = checkWinner();
            if (winner != ' ' || checkFreeSpaces() == 0)
            {
                break;
            }
            currentPlayer = COMPUTER;
        }
        else
        {
            computerMove();
            winner = checkWinner();
            if (winner != ' ' || checkFreeSpaces() == 0)
            {
                break;
            }
            currentPlayer = PLAYER;
        }
    }

    // Print final board and winner
    printBoard();
    printWinner(winner);

    return 0;
}

// Function to print the board
void printBoard()
{
    cout << "   |   |   " << endl;
    cout << " " << board[0][0] << " | " << board[0][1] << " | " << board[0][2] << endl;
    cout << "___|___|___" << endl;
    cout << "   |   |   " << endl;
    cout << " " << board[1][0] << " | " << board[1][1] << " | " << board[1][2] << endl;
    cout << "___|___|___" << endl;
    cout << "   |   |   " << endl;
    cout << " " << board[2][0] << " | " << board[2][1] << " | " << board[2][2] << endl;
    cout << "   |   |   " << endl;

    cout << endl << "Computer's moves (O): "; // Added: Displaying computer moves
    for (int i = 0; i < 3; i++)
    {
        for (int j = 0; j < 3; j++)
        {
            if (board[i][j] == COMPUTER)
            {
                cout << "(" << i << ", " << j << ") ";
            }
        }
    }
    cout << endl;
}

// Function to check the number of free spaces on the board
int checkFreeSpaces()
{
    int freeSpaces = 0;

    for (auto & i : board)
    {
        for (char j : i)
        {
            if (j == ' ')
            {
                freeSpaces++;
            }
        }
    }
    return freeSpaces;
}

// Function for player's move
void playerMove()
{
    int row, column;
    while (true)
    {
        cout << "Enter Row #(0-2): ";
        cin >> row;
        cout << "Enter Column #(0-2): ";
        cin >> column;
        if (row < 0 || row > 2 || column < 0 || column > 2)
        {
            cout << "Invalid input, try again." << endl;
        }
        else if (board[row][column] != ' ')
        {
            cout << "Tile is full, try again." << endl;
        }
        else
        {
            board[row][column] = PLAYER;
            break;
        }
    }
}

// Function for computer's move
void computerMove()
{
    // Check for winning moves
    for (auto & i : board) {
        for (char & j : i) {
            if (j == ' ') {
                j = COMPUTER;
                if (checkWinner() == COMPUTER) {
                    return;
                }
                j = ' '; // Undo the move
            }
        }
    }

    // Check for blocking opponent's winning moves
    for (auto & i : board) {
        for (char & j : i) {
            if (j == ' ') {
                j = PLAYER;
                if (checkWinner() == PLAYER) {
                    j = COMPUTER;
                    return;
                }
                j = ' '; // Undo the move
            }
        }
    }

    // If no winning or blocking moves, make a random move
    srand(time(0));
    int x, y;
    do {
        x = rand() % 3;
        y = rand() % 3;
    } while (board[x][y] != ' ');

    board[x][y] = COMPUTER;
}

// Function to check if there's a winner
char checkWinner()
{
    // Check rows
    for (auto & i : board)
    {
        if (i[0] == i[1] && i[0] == i[2] && i[0] != ' ')
        {
            return i[0];
        }
    }

    // Check columns
    for (int i = 0; i < 3; i++)
    {
        if (board[0][i] == board[1][i] && board[0][i] == board[2][i] && board[0][i] != ' ')
        {
            return board[0][i];
        }
    }

    // Check diagonals
    if (board[0][0] == board[1][1] && board[0][0] == board[2][2] && board[0][0] != ' ')
    {
        return board[0][0];
    }
    if (board[0][2] == board[1][1] && board[0][2] == board[2][0] && board[0][2] != ' ')
    {
        return board[0][2];
    }

    return ' ';
}

// Function to print the winner
void printWinner(char winner)
{
    if (winner == PLAYER)
    {
        cout << "YOU WIN!" << endl;
    }
    else if (winner == COMPUTER)
    {
        cout << "YOU LOSE!" << endl;
    }
    else
    {
        cout << "          IT'S A TIE!\n"
                "|\\      _,,,---,,_\n"
                "ZZZzz /,`.-'`'    -.  ;-;;,_\n"
                "     |,4-  ) )-,_. ,\\ (  `'-'\n"
                "    '---''(_/--'  `-'\\_)" << endl;
    }
}
=======
class TicTacToe {
private:
    char board[3][3];
    char currentPlayer;
    vector<pair<int, int>> playerMoves;
    vector<pair<int, int>> computerMoves;

public:
    TicTacToe() {
        resetBoard();
        currentPlayer = 'X'; // Player always starts the game
    }

    void resetBoard() {
        for (int i = 0; i < 3; ++i) {
            for (int j = 0; j < 3; ++j) {
                board[i][j] = ' ';
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
        playerMoves.push_back({row, col});
        return true;
    }

    void switchPlayer() {
        currentPlayer = (currentPlayer == 'X') ? 'O' : 'X';
    }

    char getCurrentPlayer() const {
        return currentPlayer;
    }

    bool isBoardFull() const {
        for (int i = 0; i < 3; ++i) {
            for (int j = 0; j < 3; ++j) {
                if (board[i][j] == ' ')
                    return false;
            }
        }
        return true;
    }

    char checkWinner() const {
        // Check rows
        for (int i = 0; i < 3; ++i) {
            if (board[i][0] == board[i][1] && board[i][0] == board[i][2] && board[i][0] != ' ')
                return board[i][0];
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

    void computerMove() {
        // Check for winning moves
        for (int i = 0; i < 3; ++i) {
            for (int j = 0; j < 3; ++j) {
                if (board[i][j] == ' ') {
                    board[i][j] = currentPlayer;
                    if (checkWinner() == currentPlayer) {
                        computerMoves.push_back({i, j});
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
                        computerMoves.push_back({i, j});
                        return;
                    }
                    board[i][j] = ' '; // Undo the move
                }
            }
        }

        // If no winning or blocking moves, make a random move
        srand(time(0));
        int x, y;
        do {
            x = rand() % 3;
            y = rand() % 3;
        } while (board[x][y] != ' ');

        board[x][y] = currentPlayer;
        computerMoves.push_back({x, y});
    }
};

void printMenu() {
    cout << "===== Tic Tac Toe =====" << endl;
    cout << "1. Play Tic Tac Toe" << endl;
    cout << "2. Quit" << endl;
    cout << "Enter your choice: ";
}

int main() {
    char choice;
    do {
        printMenu();
        cin >> choice;

        switch (choice) {
            case '1': {
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
                        game.computerMove();
                        winner = game.checkWinner();
                        if (winner != ' ' || game.isBoardFull()) break;
                        game.switchPlayer();
                    }
                }

                game.printBoard();
                if (winner == 'X') cout << "Congratulations! You win!" << endl;
                else if (winner == 'O') cout << "Computer wins! Better luck next time!" << endl;
                else cout << "It's a tie!" << endl;

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
>>>>>>> Stashed changes
