#include "common.h"
int64 array[SIZE];
void printArray(int64 array[], int size)
{
	int i;
	printf("Array is :\n");
	for(i = 0; i < size; i++)
	{
		printf("%lld  ", array[i]);
	}
	printf("\n");
}
int readData(int64 array[], int size, char *fileName)
{
	FILE *file;
	char buf[32];
	int line = 0;
	memset(array, 0, size);
	if((file = fopen(fileName, "r")) == NULL)
	{
		printf("open file %s fail\n", fileName);
		return -1;
	}
	printf("Read file(%s) success\n", fileName);
	while(fgets(buf, 32, file) != NULL)
	{
		array[line++] = atoll(buf);
		if(line >= size)
		{
			printf("array(size :%d) overflow\n", line);
			break;
		}
	}
//	printf("array size : %d\n", line);
//	printArray(array, line);
	fclose(file);
	return line;
}
void swap(int64 a[], int m, int n)
{
	int temp;
	temp = a[m];
	a[m] = a[n];
	a[n] = temp;
}
