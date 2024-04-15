#include <iostream>
#include <cstdlib> // For rand() and srand()
#include <ctime>   // For time()
#include <vector>  // For storing past moves
#include <climits> // For INT_MIN and INT_MAX
using namespace std;

// Define the board
char board[3][3] = {
        {' ', ' ', ' '},
        {' ', ' ', ' '},
        {' ', ' ', ' '}};

// Define constants for players
const char PLAYER = 'X';
const char COMPUTER = 'O'; // Computer is also 'O'
auto currentPlayer = PLAYER;
auto currentPlayerPvP = PLAYER; // Player vs Player current player
auto currentPlayerPvC = PLAYER; // Player vs Computer current player

// Store past moves for both players
vector<pair<int, int>> playerMoves;
vector<pair<int, int>> computerMoves;

// Function declarations
void resetBoard(); // Resets the game board
void printBoard(); // Prints the current state of the game board
void printPastMoves(char mode); // Prints the past moves made by players
int checkFreeSpaces(); // Checks the number of empty spaces left on the board
void playerMove(); // Handles player's move in Player vs Player mode
void player2Move(); // Handles player's move in Player vs Computer mode
void computerMove(); // Calculates and executes the computer's move
char checkWinner(); // Checks if there is a winner or if the game is a draw
void printWinner(char winner, char chosenMode); // Prints the winner or a draw message
int minimax(char board[3][3], int depth, bool isMaximizing, int alpha, int beta); // Minimax algorithm to determine the best move for the computer

int main()
{
    char winner, playAgain;

    // Seed the random number generator
    srand(time(nullptr));

    // Outer loop to handle returning to the main menu
    do
    {
        char chosenMode = '0'; // Initialize with an invalid value

        if (chosenMode == '0')
        {
            // Display the game title and menu
            cout << " _   _      _             _             \n"
                    "| | (_)    | |           | |            \n"
                    "| |_ _  ___| |_ __ _  ___| |_ ___   ___ \n"
                    "| __| |/ __| __/ _` |/ __| __/ _ \\ / _ \\\n"
                    "| |_| | (__| || (_| | (__| || (_) |  __/\n"
                    " \\__|_|\\___|\\__\\__,_|\\___|\\__\\___/ \\___|\n"
                    "\n"
                    "\"============= Tic Tac Toe =============\"\n"
                 << endl;

            cout << "Select game mode:" << endl;
            cout << "1. Player vs Player" << endl;
            cout << "2. Player vs Computer" << endl;
            cout << "3. Quit" << endl;
            cout << "Enter your choice: ";
            cin >> chosenMode;

            switch (chosenMode)
            {
                case '1':
                    cout << "Mode chosen: Player vs Player" << endl;
                    break;
                case '2':
                    cout << "Mode chosen: Player vs Computer" << endl;
                    break;
                case '3':
                    cout << "Exiting the game. Thanks for playing! :D" << endl;
                    return 0; // Exit the program
                default:
                    cout << "Invalid choice. Please choose again." << endl;
                    continue; // Go back to the beginning of the outer loop
            }
        }

        // Inner loop for playing the game
        do
        {
            resetBoard(); // Reset the game board
            currentPlayer = PLAYER;         // Reset the current player
            currentPlayerPvP = PLAYER;     // Reset the current player for Player vs Player mode
            currentPlayerPvC = PLAYER;    // Reset the current player for Player vs Computer mode

            // Clear past moves
            playerMoves.clear();
            computerMoves.clear();

            // Game loop
            do
            {
                if (chosenMode == '1')
                {
                    // Display the current board and past moves in Player vs Player mode
                    cout << endl;
                    cout << "\n" << endl;
                    printBoard();
                    printPastMoves(chosenMode);
                    if (currentPlayerPvP == PLAYER)
                    {
                        cout << "Player 1's Moves (X): ";
                        playerMove();
                    }
                    else
                    {
                        cout << "Player 2's Moves (O): ";
                        player2Move();
                    }
                }
                else if (chosenMode == '2')
                {
                    // Display the current board and past moves in Player vs Computer mode
                    cout << endl;
                    cout << "\n" << endl;
                    printBoard();
                    printPastMoves(chosenMode);
                    if (currentPlayerPvC == PLAYER)
                    {
                        cout << "Player's Moves (X): ";
                        playerMove();
                    }
                    else
                    {
                        cout << "Computer's Moves (O): ";
                        computerMove();
                    }
                }

                winner = checkWinner(); // Check if there's a winner or draw
                if (chosenMode == '1')
                {
                    currentPlayerPvP = (currentPlayerPvP == PLAYER) ? 'O' : PLAYER;
                }
                else if (chosenMode == '2')
                {
                    currentPlayerPvC = (currentPlayerPvC == PLAYER) ? COMPUTER : PLAYER;
                }

            } while (winner == ' ' && checkFreeSpaces() > 0); // Continue game loop until a winner is found or there are no more free spaces

            // Print final board and winner
            cout << endl;
            cout << "Final Board:" << endl;
            printBoard();
            printPastMoves(chosenMode);
            printWinner(winner, chosenMode);

            // Ask to play again
            cout << "Do you want to play again? (Y/N): ";
            cin >> playAgain;

        } while (playAgain == 'Y' || playAgain == 'y');

    } while (true); // Keep asking for mode choice until the user selects to quit
}

