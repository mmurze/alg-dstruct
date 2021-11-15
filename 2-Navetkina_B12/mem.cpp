
#ifdef __cplusplus
extern "C" {
#endif
#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include "memallocator.h"

#define FAIL 2
#define CHECK_NUM 777             

    typedef struct descriptor {
        int size;
        struct descriptor* next;
        int check;
    } descriptor;

    typedef struct {
        int size;
    }last_t;



    char* tmpHead = NULL;
    int wholeSize = 0;
    descriptor* startHead = NULL;

    int meminit(void* givenBlock, int size)
    {
        if (!givenBlock || size <= memgetblocksize())
            return FAIL;

        tmpHead = (char*)givenBlock;
        wholeSize = size;

        startHead = (descriptor*)givenBlock;
        startHead->size = size - memgetminimumsize();
        startHead->next = NULL;
        //((last_t*)((char*)startHead + sizeof(descriptor) + startHead->size))->size = startHead->size;

        return 0;
    }

    void* memalloc(int size)
    {
        descriptor** nextDesc = &startHead;
        descriptor** freeDesc = NULL;
        descriptor* givenBlock = NULL;
        int i = 0;

        if (tmpHead == NULL || size + memgetminimumsize() > wholeSize || size < 0)
            return NULL;


        while (*nextDesc) 
        {
            if ((*nextDesc)->size >= size) 
            {
                freeDesc = nextDesc;
                i++;
                if (i == 2)
                    break;
            }
            nextDesc = &(*nextDesc)->next;
        }

        if (freeDesc == NULL)
            return NULL;


        givenBlock = *freeDesc;

        if (givenBlock->size > size + memgetminimumsize()) 
        {
            (*freeDesc) = (descriptor*)((char*)givenBlock + memgetminimumsize() + size);
            (*freeDesc)->size = givenBlock->size - memgetminimumsize() - size;
            (*freeDesc)->next = givenBlock->next;
            ((last_t*)((char*)givenBlock + givenBlock->size + sizeof(descriptor)))->size = (*freeDesc)->size;

            givenBlock->size = size;
            givenBlock->next = NULL;
            givenBlock->check = CHECK_NUM;
            ((last_t*)((char*)givenBlock + givenBlock->size + sizeof(descriptor)))->size = -1;

            return (char*)givenBlock + sizeof(descriptor);

        }

        *freeDesc = (*freeDesc)->next;
        ((last_t*)((char*)givenBlock + givenBlock->size + sizeof(descriptor)))->size = -1;
        givenBlock->next = NULL;
        givenBlock->check = CHECK_NUM;

        return (char*)givenBlock + sizeof(descriptor);

    }

    void memfree(void* p)
    {
        descriptor* freeDesc = (descriptor*)((char*)p - sizeof(descriptor));
        descriptor* head = NULL;
        last_t* last = NULL;
        descriptor** tmp = NULL;
        int relation = 0;


        if (!p || !tmpHead || ((tmpHead + wholeSize < (char*)p + sizeof(int)) || ((char*)p - sizeof(descriptor) < tmpHead)))
            return;

        if (freeDesc->check != CHECK_NUM)
            return;

        if (((last_t*)((char*)freeDesc + freeDesc->size + sizeof(descriptor)))->size > 0)
            return;

        last = (last_t*)((char*)freeDesc - sizeof(last_t));

        if (last->size != -1 && (char*)last > tmpHead) 
        {
            head = (descriptor*)((char*)last - last->size - sizeof(descriptor));
            if ((char*)head >= tmpHead) 
            {
                head->size = head->size + freeDesc->size + memgetminimumsize();
                freeDesc->check = 0;
                ((last_t*)((char*)head + head->size + sizeof(descriptor)))->size = head->size;
                freeDesc = head;
                relation = 1;
            }
        }

        head = (descriptor*)((char*)freeDesc + freeDesc->size + memgetminimumsize());

        if ((char*)head - wholeSize < tmpHead) 
        {
            last = (last_t*)((char*)head + head->size + sizeof(descriptor));
            if (last->size != -1 && (char*)last - wholeSize < tmpHead)
            {
                freeDesc->size = freeDesc->size + head->size + memgetminimumsize();
                last->size = freeDesc->size;

                tmp = &startHead;

                while ((*tmp) != NULL && (*tmp) != head)
                    tmp = &(*tmp)->next;

                *tmp = freeDesc;

                if (relation) 
                {
                    if (head->next != freeDesc)
                    {
                        if (freeDesc->next == head) 
                            freeDesc->next = head->next;
                        else 
                            *tmp = head->next;
                        
                    }
                }
                else
                    freeDesc->next = head->next;

                relation = 1;
            }
        }

        if (relation)
            return;

        else
        {
            freeDesc->next = startHead;
            startHead = freeDesc;
            ((last_t*)((char*)freeDesc + freeDesc->size + sizeof(descriptor)))->size = freeDesc->size;
        }

    }

    void memdone() 
    {
        if (wholeSize <= 0 || tmpHead == NULL || startHead!= NULL && (wholeSize == startHead->size + memgetblocksize()))
            return;
    }

    int memgetminimumsize()
    {
        return sizeof(descriptor) + sizeof(int);
    }

    int memgetblocksize() 
    {
        return sizeof(descriptor) + sizeof(int);
    }


#ifdef __cplusplus
}
#endif 