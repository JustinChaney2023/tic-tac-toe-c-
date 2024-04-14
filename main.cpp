#include <iostream>
#include <string>
#include <ctime>
#include <limits>
using namespace std;

// Define the board
char board[3][3] = {
    {' ', ' ', ' '},
    {' ', ' ', ' '},
    {' ', ' ', ' '}
};

// Define constants for players
const char PLAYER = 'X';
const char COMPUTER = 'O';
auto currentPlayer = PLAYER;

// Function declarations
void resetBoard();
void printBoard();
int checkFreeSpaces();
void playerMove();
void computerMove();
char checkWinner();
void printWinner(char);

int main()
{
    char winner, response;

    // Main game loop
    do
    {
        resetBoard();
        currentPlayer = PLAYER; // Set currentPlayer to PLAYER initially
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

        cout << "Would you like to play again? (Y/N): ";
        cin >> response;

    } while (response == 'Y' || response == 'y');

    cout << "Thanks for playing! :D" << endl;

    return 0;
}

void resetBoard()
{
    for(auto & i : board)
    {
        for(char & j : i)
        {
            j = ' '; // when resetBoard() is called each element of the array will be an empty space
        }
    }
}

#include <cstdlib> // Include the header for system()

// Function to print the board
void printBoard()
{
    // Print the board
    cout << "   |   |   " << endl;
    cout << " " << board[0][0] << " | " << board[0][1] << " | " << board[0][2] << endl;
    cout << "---|---|---" << endl;
    cout << " " << board[1][0] << " | " << board[1][1] << " | " << board[1][2] << endl;
    cout << "---|---|---" << endl;
    cout << " " << board[2][0] << " | " << board[2][1] << " | " << board[2][2] << endl;
    cout << "   |   |   " << endl;

    // Print player's moves
    cout << endl << "Player's moves (X): ";
    for (int i = 0; i < 3; i++)
    {
        for (int j = 0; j < 3; j++)
        {
            if (board[i][j] == PLAYER)
            {
                cout << "(" << i + 1 << ", " << j + 1 << ") ";
            }
        }
    }

    cout << endl << "Computer's moves (O): ";
    for (int i = 0; i < 3; i++)
    {
        for (int j = 0; j < 3; j++)
        {
            if (board[i][j] == COMPUTER)
            {
                cout << "(" << i + 1 << ", " << j + 1 << ") ";
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

// Function for player's move with input validation
void playerMove()
{
    int row, column;
    while (true)
    {
        cout << "Enter Row #(1-3): ";
        if (!(cin >> row) || row < 1 || row > 3)
        {
            cout << "Invalid input for row. Please enter a number between 1 and 3." << endl;
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            continue;
        }

        cout << "Enter Column #(1-3): ";
        if (!(cin >> column) || column < 1 || column > 3)
        {
            cout << "Invalid input for column. Please enter a number between 1 and 3." << endl;
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            continue;
        }

        row--; // Decrement by 1 to convert from 1-3 to 0-2
        column--; // Decrement by 1 to convert from 1-3 to 0-2

        if (board[row][column] != ' ')
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
                "       |\\_,,,---,,_\n"
                "ZZZzz /,`.-'`'    -.  ;-;;,_\n"
                "     |,4-  ) )-,_. ,\\ (  `'-'\n"
                "    '---''(_/--'  `-'\\_)" << endl;
    }
}