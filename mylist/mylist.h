#ifndef __MY_LIST_H__
#define __MY_LIST_H__


typedef struct _MyList{
    void           *data;
    struct _MyList *pre;
    struct _MyList *next;
}MyList;


MyList *creatList();
int  listLength(MyList *head);
void *listDataAt(MyList *head,int index);
int  listAppend(MyList *head,void *data,int data_size);
void listRemoveFirst(MyList *head);
void listPop(MyList *head);
void listClear(MyList *head);
void freeList(MyList **head);


#endif

