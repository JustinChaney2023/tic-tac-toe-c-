#include <iostream>
#include <cstdlib> // For rand() and srand()
#include <ctime>   // For time()
#include <vector>  // For storing past moves
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
void resetBoard();
void printBoard();
void printPastMoves(char mode);
int checkFreeSpaces();
void playerMove();
void player2Move();
void computerMove();
char checkWinner();
void printWinner(char winner, char chosenMode);

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
                    cout << endl;
                    cout << "\n"
                         << endl;
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
                    cout << endl;
                    cout << "\n"
                         << endl;
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

                winner = checkWinner();
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

void computerMove()
{
    int row, column;
    while (true)
    {
        // Generate random row and column indices
        row = rand() % 3;
        column = rand() % 3;

        // Check if the selected position is empty
        if (board[row][column] == ' ')
        {
            board[row][column] = COMPUTER;
            computerMoves.push_back(make_pair(row, column));
            break;
        }
    }
}

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
