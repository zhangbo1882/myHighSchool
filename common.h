#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include <limits.h>
#include "type.h"
#define SIZE 1000001
#define HASH_SIZE 1000000
extern int64 array[SIZE];

void printArray(int64 array[], int size);
int readData(int64 array[], int size, char *fileName);
void swap(int64 a[], int m, int n);

