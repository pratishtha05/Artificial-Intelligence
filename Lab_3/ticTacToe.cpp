#include <iostream>
#include <vector>
#include <limits>
using namespace std;

// Function to print the board
void printBoard(const vector<vector<char>>& board) {
    cout << "\n";
    for (int i = 0; i < 3; i++) {
        for (int j = 0; j < 3; j++) {
            cout << board[i][j];
            if (j < 2) cout << " | ";
        }
        cout << "\n";
        if (i < 2) cout << "---------\n";
    }
    cout << "\n";
}

// Check if there are any moves left
bool isMovesLeft(const vector<vector<char>>& board) {
    for (int i = 0; i < 3; i++)
        for (int j = 0; j < 3; j++)
            if (board[i][j] == ' ')
                return true;
    return false;
}

// Evaluate board state
int evaluate(const vector<vector<char>>& board) {
    // Checking rows
    for (int row = 0; row < 3; row++) {
        if (board[row][0] == board[row][1] &&
            board[row][1] == board[row][2]) {
            if (board[row][0] == 'X')
                return +10;
            else if (board[row][0] == 'O')
                return -10;
        }
    }

    // Checking columns
    for (int col = 0; col < 3; col++) {
        if (board[0][col] == board[1][col] &&
            board[1][col] == board[2][col]) {
            if (board[0][col] == 'X')
                return +10;
            else if (board[0][col] == 'O')
                return -10;
        }
    }

    // Checking diagonals
    if (board[0][0] == board[1][1] &&
        board[1][1] == board[2][2]) {
        if (board[0][0] == 'X')
            return +10;
        else if (board[0][0] == 'O')
            return -10;
    }

    if (board[0][2] == board[1][1] &&
        board[1][1] == board[2][0]) {
        if (board[0][2] == 'X')
            return +10;
        else if (board[0][2] == 'O')
            return -10;
    }

    // No winner
    return 0;
}

// The Minimax function
int minimax(vector<vector<char>>& board, int depth, bool isMax) {
    int score = evaluate(board);

    // If maximizer (X) has won
    if (score == 10)
        return score - depth; // Prefer faster wins

    // If minimizer (O) has won
    if (score == -10)
        return score + depth; // Prefer slower losses

    // If no moves left, it's a draw
    if (!isMovesLeft(board))
        return 0;

    if (isMax) { // Maximizer’s move (X)
        int best = numeric_limits<int>::min();

        for (int i = 0; i < 3; i++) {
            for (int j = 0; j < 3; j++) {
                if (board[i][j] == ' ') {
                    board[i][j] = 'X';
                    best = max(best, minimax(board, depth + 1, false));
                    board[i][j] = ' ';
                }
            }
        }
        return best;
    } else { // Minimizer’s move (O)
        int best = numeric_limits<int>::max();

        for (int i = 0; i < 3; i++) {
            for (int j = 0; j < 3; j++) {
                if (board[i][j] == ' ') {
                    board[i][j] = 'O';
                    best = min(best, minimax(board, depth + 1, true));
                    board[i][j] = ' ';
                }
            }
        }
        return best;
    }
}

// Find the best move for the AI
pair<int, int> findBestMove(vector<vector<char>>& board) {
    int bestVal = numeric_limits<int>::min();
    pair<int, int> bestMove = {-1, -1};

    for (int i = 0; i < 3; i++) {
        for (int j = 0; j < 3; j++) {
            if (board[i][j] == ' ') {
                board[i][j] = 'X'; // AI's move
                int moveVal = minimax(board, 0, false);
                board[i][j] = ' ';

                if (moveVal > bestVal) {
                    bestMove = {i, j};
                    bestVal = moveVal;
                }
            }
        }
    }
    return bestMove;
}

bool checkWin(const vector<vector<char>>& board) {
    int score = evaluate(board);
    return score == 10 || score == -10 || !isMovesLeft(board);
}

int main() {
    vector<vector<char>> board = {
        {' ', ' ', ' '},
        {' ', ' ', ' '},
        {' ', ' ', ' '}
    };

    cout << "TIC TAC TOE using MINIMAX\n";
    cout << "You are O, Computer is X\n";
    printBoard(board);

    while (true) {
        int row, col;
        cout << "Enter your move (row[1-3] col[1-3]): ";
        cin >> row >> col;
        row--; col--;

        if (row < 0 || row >= 3 || col < 0 || col >= 3 || board[row][col] != ' ') {
            cout << "Invalid move! Try again.\n";
            continue;
        }

        board[row][col] = 'O';
        printBoard(board);
        if (evaluate(board) == -10) {
            cout << "You win! 🎉\n";
            break;
        }
        if (!isMovesLeft(board)) {
            cout << "It's a draw!\n";
            break;
        }

        cout << "Computer is thinking...\n";
        pair<int, int> bestMove = findBestMove(board);
        board[bestMove.first][bestMove.second] = 'X';
        printBoard(board);

        if (evaluate(board) == 10) {
            cout << "Computer wins! 🤖\n";
            break;
        }
        if (!isMovesLeft(board)) {
            cout << "It's a draw!\n";
            break;
        }
    }

    return 0;
}
