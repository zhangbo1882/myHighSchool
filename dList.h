#ifndef _DLIST_H_
#define _DLIST_H_

typedef struct  _dListNode
{
	struct _dListNode *prev;
	struct _dListNode *next;
	void *data;
}dListNode;
typedef struct _dListLink
{
	dListNode *head;
	dListNode *tail;
	int nodeCount;
}dListLink;
dListLink *dListLinkInit();
dListNode *dListNodeCreate(void *data);
int dListLinkDestroy(dListLink *list);
int dListLinkInsertHead(dListLink *list, dListNode *p);
int dListLinkInsertTail(dListLink *list, dListNode *p);
int dListLinkInsertF(dListLink *list, dListNode *pos, dListNode *p);
int dListLinkInsertB(dListLink *list, dListNode *pos, dListNode *p);
int dListLinkDeleteHead(dListLink *list);
int dListLinkDeleteTail(dListLink *list);
int dListNodeFree(dListNode *p);
typedef void (*dListIterCB)(dListLink *list, dListNode *p);
int dListIter(dListLink *list, dListIterCB fn);
void dListLinkPrintInt(dListLink *list, dListNode *p);
void dListLinkPrintString(dListLink *list, dListNode *p);
void dListLinkPrintData(dListLink *list, dListNode *p);
#endif
