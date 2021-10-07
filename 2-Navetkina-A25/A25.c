#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <malloc.h>
#include "A25.h"


node_t* AddnewwNodeToEnd(node_t* head, node_t* neww)        //add need node to the end of list
{
	if (head == NULL)
	{
		node_t* one = (node_t*)malloc(sizeof(node_t));
		if (one == NULL)
		{
			perror("error of memory");
			return NULL;
		}
		one->next = NULL;
		one->person = neww->person;
		head = one;
		return head;
	}

	if (neww == NULL)
		return NULL;

	node_t* tmp = head;
	while (tmp->next != NULL)
		tmp = tmp->next;

	node_t* one = neww;
	one->person = neww->person;
	tmp->next = one;
	one->next = NULL;
	return head;
}

int WriteStringToNode(char* string, node_t* neww)             //write string to node
{
	if (string == NULL)
	{
		printf("empty buffer\n");
		return ERROR;
	}
	if (neww == NULL)  // если нам закинули пустой узел
	{
		printf("not enough memory\n");
		return ERROR;
	}

	int i = 0, j = 0, k = 0;
	char lastName[MAX_STR], name[MAX_STR], middleName[MAX_STR];
	char t;

	while ((t = string[i]) != ' ')                            //read string until meeting ewhitespace
	{
		if (i > MAX_STR)
		{
			printf("overflow\n");
			return ERROR;
		}
		lastName[i] = t;
		i++;
	}
	lastName[i] = '\0';
	i++;                                                      //it's for missing empty space

	while ((t = string[i]) != ' ')
	{
		if (k > MAX_STR)
		{
			printf("overflow\n");
			return ERROR;
		}
		name[k] = t;
		k++;
		i++;
	}
	name[k] = '\0';
	i++;

	while ((t = string[i]) != '\0')
	{
		if (j > MAX_STR)
		{
			printf("overflow\n");
			return ERROR;
		}
		middleName[j] = t;
		j++;
		i++;
	}
	if (j > 0 && middleName[j - 1] == '\n')
		middleName[j - 1] = '\0';
	else
		middleName[j] = '\0';

	strcpy(neww->person.lastName, lastName);                   //add strings to node
	strcpy(neww->person.name, name);
	strcpy(neww->person.middleName, middleName);

	return SUCCESS;
}

node_t* AddToList(node_t* head, node_t* neww)                  //write the node to the right place
{
	if (neww == NULL)
	{
		printf("tried to add empty element\n");
		return NULL;
	}

	node_t* tmp = head;
	if (tmp == NULL)                                           //head пустой и neww становится первым узлом
	{
		neww->next = NULL;
		head = neww;
		return head;
	}

	node_t* last = NULL;
	while (tmp != NULL)
	{
		int lastName = strcmp(neww->person.lastName, tmp->person.lastName);
		int name = strcmp(neww->person.name, tmp->person.name);
		int middleName = strcmp(neww->person.middleName, tmp->person.middleName);

		if (lastName < 0)
		{
			if (last == NULL)                                  //if tmp - is head, it's mean that we need add newwNode to the top of the list
			{
				neww->next = tmp;
				head = neww;
				return head;
			}
			last->next = neww;
			neww->next = tmp;
			return head;
		}
		else if (lastName == 0 && name < 0)
		{
			if (last == NULL)                                 //if tmp - is head, it's mean that we need add newwNode to the top of the list
			{
				neww->next = tmp;
				head = neww;
				return head;
			}
			last->next = neww;
			neww->next = tmp;
			return head;
		}
		else if (lastName == 0 && name == 0 && middleName < 0)
		{
			if (last == NULL)                                 //if tmp - is head, it's mean that we need add newwNode to the top of the list
			{
				neww->next = tmp;
				head = neww;
				return head;
			}
			last->next = neww;
			neww->next = tmp;
			return head;
		}
		last = tmp;                                           //  go to the next node (there is no coincidences) 
		tmp = tmp->next;
	}
	last->next = neww;                                        // if we are here, so newwNode is added to the end of the list  
	neww->next = NULL;
	return head;
}

int FreeList(node_t* head)    
{
	if (head != NULL)
	{
		while (head->next != NULL)
		{
			node_t* t = head;
			head = head->next;
			free(t);
		}
		return SUCCESS;
	}
	else
		return ERROR;
}

node_t* Compare(node_t* head, char* findLastname, char* findName, char* findMiddlename) //getting a sorted array
{
	if (head == NULL)
	{
		printf("empty list\n");
		return NULL;
	}
	node_t* tmp = head;
	node_t* needed = NULL;

	char l, n, m;
	if ((l = findLastname[0]) == '\0' && (n = findLastname[0]) == '\0' && (m = findLastname[0]) == '\0')
		return head;

	while (tmp != 0)
	{
		int matchL = 0;
		int i = 0;
		for (i, matchL; *(findLastname + i) != '\0'; i++)             //compair lastname and needed string
			if (findLastname[i] == *(tmp->person.lastName + i))
				matchL++;
		if (matchL == i)
			matchL = 1;
		else
			matchL = 0;

		int matchN = 0;
		for (i = 0, matchN; *(findName + i) != '\0'; i++)             //compair name and needed string
			if (findName[i] == *(tmp->person.name + i))
				matchN++;
		if (matchN == i)
			matchN = 1;
		else
			matchN = 0;

		int matchM = 0;
		for (i = 0, matchM; *(findMiddlename + i) != '\0'; i++)       //compair middlename and needed string
			if (findMiddlename[i] == *(tmp->person.middleName + i))
				matchM++;
		if (matchM == i)
			matchM = 1;
		else
			matchN = 0;

		if (matchN * matchL * matchM)                                 //if all of this match
			needed = AddnewwNodeToEnd(needed, tmp);
		tmp = tmp->next;
	}
	head = needed;
	return head;
}

