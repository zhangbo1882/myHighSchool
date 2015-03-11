#include "common.h"
#define PIVOT_TYPE_FIRST 1
#define PIVOT_TYPE_LAST 2
#define PIVOT_TYPE_MEDIAN 3

int pivotSelectFirst(int a[], int size)
{
	return 0;
}
int pivotSelectLast(int a[], int size)
{
	return size - 1;
}
int pivotSelectMedian(int a[], int size)
{
	int mid;
	if(size % 2 == 1)
		mid = size/2;
	else
		mid = size/2 - 1;
	
	if(a[0] <= a[mid])
	{
		if(a[0] >= a[size - 1])
			return 0;
		else
			return (a[mid] < a[size -1]) ? mid : (size - 1);
	}
	else
	{
		if(a[mid] >= a[size-1])
			return mid;
		else
			return (a[0] >= a[size -1]) ? (size - 1): 0;
	}
			
}
int pivotSelect(int a[], int size, int pivotType)
{
	int index = 0;
	switch(pivotType)
	{
		case PIVOT_TYPE_FIRST:
			index = pivotSelectFirst(a, size);
			break;
		case PIVOT_TYPE_LAST:
			index = pivotSelectLast(a, size);
			break;
		case PIVOT_TYPE_MEDIAN:
			index = pivotSelectMedian(a, size);
			break;
	}
	return index;
}
int partition(int a[], int size, int pivotType)
{
	int pivotIndex = pivotSelect(a, size, pivotType);
	int i = 1,j =1;
	swap(a, 0, pivotIndex);
	for(j; j < size; j++)
	{
		if(a[j] < a[0])
		{
			swap(a, i, j);
			i++;
		}
	}
	swap(a, 0, i-1);
	return i - 1;
}
int quickSort(int array[], int size, int pivotType)
{
	int leftCount = 0, rightCount = 0, total = 0;
	int split;
	if(size == 1 || size == 0)
		return 0;
	split = partition(array, size, pivotType);
	/*if split is 0, the array is sorted, teminate the sort
	if(split == 0)
		return size - 1;
	*/
	leftCount = quickSort(array, split, pivotType);
	rightCount =  quickSort(array+split+1, size - split - 1, pivotType);
	total = size - 1 + leftCount + rightCount;
	return total;
}
