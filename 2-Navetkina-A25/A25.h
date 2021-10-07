#pragma once

#ifdef __cplusplus
extern "C" {
#endif // !__cplusplus


#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <malloc.h>
#define MAX_STR 15
#define NO_MATCH 0
#define MATCH 1
#define ERROR -1
#define EMPTY_ELEMENT 2
#define SUCCESS 1
#define ADD_TO_END 2
#pragma warning(disable: 4996)

	typedef struct {                                            //структура фиo человека
		char lastName[MAX_STR], name[MAX_STR], middleName[MAX_STR];
	} person_t;

	typedef struct Node                                         //узел, где хранятся данные 
	{
		person_t person;
		struct Node* next;
	} node_t;

	node_t* AddnewwNodeToEnd(node_t* head, node_t* neww);

	int WriteStringToNode(char* string, node_t* neww);

	node_t* AddToList(node_t* head, node_t* neww);

	int FreeList(node_t* head);

	node_t* Compare(node_t* head, char* findLastname, char* findName, char* findMiddlename);

#ifdef __cplusplus
}
#endif