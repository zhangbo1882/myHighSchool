#include "aaron.h"
Queue *queueInit()
{
	return listInit();
}

int queueEnqueue(Queue *queue, void *data)
{
	return listInsertNext(queue, queue->tail, data);
}

int queueDequeue(Queue *queue, void **data)
{
	return listDeleteNext(queue, NULL, data);
}

void *queuePeek(Queue *queue)
{
	return queue->head;
}

int queueSize(Queue *queue)
{
	return queue->size;
}

int queueDestory(Queue* queue)
{
	return listDestory(queue);

}
