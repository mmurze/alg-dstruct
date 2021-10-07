#include "A25.h"

int main()
{
	FILE* text = fopen("TEXT.txt", "r");
	if (text == NULL)
	{
		perror("\nfile doen't open");
		return ERROR;
	}

	char* string = malloc(sizeof(char) * 3 * MAX_STR);
	if (string == NULL)
	{
		perror("\nnot enough memory");
		return ERROR;
	}

	node_t* head = NULL;
	while (!feof(text))
	{
		fgets(string, 3 * MAX_STR, text);
		node_t* neww = (node_t*)malloc(sizeof(node_t));
		if (neww == NULL)
		{
			perror("error of memory");
			return ERROR;
		}
		int cheak = WriteStringToNode(string, neww);
		if (!cheak)
		{
			printf("\nwas error in WriteStringToNode");
			return ERROR;
		}
		head = AddToList(head, neww);
	}
	node_t* tmp = head;
	while (tmp != NULL)
	{
		printf("%10s, %10s, %10s\n", &(tmp->person.lastName), tmp->person.name, tmp->person.middleName);
		tmp = tmp->next;
	}

	printf("Put here your FIO in form: \"Lasnname Name Middlename\" (if you want miss some name, you can just push whitespace\n");
	fgets(string, 3 * MAX_STR, stdin);
	node_t* zero = (node_t*)malloc(sizeof(node_t));             //одноразка, чтобы просто вставить в функцию
	if (zero == NULL)
	{
		perror("error of memory");
		return -1;
	}

	WriteStringToNode(string, zero);
	head = Compare(head, zero->person.lastName, zero->person.name, zero->person.middleName);

	while (head != NULL)
	{
		printf("%10s, %10s, %10s\n", &(head->person.lastName), head->person.name, head->person.middleName);
		head = head->next;
	}

	FreeList(head);
	free(zero);
	free(string);
	fclose(text);
	return 0;
}