// Reset the game board to its initial state
void resetBoard()
{
    for (auto &i : board)
    {
        for (char &j : i)
        {
            j = ' ';
        }
    }
}

// Print the current state of the game board
void printBoard()
{
    cout << endl;
    cout << "   |   |   " << endl;
    cout << " " << board[0][0] << " | " << board[0][1] << " | " << board[0][2] << endl;
    cout << "---|---|---" << endl;
    cout << " " << board[1][0] << " | " << board[1][1] << " | " << board[1][2] << endl;
    cout << "---|---|---" << endl;
    cout << " " << board[2][0] << " | " << board[2][1] << " | " << board[2][2] << endl;
    cout << "   |   |   " << endl;
}

// Print the past moves made by players
void printPastMoves(char mode)
{
    cout << "Past Moves:" << endl;
    if (mode == '1') // Player vs Player mode
    {
        cout << "Player 1 (X): ";
        for (auto &move : playerMoves)
        {
            cout << "(" << move.first + 1 << "," << move.second + 1 << ") ";
        }
        cout << endl;
        cout << "Player 2 (O): ";
        for (auto &move : computerMoves)
        {
            cout << "(" << move.first + 1 << "," << move.second + 1 << ") ";
        }
    }
    else if (mode == '2') // Player vs Computer mode
    {
        cout << "Player's Moves (X): ";
        for (auto &move : playerMoves)
        {
            cout << "(" << move.first + 1 << "," << move.second + 1 << ") ";
        }
        cout << endl;
        cout << "Computer's Moves (O): ";
        for (auto &move : computerMoves)
        {
            cout << "(" << move.first + 1 << "," << move.second + 1 << ") ";
        }
    }
    cout << endl;
}

