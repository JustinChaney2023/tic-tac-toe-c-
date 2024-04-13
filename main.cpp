#include <iostream>
#include <string>
#include <ctime>
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
    char winner = ' ';

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

    for (int i = 0; i < 3; i++)
    {
        for (int j = 0; j < 3; j++)
        {
            if (board[i][j] == ' ')
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
    srand(time(0));
    int x, y;

    if (checkFreeSpaces() > 0)
    {
        do
        {
            x = rand() % 3;
            y = rand() % 3;
        } while (board[x][y] != ' ');

        board[x][y] = COMPUTER;
    }
}

// Function to check if there's a winner
char checkWinner()
{
    // Check rows
    for (int i = 0; i < 3; i++)
    {
        if (board[i][0] == board[i][1] && board[i][0] == board[i][2] && board[i][0] != ' ')
        {
            return board[i][0];
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
        cout << "IT'S A TIE!" << endl;
    }
}
