#include <stdio.h> 
#include <stdbool.h>

void choosePos(char board[3][3], int pos, int O, int X, int isTurn); // function prototype
bool isGameOver(char board[3][3], char O, char X, int *scoreO, int *scoreX, int i, int j); // function prototype
bool isTie(char board[3][3], char O, char X, int i, int j); // function prototype
void whoStart(int *isBegin, bool *isTurn); // function prototype
int moreGame();  // function prototype
void printBoard(char board[3][3], int i, int j); // function prototype
void resetBoard(char board[3][3]); // function prototype

char board[3][3] = {{'1', '2', '3'}, {'4', '5', '6'}, {'7', '8', '9'}}; // board 2D array
int i = 0, j = 0, pos = 0, scoreO = 0, scoreX = 0, newGame = 0, isBegin = 0; // indexes, scores, is new game, is game began
char O = 'O', X = 'X'; // 2 chars
bool isTurn = true, end = false, isStart = false; // is turn, is the game en, is the game start

/**
 * 21 lines
 * main method 
 * @return int
*/
int main() {
    while (true) {
        if (!isStart) {
            whoStart(&isBegin, &isTurn); // call method to choose who start the game
            isStart = true;
        }
        printBoard(board, i, j); // cal method to print the board
        choosePos(board, pos, O, X, isTurn); // the player that have the turn choose position
        end = isGameOver(board, O, X, &scoreO, &scoreX, i, j); // store true if game over, else false in a boolean variable
        if (end) {
            printf("\nthe score is\nO - %d\nX - %d", scoreO, scoreX);
            newGame = moreGame(); // store true if more game, else false in a boolean variable
            if (newGame == 2) {
                break;
            }
            isStart = false;
            break; // Add this line to exit the while loop after the game is over
        }
        isTurn = !isTurn;
    }
    printf("game over");
    return 0;
}

// int main() {
//     while (true) {
//         if (!isStart) {
//             whoStart(&isBegin, &isTurn); // call method to choose who start the game
//             isStart = true;
//         }
//         printBoard(board, i, j); // cal method to print the board
//         choosePos(board, pos, O, X, isTurn); // the player that have the turn choose position
//         end = isGameOver(board, O, X, &scoreO, &scoreX, i, j); // store true if game over, else false in a boolean variable
//         if (end) {
//             printf("\nthe score is\nO - %d\nX - %d", scoreO, scoreX);
//             newGame = moreGame(); // store true if more game, else false in a boolean variable
//             if (newGame == 2) {
//                 break;
//             }
//             isStart = false;
//         }
//         isTurn = !isTurn;
//     }
//     printf("game over");
//     return 0;
// }

/**
 * 36 lines
 * choose pos
 * @return void 
*/
void choosePos(char board[3][3], int pos, int O, int X, int isTurn) {
    printf("choose pos ");
    scanf("%d", &pos);
    while (pos < 1 || pos > 9 || (board[(pos - 1) / 3][(pos - 1) % 3] == O) ||
          (board[(pos - 1) / 3][(pos - 1) % 3] == X)) {
        printf("Invalid position or position already taken. Please choose another position: ");
        scanf("%d", &pos);
    }
    int row = (pos - 1) / 3;
    int col = (pos - 1) % 3;

    if (isTurn) {
        if (pos == 1) board[0][0] = O;
        if (pos == 2) board[0][1] = O;
        if (pos == 3) board[0][2] = O;
        if (pos == 4) board[1][0] = O;
        if (pos == 5) board[1][1] = O;
        if (pos == 6) board[1][2] = O;
        if (pos == 7) board[2][0] = O;
        if (pos == 8) board[2][1] = O;
        if (pos == 9) board[2][2] = O;
    } else if (!isTurn) {
        if (pos == 1) board[0][0] = X;
        if (pos == 2) board[0][1] = X;
        if (pos == 3) board[0][2] = X;
        if (pos == 4) board[1][0] = X;
        if (pos == 5) board[1][1] = X;
        if (pos == 6) board[1][2] = X;
        if (pos == 7) board[2][0] = X;
        if (pos == 8) board[2][1] = X;
        if (pos == 9) board[2][2] = X;
    }
}

/**
 * 26 lines
 * check if game over
 * @return true if yes, else false
*/
bool isGameOver(char board[3][3], char O, char X, int *scoreO, int *scoreX, int i, int j) {
    if (board[0][0] == O && board[0][1] == O && board[0][2] == O ||
        board[1][0] == O && board[1][1] == O && board[1][2] == O ||
        board[2][0] == O && board[2][1] == O && board[2][2] == O ||
        board[0][0] == O && board[1][1] == O && board[2][2] == O ||
        board[0][2] == O && board[1][1] == O && board[2][0] == O) {
            (*scoreO)++; // increase by 1 the score for O
            printf("\nO won");
            return true;
        }
    if (board[0][0] == X && board[0][1] == X && board[0][2] == X ||
        board[1][0] == X && board[1][1] == X && board[1][2] == X ||
        board[2][0] == X && board[2][1] == X && board[2][2] == X ||
        board[0][0] == X && board[1][1] == X && board[2][2] == X ||
        board[0][2] == X && board[1][1] == X && board[2][0] == X) {
            (*scoreX)++; // increase by 1 the score for X
            printf("\nX won");
            return true;
        }
    if (isTie(board, O, X, i, j)) { // if the board is full and no one won, return true
        printf("\nthe game is tie");
        return true;
    }
    return false;
}

/**
 * 9 lines
 * check if tie game
 * @return true if tie, else false
*/
bool isTie(char board[3][3], char O, char X, int i, int j) {
    for (i = 0; i < 3; i++) {
        for (j = 0; j < 3; j++) {
            if (board[i][j] != O && board[i][j] != X) 
                return false;
        }
    }
    return true;
}

/**
 * 14 lines
 * check who start the game
 * @return void
*/
void whoStart(int *isBegin, bool *isTurn) {
    printf("who start the game?\nO - 1\nX - 2\n");
        scanf("%d", isBegin);
        while (*isBegin < 1 || *isBegin > 2)
        {
            printf("enter a valid answer");
            printf("who start the game?\nO - 1\nX - 2");
            scanf("%d", isBegin);
        }
        if (*isBegin == 1) {
            *isTurn = true;
        } else {
            *isTurn = false;
        }
}

/**
 * 14 lines
 * more game
 * @return 1 if yes, else 2
*/
int moreGame() {
    int newGame = 0;
    printf("\nAnother game?\nyes - 1\nno  - 2\n");
        scanf("%d", &newGame);
        while (newGame < 1 || newGame > 2) 
        {
            printf("enter a valid answer");
            printf("Another game?\nyes - 1\nno - 2");
            scanf("%d", &newGame);
        }
        if (newGame == 1) {
            resetBoard(board); // call method to send the board to the start point
        }
        return newGame;      
}

/**
 * 8 lines
 * print the board game
 * @return void
*/
void printBoard(char board[3][3], int i, int j) {
    for (i = 0; i < 3; i++)
    {
        for(j = 0; j < 3; j++) {
            printf("\t%c  ", board[i][j]);
        }
        printf("\n");
    }
}

/**
 * 10 lines
 * reset the board to the beginning point
 * @return void
*/
void resetBoard(char board[3][3]) {
    board[0][0] = '1';
    board[0][1] = '2';
    board[0][2] = '3';
    board[1][0] = '4';
    board[1][1] = '5';
    board[1][2] = '6';
    board[2][0] = '7';
    board[2][1] = '8';
    board[2][2] = '9';
}