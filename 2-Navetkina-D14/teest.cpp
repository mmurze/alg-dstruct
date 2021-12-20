#include "pch.h"
#include "sudoku.h"
#include "SudokuMain.c"

int testResult(FILE* out, FILE* expected)
{
	if (!out) 
	{
		perror("");
		return 0;
	}
	if (!expected) 
	{
		perror("");
		return 0;
	}
	fseek(out, 0, SEEK_END);
	fseek(expected, 0, SEEK_END);
	fseek(out, 0, SEEK_SET);
	fseek(expected, 0, SEEK_SET);
	if (ftell(out) != ftell(expected)) 
	{
		fclose(out);
		fclose(expected);
		return 0;
	}
	int val = -1;
	int exp = -1;
	while ((fscanf(out, "%d ", &val) > 0) && (fscanf(expected, "%d ", &exp) > 0)) 
	{
		if (val != exp)
		{
			fclose(out);
			fclose(expected);
			return 0;
		}
	}
	return 1;
}

TEST(SudokuTest, sudoku_solved_4x4) 
{
	FILE* inputF = fopen("input.txt", "w");

	fprintf(inputF, "2\n"\
		"0 2 3 4\n"\
		"3 0 2 1\n"\
		"2 1 0 3\n"\
		"4 3 1 0\n"\
	);

	inputF = freopen("input.txt", "r", inputF);

	sudoku_t sudoku;
	readField(&sudoku);
	solveSudoku(&sudoku, 1, 0);
	if (sudoku.isSolved == T)
		writeField(sudoku);

	inputF = freopen("input.txt", "w", inputF);

	fprintf(inputF, "2\n"\
		"1 2 3 4\n"\
		"3 4 2 1\n"\
		"2 1 4 3\n"\
		"4 3 1 2\n"\
	);

	inputF = freopen("input.txt", "r", inputF);
	FILE* outputF = fopen("output.txt", "r");

	EXPECT_TRUE(testResult(outputF, inputF));
}

TEST(SudokuTest, sudoku_is_solved)
{
	FILE* inputF = fopen("input.txt", "w");

	fprintf(inputF, "2\n"\
		"1 2 3 4\n"\
		"3 4 2 1\n"\
		"2 1 4 3\n"\
		"4 3 1 2\n"\
	);

	inputF = freopen("input.txt", "r", inputF);

	sudoku_t sudoku;
	readField(&sudoku);
	solveSudoku(&sudoku, 1, 0);
	if (sudoku.isSolved == T)
		writeField(sudoku);

	inputF = freopen("input.txt", "w", inputF);
	fprintf(inputF, "2\n"\
		"1 2 3 4\n"\
		"3 4 2 1\n"\
		"2 1 4 3\n"\
		"4 3 1 2\n"\
	);

	inputF = freopen("input.txt", "r", inputF);
	FILE* outputF = fopen("output.txt", "r");

	EXPECT_TRUE(testResult(outputF, inputF));
}

TEST(SudokuTest, sudoku_solved_9x9)
{
	FILE* inputF = fopen("input.txt", "w");

	fprintf(inputF, "3\n"\
		"1 0 3 0 5 0 7 0 9\n" \
		"4 5 6 7 8 9 1 2 3\n" \
		"7 8 9 1 2 3 4 5 6\n" \
		"2 1 4 3 6 5 8 9 7\n" \
		"3 6 5 8 9 7 2 1 4\n" \
		"8 9 7 2 1 4 3 6 5\n" \
		"5 3 1 6 4 2 9 7 8\n" \
		"6 4 2 9 7 8 5 3 1\n" \
		"9 7 8 5 3 1 6 4 2" \
	);

	inputF = freopen("input.txt", "r", inputF);

	sudoku_t sudoku;
	readField(&sudoku);
	solveSudoku(&sudoku, 1, 0);
	if (sudoku.isSolved == T)
		writeField(sudoku);

	inputF = freopen("input.txt", "w", inputF);

	fprintf(inputF, "3\n"\
		"1 2 3 4 5 6 7 8 9 \n" \
		"4 5 6 7 8 9 1 2 3 \n" \
		"7 8 9 1 2 3 4 5 6 \n" \
		"2 1 4 3 6 5 8 9 7 \n" \
		"3 6 5 8 9 7 2 1 4 \n" \
		"8 9 7 2 1 4 3 6 5 \n" \
		"5 3 1 6 4 2 9 7 8 \n" \
		"6 4 2 9 7 8 5 3 1 \n" \
		"9 7 8 5 3 1 6 4 2 \n" \
	);

	inputF = freopen("input.txt", "r", inputF);
	FILE* outputF = fopen("output.txt", "r");

	EXPECT_TRUE(testResult(outputF, inputF));
}