#include "pch.h"
#include "A25.h"

TEST(AddnewwNodeToEnd, AddnewwNodein_Empty_Head)        
{
	node_t* head = nullptr;
	node_t* cheak = nullptr;
	node_t* cheakNULL = nullptr;
	node_t* neww = (node_t*)malloc(sizeof(node_t));
	cheak = AddnewwNodeToEnd(head, neww);
	ASSERT_TRUE(cheak != cheakNULL);                // add new node to beginning of the list, so i
	free(neww);
}

TEST(AddnewwNodeToEnd, Addneww_Empty_NodeinHead)
{
	node_t* head = (node_t*)malloc(sizeof(node_t));
	if (head != NULL)
	{
		node_t* cheak = nullptr;
		node_t* cheakNULL = nullptr;
		node_t* neww = nullptr;
		cheak = AddnewwNodeToEnd(head, neww);
		ASSERT_TRUE(cheak == cheakNULL);
		free(head);
	}
}

TEST(AddnewwNodeToEnd, AddnewwNodeToEnd_Success)
{
	node_t* head = (node_t*)malloc(sizeof(node_t));
	node_t* head2 = (node_t*)malloc(sizeof(node_t));
	node_t* head3 = (node_t*)malloc(sizeof(node_t));

	
	// we get that head3->head2->NULL and head is separately
	if (head != NULL && head2 != NULL && head3 != NULL)
	{
		char l[MAX_STR] = "Navetkina", n[MAX_STR] = "Irina", m[MAX_STR] = "Sergeevna";
		strcpy(head->person.lastName, l);
		strcpy(head->person.name, n);
		strcpy(head->person.middleName, m);
		head->next = NULL;

		char l2[MAX_STR] = "Ivanov", n2[MAX_STR] = "Nikolay", m2[MAX_STR] = "Petrovich";
		strcpy(head2->person.lastName, l2);
		strcpy(head2->person.name, n2);
		strcpy(head2->person.middleName, m2);
		head2->next = NULL;

		char l3[MAX_STR] = "Ivanov", n3[MAX_STR] = "Boris", m3[MAX_STR] = "Crecovich";
		strcpy(head3->person.lastName, l3);
		strcpy(head3->person.name, n3);
		strcpy(head3->person.middleName, m3);
		head3->next = head2;

		head3 = AddnewwNodeToEnd(head3, head);
		ASSERT_TRUE(head3->next->next == head);
		free(head);
		free(head2);
		free(head3);
	}
}



TEST(WriteStringToNode, Write_Empty_StringToNode)
{
	char* string = nullptr;
	person_t neww = { "L", "N", "M" };
	node_t* head = (node_t*)malloc(sizeof(node_t));
	if (head != nullptr)
	{
		head->person = neww;
		int cheak = WriteStringToNode(string, head);
		ASSERT_TRUE(cheak == ERROR);
		free(head);
	}
}

TEST(WriteStringToNode, Write_Overflou_StringToNode)
{
	char* string = nullptr;
	person_t neww = { "L", "N", "M" };
	node_t* head = (node_t*)malloc(sizeof(node_t));
	if (head != nullptr)
	{
		head->person = neww;
		string = (char*)malloc(sizeof(3 * MAX_STR + 5));
		if (string == nullptr)
		{
			string = "Helloworldhoneuy Helloworldhoneiy Helloworldhoneoy";   //names are bigger than MAX_STR
			int cheak = WriteStringToNode(string, head);
			free(string);
			free(head);
			ASSERT_TRUE(cheak == ERROR);
		}
	}
}

TEST(WriteStringToNode, WriteStringTo_Empty_Node)
{
	node_t* neww = NULL;
	char string[3 * MAX_STR + 5] = "Helloworld Helloworld Helloworld";
	int cheak = WriteStringToNode(string, neww);
	ASSERT_TRUE(cheak == ERROR);
}

TEST(WriteStringToNode, WriteStringToNode_Success)
{

	node_t* neww = (node_t*)malloc(sizeof(node_t));;
	char string[3 * MAX_STR + 5] = "Helloworld Helloworld Helloworld";
	int cheak = WriteStringToNode(string, neww);
	ASSERT_TRUE(cheak == SUCCESS);
	free(neww);
}



TEST(AddToList, AddTo_Empty_List)
{
	node_t* head = nullptr;
	node_t* neww = (node_t*)malloc(sizeof(node_t));
	if(neww!=nullptr)
	{
		node_t* cheak = AddToList(head, neww);
		ASSERT_TRUE(cheak == neww);
		free(neww);
	}
}

TEST(AddToList, AddToList_Empty_Node)
{
	node_t* neww = nullptr;
	node_t* cheakNull = nullptr;
	node_t* head = (node_t*)malloc(sizeof(node_t));
	if (head != nullptr)
	{
		node_t* cheak = AddToList(head, neww);
		ASSERT_TRUE(cheak == cheakNull);
		free(head);
	}
}

