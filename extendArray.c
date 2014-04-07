#include "extendArray.h"
#include <stdlib.h>

ExtendArray *extendArrayInit(void)
{
	ExtendArray *temp = calloc(1, sizeof(ExtendArray));
	return temp;
}

void extendArrayPush(ExtendArray *theExtendArray, int id)
{
	if (id > theExtendArray->size)
	{
		int i = 0;
		theExtendArray->array = realloc(theExtendArray->array, id * sizeof(Vertex));
		for (i = theExtendArray->size; i < id; i++)
		{
			theExtendArray->array[i].inCount = 0;
			theExtendArray->array[i].outCount = 0;
			theExtendArray->array[i].id = -1;
			theExtendArray->array[i].inVerteces = NULL;
			theExtendArray->array[i].outVerteces = NULL;
			theExtendArray->array[i].been = 0;
		}
		theExtendArray->size = id;
	}
	if (theExtendArray->array[id - 1].id == -1)
		theExtendArray->array[id - 1].id = id;
	return;
}

void extendArrayPushVertexIn(ExtendArray *theExtendArray, int id, int idVertex)
{
	int i = 0;
	int isFind = 0;
	for (i = 0; i < theExtendArray->array[id - 1].inCount; i++)
	{
		if (theExtendArray->array[id - 1].inVerteces[i] == idVertex)
			isFind = 1;
	}
	if (isFind == 0)
	{
		theExtendArray->array[id - 1].inVerteces = realloc(theExtendArray->array[id - 1].inVerteces, (theExtendArray->array[id - 1].inCount + 1) * sizeof(int));
		theExtendArray->array[id - 1].inVerteces[theExtendArray->array[id - 1].inCount] = idVertex;
		theExtendArray->array[id - 1].inCount++;
	}
}

void extendArrayPushVertexOut(ExtendArray *theExtendArray, int id, int idVertex)
{
	int i = 0;
	int isFind = 0;
	for (i = 0; i < theExtendArray->array[id - 1].outCount; i++)
	{
		if (theExtendArray->array[id - 1].outVerteces[i] == idVertex)
			isFind = 1;
	}
	if (isFind == 0)
	{
		theExtendArray->array[id - 1].outVerteces = realloc(theExtendArray->array[id - 1].outVerteces, (theExtendArray->array[id - 1].outCount + 1) * sizeof(int));
		theExtendArray->array[id - 1].outVerteces[theExtendArray->array[id - 1].outCount] = idVertex;
		theExtendArray->array[id - 1].outCount++;
	}
}

void extendArrayDelete(ExtendArray *theExtendArray)
{
	int i = 0;
	for (i = 0; i < theExtendArray->size; i++)
	{
		if (theExtendArray->array[i].inCount > 0)
			free(theExtendArray->array[i].inVerteces);
		if (theExtendArray->array[i].outCount > 0)
			free(theExtendArray->array[i].outVerteces);
	}
	free(theExtendArray->array);
	free(theExtendArray);
}
