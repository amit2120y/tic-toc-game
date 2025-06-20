#include <stdio.h>
#include <string.h> // memset

// Function to initialize the board
// board is in stack as | 00 | 01 | 02 | 10 | 11 | 12 | 20 | 21 | 22 | in form of array of 9 bytes/ chars
// So we can them all ' ' by a single for loop or memset
void initializeBoard(char board[3][3]) {
        for (int i = 0; i < 9; i++) {
                board[i / 3][i % 3] = ' ';
                // or
                // *((char *)board + i) = ' ';
        }
        // or
        // memset(board, ' ', 9);
}

// Function to print the board
void printBoard(char board[3][3]) {
    printf("  1 2 3\n");
    for (int i = 0; i < 3; i++) {
        printf("%d ", i + 1);
        for (int j = 0; j < 3; j++) {
            printf("%c ", board[i][j]);
        }
        printf("\n");
    }
}

// All combination by which player can win
char winCombos[][9] = {
  {1, 1, 1, 0, 0, 0, 0, 0, 0}, // first row
  {1, 0, 0, 1, 0, 0, 1, 0, 0}, // 1st column
  {1, 0, 0, 0, 1, 0, 0, 0, 1}, // (1, 1) box to (3, 3) box, diagonal
  {0, 0, 0, 1, 1, 1, 0, 0, 0},  // 2nd row
  {0, 1, 0, 0, 1, 0, 0, 1, 0}, // 2nd column
  {0, 0, 1, 0, 1, 0, 1, 0, 0}, // (1, 3) box to (3, 1) box, diagonal
  {0, 0, 0, 0, 0, 0, 1, 1, 1}, // 3rd row
  {0, 0, 1, 0, 0, 1, 0, 0, 1} // 3rd column
};
// Function to check if the current player has won
int checkWin(char board[3][3], char player) {    // Check rows and columns
  for (int probs = 0; probs < 8; probs++) {
    int matched = 0;
    for (int i = 0; i < 9; i++) {
      if (winCombos[probs][i] * player == board[i/3][i%3])
        matched++;
    }
    if (matched == 3)
      return 1; // player won
  }
  return 0; // player didn't win
}

// Function to check if the board is full
int isBoardFull(char board[3][3]) {
    for (int i = 0; i < 3; i++) {
        for (int j = 0; j < 3; j++) {
            if (board[i][j] == ' ') {
                return 0; // Board is not full
            }
        }
    }
    return 1; // Board is full
}

int main() {
    char board[3][3];
    int row, col;
    char currentPlayer = 'X';

    initializeBoard(board);

    printf("Welcome to Tic-Tac-Toe!\n");

    do {
        printBoard(board);

        // Get the player's move
        printf("Player %c, enter your move (row and column): ", currentPlayer);
        scanf("%d %d", &row, &col);
        row--;
        col--;

        // Check if the move is valid
        if (row >= 0 && row < 3 && col >= 0 && col < 3 && board[row][col] == ' ') {
            board[row][col] = currentPlayer;

            // Check if the current player has won
            if (checkWin(board, currentPlayer)) {
                printBoard(board);
                printf("Player %c wins!\n", currentPlayer);
                break;
            }

            // Check if the board is full (draw)
            if (isBoardFull(board)) {
                printBoard(board);
                printf("It's a draw!\n");
                break;
            }

            // Switch to the other player
            currentPlayer = (currentPlayer == 'X') ? 'O' : 'X';

        } else {
            printf("Invalid move. Please try again.\n");
        }

    } while (1);

    return 0;
}
