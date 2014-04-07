#define _CRTDBG_MAP_ALLOC
#include <crtdbg.h>

#include <stdio.h>
#include <memory.h>
#include <string.h>
#include <stdlib.h>

#include "extendArray.h"
#include "queue.h"

#define VERTEXNAME "vertex"
#define EDGENAME "edge"
#define STARTENDNAME "startend"
#define MAXVALUE 1000000

int **dynamicArrayInit(int width, int height)
{
	int *array = calloc(width * height, sizeof(int));
	int **parray = calloc(height, sizeof(int*));
	int i = 0;
	for (i = 0; i < height; i++)
		parray[i] = array + width * i;
	return parray;
}

void dynamicArrayFree(int **value)
{
	free(*value);
	free(value);
}

void readFile(const char *name, ExtendArray *theExtendArray,int *max,int ***capacity, int *start, int *end)
{
	int id = 0;
	int first = 0;
	int second = 0;
	int length = 0;
	char s[255] = "";
	typedef enum State
	{
		NONE, VERTEX, EDGE,	STARTEND
	} State;
	State state = NONE;
	char *pos = NULL;

	FILE *f = fopen(name, "r");
	if (f == NULL)
		return;
	*max = 0;
	while (fgets(s, 255, f) != NULL)
	{
		if ((pos = strchr(s, '\n')) != NULL)
			*pos = '\0';
		if (strcmp(s, VERTEXNAME) == 0)
		{
			state = VERTEX;
			continue;
		}
		if (strcmp(s, STARTENDNAME) == 0)
		{
			state = STARTEND;
			continue;
		}
		if (strcmp(s, EDGENAME) == 0)
		{
			state = EDGE;
			(*capacity) = dynamicArrayInit(*max, *max);
			continue;
		}
		switch (state)
		{
		case NONE:
			continue;
		case VERTEX:
			sscanf(s, "%d", &id);
			if (id > 0)
				extendArrayPush(theExtendArray, id);
			if (id > *max)
				*max = id;
			break;
		case EDGE:
			sscanf(s, "%d %d %d", &first, &second, &length);
			if ((first > 0) && (second > 0))
			{
				extendArrayPushVertexIn(theExtendArray, first, second);
				extendArrayPushVertexOut(theExtendArray, second, first);
				(*capacity)[first - 1][second - 1] = length;
			}
			break;
		case STARTEND:
			sscanf(s, "%d %d", start, end);
			break;
		default:
			break;
		}
	}
	fclose(f);
}


int maxFlow(ExtendArray *theExtendArray, int start, int finish, int max, int **capacity)
{
	int i = 0;
	int result = 0;
	Vertex *vertex = NULL;
	Queue *queue = queueInit();
	int **flow = dynamicArrayInit(max, max);
	int *mark = calloc(max, sizeof(int));
	int *push = calloc(max, sizeof(int));
	int *sign = calloc(max, sizeof(int));
	int *parent = calloc(max, sizeof(int)); 
	int isFind = 0;
	queuePush(queue, &theExtendArray->array[start - 1]);
	memset(*flow, 0, sizeof(max * max * sizeof(int)));
	memset(mark, 0, max * sizeof(int));
	memset(push, 0, max * sizeof(int));
	memset(parent, 0, max * sizeof(int));
	push[start - 1] = MAXVALUE;
	while (queueIsEmpty(queue) != 1)
	{
		vertex = queuePop(queue);
		if (theExtendArray->array[vertex->id - 1].been)
			continue;
		theExtendArray->array[vertex->id - 1].been = 1;
		if (vertex->id == finish)
		{
			int now = finish;
			while (now != start)
			{
//				printf("%d ", now);
				if (sign[now - 1] == 1)
				{
					flow[parent[now - 1] - 1][now - 1] += push[finish - 1];
				}
				else
				{
					flow[now - 1][parent[now - 1] - 1] -= push[finish - 1];
				}
				now = parent[now - 1];
			}
//			printf("%d\n", start);
			while (queuePop(queue) != NULL);
			queuePush(queue, &theExtendArray->array[start - 1]);
			memset(mark, 0, max * sizeof(int));
			memset(push, 0, max * sizeof(int));
			memset(parent, 0, max * sizeof(int));
			isFind = 0;
			for (i = 0; i < max; i++)
			{
				theExtendArray->array[i].been = 0;
			}
			push[start - 1] = MAXVALUE;
			continue;
		}
		for (i = 0; i < vertex->inCount; i++)
		{
			if (theExtendArray->array[vertex->inVerteces[i] - 1].been)
				continue;
			if (!mark[theExtendArray->array[vertex->inVerteces[i] - 1].id - 1])
			{
				if (flow[vertex->id - 1][vertex->inVerteces[i] - 1] == capacity[vertex->id - 1][vertex->inVerteces[i] - 1])
					continue;
				if (capacity[vertex->id - 1][vertex->inVerteces[i] - 1] > flow[vertex->id - 1][vertex->inVerteces[i] - 1])
				{
					mark[theExtendArray->array[vertex->inVerteces[i] - 1].id - 1] = 1;
					push[vertex->inVerteces[i] - 1] = min(push[vertex->id - 1], capacity[vertex->id - 1][vertex->inVerteces[i] - 1] - flow[vertex->id - 1][vertex->inVerteces[i] - 1]);
					queuePush(queue, &theExtendArray->array[vertex->inVerteces[i] - 1]);
					sign[vertex->inVerteces[i] - 1] = 1;
					parent[vertex->inVerteces[i] - 1] = vertex->id;
					continue;
				}
			}
		}
		for (i = 0; i < vertex->outCount; i++)
		{
			if (vertex->id == start)
				break;
			if (theExtendArray->array[vertex->outVerteces[i] - 1].id == finish)
				continue;
			if (theExtendArray->array[vertex->outVerteces[i] - 1].been)
				continue;
			if (!mark[theExtendArray->array[vertex->outVerteces[i] - 1].id - 1])
			{
				if (flow[vertex->id - 1][vertex->outVerteces[i] - 1] == 0)
					continue;
				if (0 < flow[vertex->id - 1][vertex->outVerteces[i] - 1])
				{
					mark[theExtendArray->array[vertex->outVerteces[i] - 1].id - 1] = 1;
					push[vertex->outVerteces[i] - 1] = min(push[vertex->id - 1], flow[vertex->id - 1][vertex->outVerteces[i] - 1]);
					queuePush(queue, &theExtendArray->array[vertex->outVerteces[i] - 1]);
					sign[vertex->outVerteces[i] - 1] = -1;
					parent[vertex->outVerteces[i] - 1] = vertex->id;
					continue;
				}
			}
		}
	}
	for (i = 0; i < max; i++)
		result += flow[i][finish - 1];
	free(mark);
	free(push);
	free(sign);
	free(parent);
	dynamicArrayFree(flow);
	dynamicArrayFree(capacity);
	queueDelete(queue);
	return result;
}


int main(void)
{
	ExtendArray *vertex = extendArrayInit();
	int max = 0;
	int **capacity = NULL;
	int start = 1;
	int end = 1;
	_CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF);
	readFile("input.txt", vertex, &max, &capacity, &start, &end);
	printf("result = %d", maxFlow(vertex, start, end, max, capacity));
	extendArrayDelete(vertex);
	return 0;
}