TEST(AddToList, AddToList_Success)
{
	node_t* head = (node_t*)malloc(sizeof(node_t));
	node_t* head2 = (node_t*)malloc(sizeof(node_t));
	node_t* head3 = (node_t*)malloc(sizeof(node_t));
	node_t* head4 = (node_t*)malloc(sizeof(node_t));


	// we get that head3->head2->NULL and head is separately
	if (head != NULL && head2 != NULL && head3 != NULL && head4 != NULL)
	{
		char l[MAX_STR] = "Navetkina", n[MAX_STR] = "Irina", m[MAX_STR] = "Sergeevna";
		strcpy(head->person.lastName, l);
		strcpy(head->person.name, n);
		strcpy(head->person.middleName, m);
		head->next = NULL;

		char l2[MAX_STR] = "Ivanov", n2[MAX_STR] = "Nikolay", m2[MAX_STR] = "Petrovich";
		strcpy(head2->person.lastName, l2);
		strcpy(head2->person.name, n2);
		strcpy(head2->person.middleName, m2);
		head2->next = NULL;

		char l3[MAX_STR] = "Ivanov", n3[MAX_STR] = "Boris", m3[MAX_STR] = "Crecovich";
		strcpy(head3->person.lastName, l3);
		strcpy(head3->person.name, n3);
		strcpy(head3->person.middleName, m3);
		head3->next = head2;

		char l4[MAX_STR] = "Ivanova", n4[MAX_STR] = "Karina", m4[MAX_STR] = "Pokrashena";
		strcpy(head4->person.lastName, l4);
		strcpy(head4->person.name, n4);
		strcpy(head4->person.middleName, m4);
		head4->next = head2;
		node_t* cheak = AddToList(head3, head4);
		ASSERT_TRUE(cheak->next->next == head4);
		free(head);
		free(head2);
		free(head3);
		free(head4);
	}
}


TEST(Compare, Add_EmptyHead_Compare)
{
	char l[MAX_STR] = "Lol", n[MAX_STR] = "Kek", m[MAX_STR] = "Cheburek";
	node_t* head = nullptr;
	node_t* cheak = Compare(head, l, n, m);
	ASSERT_TRUE(cheak == nullptr);
}

TEST(Compare, Add_EmptyStrings_Compare)
{
	node_t* head = (node_t*)malloc(sizeof(node_t));
	node_t* head2 = (node_t*)malloc(sizeof(node_t));
	node_t* head3 = (node_t*)malloc(sizeof(node_t));

	if (head != NULL && head2 != NULL && head3 != NULL)
	{
		char l[MAX_STR] = "Navetkina", n[MAX_STR] = "Irina", m[MAX_STR] = "Sergeevna";
		strcpy(head->person.lastName, l);
		strcpy(head->person.name, n);
		strcpy(head->person.middleName, m);
		head->next = NULL;

		char l2[MAX_STR] = "Ivanov", n2[MAX_STR] = "Nikolay", m2[MAX_STR] = "Petrovich";
		strcpy(head2->person.lastName, l2);
		strcpy(head2->person.name, n2);
		strcpy(head2->person.middleName, m2);
		head2->next = head;

		char l3[MAX_STR] = "Ivanov", n3[MAX_STR] = "Boris", m3[MAX_STR] = "Crecovich";
		strcpy(head3->person.lastName, l3);
		strcpy(head3->person.name, n3);
		strcpy(head3->person.middleName, m3);
		head3->next = head2;

		char l4[MAX_STR] = "", n4[MAX_STR] = "", m4[MAX_STR] = "";

		node_t* cheak = Compare(head3, l4, n4, m4);
		EXPECT_TRUE(cheak == head3);
		EXPECT_TRUE(cheak->next == head2);
		EXPECT_TRUE(cheak->next->next == head);
		free(head);
		free(head2);
		free(head3);
	}
}

TEST(Compare, Compare_Success)
{
	node_t* head = (node_t*)malloc(sizeof(node_t));
	node_t* head2 = (node_t*)malloc(sizeof(node_t));
	node_t* head3 = (node_t*)malloc(sizeof(node_t));

	if (head != NULL && head2 != NULL && head3 != NULL)
	{
		char l[MAX_STR] = "Navetkina", n[MAX_STR] = "Irina", m[MAX_STR] = "Sergeevna";
		strcpy(head->person.lastName, l);
		strcpy(head->person.name, n);
		strcpy(head->person.middleName, m);
		head->next = NULL;

		char l2[MAX_STR] = "Ivanov", n2[MAX_STR] = "Nikolay", m2[MAX_STR] = "Petrovich";
		strcpy(head2->person.lastName, l2);
		strcpy(head2->person.name, n2);
		strcpy(head2->person.middleName, m2);
		head2->next = head;

		char l3[MAX_STR] = "Ivanov", n3[MAX_STR] = "Boris", m3[MAX_STR] = "Crecovich";
		strcpy(head3->person.lastName, l3);
		strcpy(head3->person.name, n3);
		strcpy(head3->person.middleName, m3);
		head3->next = head2;

		char l4[MAX_STR] = "Iva", n4[MAX_STR] = "", m4[MAX_STR] = "";
		node_t* cheak = Compare(head3, l4, n4, m4);

		ASSERT_FALSE(strcmp(cheak->person.lastName, head3->person.lastName));  
		ASSERT_FALSE(strcmp(cheak->next->person.lastName, head2->person.lastName));
		free(head);
		free(head2);
		free(head3);
	}
}