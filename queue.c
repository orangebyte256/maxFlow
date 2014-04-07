#include "queue.h"

#include <stdlib.h>

Queue *queueInit(void)
{
	Queue *temp = calloc(1, sizeof(Queue));
	return temp;
}

void queuePush(Queue *theQueue, const Vertex *value)
{
	Element *temp = calloc(1, sizeof(Element));
	temp->value = (Vertex*)value;
	if (theQueue->head == NULL)
		theQueue->head = temp;
	else
		theQueue->tail->next = temp;
	theQueue->tail = temp;
}

Vertex *queuePop(Queue *theQueue)
{
	Vertex *result = NULL;
	Element *temp = NULL;
	if (theQueue->head == NULL)
		return NULL;
	result = theQueue->head->value;
	temp = theQueue->head;
	theQueue->head = theQueue->head->next;
	free(temp);
	return result;
}

void queueDelete(Queue *theQueue)
{
	Element *it = theQueue->head;
	Element *temp = NULL;
	while (it != NULL)
	{
		temp = it->next;
		free(it);
		it = temp;
	}
	free(theQueue);
}

int queueIsEmpty(Queue *theQueue)
{
	return (theQueue->head == NULL);
}