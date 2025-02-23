#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <time.h>
#include "windows.h"
#include <assert.h>
#pragma warning(disable: 4996)

int n;
int** tree;
int* was;
int* queue;
int count = 0;

typedef struct {
	int own;
	int* add;
	int count;
}node;

node* ListCreate(int n)
{
	node* list = malloc(sizeof(node) * n);
	for (int i = 0; i < n; i++)
	{
		list[i].add = NULL;
		list[i].own = 0;
		list[i].count = 0;
	}
	return list;
}

int searchI(int* list, int n, int count) 
{
	for (int i = 0; i < count; i++)
		if (list[i] == n) return 0;
	return n;
}

void AddI(node* list, int i, int n) 
{
	if (list[i].add == NULL) 
	{
		list[i].add = malloc(sizeof(int));
		list[i].add[0] = n;
		list[i].count++;
	}

	int isInadd = searchI(list[i].add, n, list[i].count);
	if (isInadd)
	{
		int count = list[i].count + 1;
		list[i].add = realloc(list[i].add, sizeof(int) * count);
		if (list[i].add != NULL) 
		{
			list[i].add[count - 1] = n;
			list[i].count++;
		}
		else perror("Realloc error!\n");
	}
}

void ReadList(FILE * file, node* list, int n) 
{
	int j = 0, k = 0;
	while (feof(file) == 0)
	{
		fscanf(file, "%d %d\n", &j, &k);
		list[j].own = j;
		list[k].own = k;
		AddI(list, k, j);
		AddI(list, j, k);
	}
	return;
}

void FreeList(node* list, int n) 
{
	for (int i = 0; i < n; i++) 
		free(list[i].add);
	
	free(list);
}

void DFS(node* list, int n, int point, int* res, int* res_count) 
{
	for (int i = 0; i < list[point].count; i++)
	{
		int new_point = searchI(res, list[point].add[i], *res_count);
		if (new_point) 
		{
			res[*res_count] = new_point;
			(*res_count)++;
			DFS(list, n, new_point, res, res_count);
		}
	}
}

void PrintIarr(int* res, int count)
{
	for (int i = 0; i < count; i++)
		printf("%d ", res[i]);
}

void stress_test(int n) {

	node* list = ListCreate(n);
	int width = 40;
	for (int i = 0; i < n; i++) 
	{
		for (int j = 0; j < width; j++)
		{
			AddI(list, i, j);
			AddI(list, j, i);
		}
	}
	int* result_list = malloc(sizeof(int) * n);
	if (result_list == NULL)
		return;
	result_list[0] = 0;
	int result_count = 1, start = 0;
	double start_time = clock();
	DFS(list, n, start, result_list, &result_count);
	double time = 0;
	time = (double)((double)clock() - start_time) / CLOCKS_PER_SEC;
	printf("%lf\n", time);

	free(list);
	free(result_list);
}
int main(void) {
	stress_test(5000);

	int n = 0, i = 0, res_count = 1;
	int* res = NULL;
	FILE* file = fopen("test.txt", "r");
	//FILE* file  = stdin;
	if (fscanf(file, "%d", &n) < 0) {
		perror("Scan failed!");
		return 1;
	}
	node* list = ListCreate(n);
	if (!list) return 1;
	ReadList(file, list, n);
	res = malloc(sizeof(int) * n);
	if (res) {
		res[0] = 0;
		DFS(list, n, 0, res, &res_count);
		PrintIarr(res, res_count);
	}
	FreeList(list, n);
	return 0;
}