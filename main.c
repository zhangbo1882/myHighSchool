#include "common.h"
#include "aaron.h"
int main(int argc ,char *argv[])
{
	char fileName[1024] = {0};
	int size;
	hashTable *myHash = NULL;
	int64 begin = -10000, end = 10000;
	if(argc != 2)
	{
		printf("input the data file name\n");
		return -1;
	}
	strncpy(fileName, argv[1], 1024);
	printf("file is %s\n", fileName);

	size = readData(array, SIZE, fileName);
	if(size < 0)
	{
		printf("read data fail\n");
		return -1;
	}
	//printArray(array, size);
	printf("read data success, array size %d, hashSize: %d\n", size, HASH_SIZE);
	myHash = createHashTable(HASH_SIZE, myHashFunc, myCompareFunc);
	printf("hash table created\n");
	hashInit(myHash, array, size);
	printf("hash table init\n");
	twoSumCount(array, size,begin, end, myHash);
	return 0 ;
}