// Check the number of empty spaces left on the board
int checkFreeSpaces()
{
    int freeSpaces = 0;

    for (auto &i : board)
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

// Handle player's move in Player vs Player mode
void playerMove()
{
    int row, column;
    while (true)
    {
        cout << "Enter Row and Column #(1-3): ";
        cin >> row;
        if (row < 1 || row > 3)
        {
            cout << "Invalid input. Please enter a number between 1 and 3." << endl;
            continue;
        }

        cin >> column;
        if (column < 1 || column > 3)
        {
            cout << "Invalid input. Please enter a number between 1 and 3." << endl;
            continue;
        }

        row--;
        column--;

        if (board[row][column] != ' ')
        {
            cout << "Tile is full, try again." << endl;
        }
        else
        {
            board[row][column] = PLAYER;
            playerMoves.push_back(make_pair(row, column));
            break;
        }
    }
}

// Handle player's move in Player vs Computer mode
void player2Move()
{
    int row, column;
    while (true)
    {
        cout << "Enter Row and Column #(1-3): ";
        cin >> row;
        if (row < 1 || row > 3)
        {
            cout << "Invalid input. Please enter a number between 1 and 3." << endl;
            continue;
        }

        cin >> column;
        if (column < 1 || column > 3)
        {
            cout << "Invalid input. Please enter a number between 1 and 3." << endl;
            continue;
        }

        row--;
        column--;

        if (board[row][column] != ' ')
        {
            cout << "Tile is full, try again." << endl;
        }
        else
        {
            board[row][column] = 'O';
            computerMoves.push_back(make_pair(row, column));
            break;
        }
    }
}

// Check if there is a winner or if the game is a draw
char checkWinner()
{
    for (auto &i : board)
    {
        if (i[0] == i[1] && i[0] == i[2] && i[0] != ' ')
        {
            return i[0];
        }
    }

    for (int i = 0; i < 3; i++)
    {
        if (board[0][i] == board[1][i] && board[0][i] == board[2][i] && board[0][i] != ' ')
        {
            return board[0][i];
        }
    }

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

// Minimax algorithm to determine the best move for the computer
int minimax(char board[3][3], int depth, bool isMaximizing, int alpha, int beta)
{
    char winner = checkWinner();

    // If the game is over, return the score
    if (winner == COMPUTER) {
        return 10;
    } else if (winner == PLAYER) {
        return -10;
    } else if (checkFreeSpaces() == 0) {
        return 0; // Draw
    }

    // If maximizing player's turn (computer)
    if (isMaximizing) {
        int bestScore = INT_MIN;
        for (int i = 0; i < 3; ++i) {
            for (int j = 0; j < 3; ++j) {
                if (board[i][j] == ' ') {
                    board[i][j] = COMPUTER;
                    int score = minimax(board, depth + 1, false, alpha, beta);
                    board[i][j] = ' '; // Undo move
                    bestScore = max(bestScore, score);
                    alpha = max(alpha, score);
                    if (beta <= alpha) {
                        break; // Beta cutoff
                    }
                }
            }
        }
        return bestScore;
    } else { // Minimizing player's turn (opponent)
        int bestScore = INT_MAX;
        for (int i = 0; i < 3; ++i) {
            for (int j = 0; j < 3; ++j) {
                if (board[i][j] == ' ') {
                    board[i][j] = PLAYER;
                    int score = minimax(board, depth + 1, true, alpha, beta);
                    board[i][j] = ' '; // Undo move
                    bestScore = min(bestScore, score);
                    beta = min(beta, score);
                    if (beta <= alpha) {
                        break; // Alpha cutoff
                    }
                }
            }
        }
        return bestScore;
    }
}

// Execute the computer's move
void computerMove()
{
    int bestScore = INT_MIN;
    pair<int, int> bestMove = {-1, -1};

    // Traverse all cells, evaluate minimax function for all empty cells.
    for (int i = 0; i < 3; ++i) {
        for (int j = 0; j < 3; ++j) {
            if (board[i][j] == ' ') {
                board[i][j] = COMPUTER;
                int score = minimax(board, 0, false, INT_MIN, INT_MAX);
                board[i][j] = ' '; // Undo move
                if (score > bestScore) {
                    bestScore = score;
                    bestMove = {i, j};
                }
            }
        }
    }

    // Make the best move found by the minimax algorithm
    board[bestMove.first][bestMove.second] = COMPUTER;
    computerMoves.push_back(bestMove);
}

// Print the winner or a draw message
void printWinner(char winner, char chosenMode)
{
    if (chosenMode == '1') // Player vs Player mode
    {
        if (winner == PLAYER)
        {
            cout << "Player 1 wins!" << endl;
        }
        else if (winner == 'O')
        {
            cout << "Player 2 wins!" << endl;
        }
        else
        {
            cout << "          IT'S A TIE!\n"
                    "       |\\_,,,---,,_\n"
                    "ZZZzz /,`.-'`'    -.  ;-;;,_\n"
                    "     |,4-  ) )-,_. ,\\ (  `'-'\n"
                    "    '---''(_/--'  `-'\\_)" << endl;
        }
    }
    else if (chosenMode == '2') // Player vs Computer mode
    {
        if (winner == PLAYER)
        {
            cout << "Congratulations! You win!" << endl;
        }
        else if (winner == COMPUTER)
        {
            cout << "Computer wins! Better luck next time!" << endl;
        }
        else
        {
            cout << "          IT'S A TIE!\n"
                    "       |\\_,,,---,,_\n"
                    "ZZZzz /,`.-'`'    -.  ;-;;,_\n"
                    "     |,4-  ) )-,_. ,\\ (  `'-'\n"
                    "    '---''(_/--'  `-'\\_)" << endl;
        }
    }
}
