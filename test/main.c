#include <stdlib.h>
#include <stdio.h>
#include <math.h>
#include <memory.h>

#define max 100

int main()
{
	FILE *f = fopen("input.txt", "w");
	int first = 0;
	int second = 0;
	int length = 0;
	int i = 0;
	int j = 0;
	int arr[100] = { 0 };
	fprintf(f, "vertex\n");
	for (i = 0; i < max; i++)
	{
		fprintf(f,"%d\n", i + 1);
	}
	fprintf(f, "edge\n");
	for (i = 0; i < max; i++)
	{
		for (j = 0; j < max / 2; j++)
		{
			int num = 0;
			do
			{
				num = rand() % max;
			} while ((arr[num]) || (i == num));
			arr[num] = 1;
			fprintf(f, "%d %d %d\n", i + 1, num + 1, rand() % 50 + 1);
		}
		memset(arr, 0, sizeof(arr));
	}
	fclose(f);
	return 0;
}