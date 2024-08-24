#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include "Queue.h"
#define HANDLE_CHECK if (hQueue == NULL) return FAILURE;
#define POINTER_BUILD Queue* pQueue = (Queue*)hQueue;

typedef struct node
{
    int data;
    struct node* next;
}Node;
typedef struct queue
{
    Node* back;
    Node* front;
    int size;
}Queue;
//Helper function, can only work if the linked list has a size of 2 or more
Node* getSecondToLastNode(Queue* pQueue)
{
    // Handle the case where the list is empty or has only one element
    if (pQueue->back == NULL || pQueue->back == pQueue->front)
    {
        return NULL; // No second-to-last node exists
    }

    Node* secondLast = pQueue->back;

    while (secondLast->next && secondLast->next != pQueue->front)
    {
        secondLast = secondLast->next;
    }
    return secondLast;
}

int getSize(QUEUE hQueue)
{
    HANDLE_CHECK POINTER_BUILD
        return pQueue->size;
}
int getFront(QUEUE hQueue)
{
    HANDLE_CHECK  POINTER_BUILD
    if (pQueue->size == 0)
        return -1;
    return pQueue->front->data;
}
QUEUE queueInit(void)
{
    Queue* pQueue = (Queue*)malloc(sizeof(Queue));
    pQueue->size = 0;
    pQueue->back = NULL;
    pQueue->front = NULL;
    return (QUEUE)pQueue;
}
STATUS queueInsert(QUEUE hQueue, int input)
{

    HANDLE_CHECK POINTER_BUILD
        if (pQueue->back == NULL)
        {
            //size would be 0 in this case//pQueue->back isn't null immediately before this line, perhaps not properly reset between test cases
            pQueue->back = (Node*)malloc(sizeof(Node));
            if (!(pQueue->back))
                return FAILURE;
            (*pQueue->back).data = input;
            (*pQueue->back).next = NULL;
            pQueue->size = 1;
            pQueue->front = pQueue->back;
            return SUCCESS;
        }

        else
        {
            Node* pNewNode = (Node*)malloc(sizeof(Node));
            if (!pNewNode)
                return FAILURE;
            pNewNode->data = input;
            pNewNode->next = pQueue->back;
            pQueue->back = pNewNode;
            pQueue->size++;
            return SUCCESS;
        }

}
STATUS queueService(QUEUE hQueue)
{
    HANDLE_CHECK POINTER_BUILD

        if (pQueue->size == 0)
            return FAILURE; // No element to remove

    Node* temp = pQueue->front;
    if (pQueue->size == 1)//size seems to be unjustly incremented at the start of each test case
    {
        pQueue->front = pQueue->back = NULL; // Queue is now empty
    }
    else
    {
        Node* secondLast = getSecondToLastNode(pQueue);//looks like the node being pointed to here has incorrect data but its next pointer does indeed point to the last node
        pQueue->front = secondLast;
        secondLast->next = NULL;
    }
    free(temp);
    pQueue->size--;
    return SUCCESS;
}

STATUS queueDestroy(QUEUE* phQueue)
{
    if (!phQueue)
        return FAILURE;
    Queue* pQueue = (Queue*)(*phQueue);
    Node* current = pQueue->back;
    {
        Node* temp;
        while (current)
        {
            temp = current->next;
            free(current);
            current = temp;
        }
    }
    free(pQueue);
    phQueue = NULL;
    return SUCCESS;

}