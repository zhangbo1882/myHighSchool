#include "common.h"
long long f(int array[], int count)
{
	int *first = NULL;
	int *sec = NULL;
	int *result = NULL;
	int i = 0, j = 0, k = 0;
	long long left = 0, right = 0, split = 0;
	int mid = count/2;
//	printf("\narrary count %d: \n", count);
//	printArray(array, count);
	if(count == 1)
		return 0;
	left = f(array, mid);
	right = f(array + mid, count - mid);
   	first = (int *)malloc(mid * sizeof(int));
	sec = (int *)malloc((count - mid)* sizeof(int));
	if(first == NULL || sec == NULL)
	{
		printf("error\n");
		return 0;
	}
	for(i = 0 ;i < mid; i++)
	{
		first[i] = array[i];
	}
	for(j = 0; j < (count - mid); j++)
	{
		sec[j] = array[mid+j];
	}
	i = 0;
	j = 0;
//	printf("\nbegin split : \n");
//	printArray(array, count);
//	printf("first array : \n");
//	printArray(first, mid);
//	printf("secondary array :\n");
//	printArray(sec, count - mid);
	for(k = 0; k < count; k++)
	{
		if(first[i] <= sec[j])
		{
			array[k] = first[i];
			i++;
			if(i == mid)
				break;
		}
		else
		{
			array[k] = sec[j];
			j++;
			split += mid - i;
			if(j == (count - mid))
			{
				array[k+1] = first[i];
				i++;
				for(j = k+2; j < count; j++,i++)
				{
					array[j] = first[i];
				}
				break;
			}
		}
	}
//	printf("\nsplit : %d\n", split);
	return split + left + right;
	
}
long long  f1(int array[], int count)
{
	int i = 0, j = 0;
	long long number  = 0;
	for(i; i < count; i++)
	{
		for(j = i + 1; j < count; j++)
		{
			if(array[i] > array[j])
				number++;
		}
	}
	return number;

}
