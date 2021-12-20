#pragma once 
#pragma warning(disable: 4996)
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#define F 0
#define T 1
typedef struct {
	int* field;
	int n;
	int isSolved;
}sudoku_t;
int checkCell(sudoku_t sudoku, int value, int cell);
void solveSudoku(sudoku_t* sudoku, int value, int cell);
void readField(sudoku_t* sudoku);
void writeField(sudoku_t sudoku);