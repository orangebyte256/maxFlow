#ifndef EXTEND_ARRAY_H
#define EXTEND_ARRAY_H

#include "graph.h"
#include <memory.h>
#include <string.h>


typedef struct ExtendArray
{
	Vertex *array;
	int size;
} ExtendArray;

ExtendArray *extendArrayInit(void);
void extendArrayPush(ExtendArray *theExtendArray, int id);
void extendArrayPushVertexIn(ExtendArray *theExtendArray, int id, int idVertex);
void extendArrayPushVertexOut(ExtendArray *theExtendArray, int id, int idVertex);
void extendArrayDelete(ExtendArray *theExtendArray);

#endif