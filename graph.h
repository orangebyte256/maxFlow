#ifndef GRAPH_H
#define GRAPH_H

typedef struct Vertex
{
	int id;
	int inCount;
	int outCount;
	int *inVerteces;
	int *outVerteces;
	int been;
} Vertex;

#endif