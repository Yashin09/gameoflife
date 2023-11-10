#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <unistd.h>
#include <string.h>

#define ROWS 10
#define COLS 20

typedef int Board[ROWS][COLS];

void populateBoard(Board board) {
	for (int i = 0; i < ROWS; i++)
		for (int j = 0; j < COLS; j++)
         	board[i][j] = rand() % 2;  
}

int countNeighbors(Board board, int x, int y) {
	int sum = 0;

	for (int i = -1; i < 2; i++) {
		for (int j = -1; j < 2; j++) {

			int row = (x + i + ROWS) % ROWS;
			int col = (y + j + COLS) % COLS;

			sum += board[row][col];
		}
	}

	sum -= board[x][y];

	return sum;
}

void computeNewGen(Board board, Board next) {
	for (int i = 0; i < ROWS; i++) {
		for (int j = 0; j < COLS; j++) {
			int state = board[i][j];

			int neighbors = countNeighbors(board, i, j);

			if (state == 0 && neighbors == 3) {
				next[i][j] = 1;
			} else if (state == 1 && (neighbors < 2 || neighbors > 3)) {
				next[i][j] = 0;
			} else {
				next[i][j] = board[i][j];
			}
			
		}
	}
}

void printBoard(Board board) {
   	for (int i = 0; i < ROWS; i++) {
		for (int j = 0; j < COLS; j++) {
			if (board[i][j] == 1) {
				printf("*");
			} else {
				printf(" ");
			}
			
		}
		printf("\n");
	}
}

int main() {
	srand(time(0)); 

	Board board;
	populateBoard(board);
	Board next;
	memcpy(next, board, sizeof(board));
	Board *pboard = &board;
	Board *pnext = &next; 

	while (1) {
		system("clear");
		printBoard(*pboard);

		computeNewGen(*pboard, *pnext);

		Board *temp = pboard;
		pboard = pnext;
		pnext = temp;

		usleep(1000000/4);
	}	

	return 0;
}
