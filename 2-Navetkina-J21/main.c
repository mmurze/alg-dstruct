#include <stdlib.h>
#include <stdio.h>
#include <string.h>

node* table;
const int size = 546378;

typedef struct 
{
	char* str;
	int key;
} node;

void HashTable(void)
{
	table = (node*)malloc(size * sizeof(node));
	if (table == NULL)
		return;
	for (int i = 0; i < size; i++)
	{
		table[i].str = NULL;
		table[i].key = 0;
	}
}

int MakeHash(const char* str, int iter)
{
	int h = 42;
	int h1 = 0;
	for (int i = 0; str[i] != '\0'; i++)
		h1 = h * h1 + str[i];
	h1 = h1 % size;
	int h2 = (int)(h1 + iter) % size;
	return h2;
}

int Find(const char* str)
{
	int h = MakeHash(str, 0);
	int i = 0;
	while (table[h].str != NULL && i < size)
	{
		if (!table[h].key && strcmp(table[h].str, str) == 0) 
			return 1;
		i++;
		h = MakeHash(str, i);
	}
	return 0;
}

void Add(const char* str) 
{
	int i = 0;
	int h = MakeHash(str, 0);
	int first_key = -1;
	while (table[h].str != NULL && i < size)
	{
		if (strcmp(table[h].str, str) == 0 && !table[h].key) 
			return;
		
		if (table[h].key && first_key == -1) 
			first_key = h;
		
		i++;
		h = MakeHash(str, i);
	}

	if (first_key != -1) 
	{
		table[first_key].str = (char*)malloc((strlen(str) + 1) * sizeof(char));
		strcpy(table[first_key].str, str);
		table[first_key].key = 0;
	}
	else 
	{
		table[h].str = (char*)malloc((strlen(str) + 1) * sizeof(char));
		strcpy(table[h].str, str);
	}
}

void Remove(const char* str)
{
	int h = MakeHash(str, 0);
	int i = 0;
	while (table[h].str != NULL && i < size) 
	{
		if (strcmp(table[h].str, str) == 0 && !table[h].key) 
		{
			table[h].key = 1;
			return;
		}
		i++;
		h = MakeHash(str, i);
	}
}

void DestroyHashTable(void)
{
	if (table == NULL)
		return;

	for (int i = 0; i < size; i++)
		free(table[i].str);

	free(table);
	table = NULL;
}

int main() {
	HashTable();
	char command;
	char value[10000];
	while (scanf("%c", &command) > 0)
	{
		if (command == 'a')
		{
			scanf("%s", &value);
			Add(value);
		}
		if (command == 'f') 
		{
			scanf("%s", &value);
			if (Find(value))
				printf("%s", "yes\n");
			else
				printf("%s", "no\n");
		}
		if (command == 'r') 
		{
			scanf("%s", &value);
			Remove(value);
		}
	}
	DestroyHashTable();
	return 0;
}