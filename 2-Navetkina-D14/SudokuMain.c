#include "sudoku.h"

int checkCell(sudoku_t sudoku, int value, int cell)
{
	int row = cell / sudoku.n;
	int column = cell % sudoku.n;
	int ssquare = (int)sqrt(sudoku.n);
	for (int i = 0; i < sudoku.n; i++)
	{
		if (value == sudoku.field[row * sudoku.n + i] || value == sudoku.field[i * sudoku.n + column])
			return F;
	}

	for (int i = 0; i < sudoku.n; i += ssquare)
	{
		if (i + ssquare > row)
		{
			row = i;
			break;
		}
	}

	for (int i = 0; i < sudoku.n; i += ssquare)
	{
		if (i + ssquare > column)
		{
			column = i;
			break;
		}
	}

	for (int i = 0; i < ssquare; i++)
	{
		for (int j = 0; j < ssquare; j++)
		{
			if (value == sudoku.field[(row + i) * sudoku.n + column + j])
				return F;
		}
	}
	return T;
}

void solveSudoku(sudoku_t* sudoku, int value, int cell)
{
	while (sudoku->field[cell] != 0 && cell + 1 < sudoku->n * sudoku->n)
		cell++;


	if (sudoku->field[cell] != 0)
	{
		sudoku->isSolved = T;
		return;
	}

	while (sudoku->isSolved != T && value <= sudoku->n)
	{
		if (checkCell(*sudoku, value, cell) == T)
		{
			sudoku->field[cell] = value;

			if (cell + 1 == sudoku->n * sudoku->n)
				sudoku->isSolved = T;
			else
			{
				solveSudoku(sudoku, 1, cell + 1);

				if (sudoku->isSolved != T)
					sudoku->field[cell] = 0;
			}
		}
		value++;
	}
}

void readField(sudoku_t* sudoku)
{
	FILE* f = fopen("input.txt", "r");
	if (!f)
	{
		printf("Error opening input file\n");
		exit(1);
	}

	char bufer;
	if (fscanf(f, "%d%c", &sudoku->n, &bufer) < 0)
	{
		printf("Error reading file\n");
		exit(1);
	}
	sudoku->n = sudoku->n * sudoku->n;
	sudoku->field = (int*)malloc(sudoku->n * sudoku->n * sizeof(int));

	if (!sudoku->field)
	{
		printf("Error allocating memory\n");
		exit(1);
	}
	int cheak = 0;
	for (int i = 0; i < sudoku->n * sudoku->n; i++)
	{
		if (fscanf(f, "%d%c", &sudoku->field[i], &bufer) < 0)
		{
			printf("Error reading file\n");
			exit(1);
		}
	}
	if (cheak != 0)
	{
		printf("Error reading file\n");
		exit(1);
	}
	fclose(f);
}

void writeField(sudoku_t sudoku)
{
	FILE* f = fopen("output.txt", "w");
	if (!f)
	{
		printf("Error opening file\n");
		exit(1);
	}

	fprintf(f, "%d\n", (int)sqrt(sudoku.n));
	for (int i = 0; i < sudoku.n * sudoku.n; i++)
	{
		if ((i + 1) % sudoku.n == 0)
			fprintf(f, "%d\n", sudoku.field[i]);
		else
			fprintf(f, "%d ", sudoku.field[i]);
	}
	fclose(f);
}

//int main(void)
//{
//	sudoku_t sudoku;
//	readField(&sudoku);
//	solveSudoku(&sudoku, 1, 0);
//	if (sudoku.isSolved == T)
//		writeField(sudoku);
//	else
//	{
//		FILE* f = fopen("output.txt", "w");
//		if (!f)
//		{
//			printf("Error opening output file\n");
//			exit(1);
//		}
//		fprintf(f, "0");
//		fclose(f);
//	}
//	return 0;
//}