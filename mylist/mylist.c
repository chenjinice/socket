#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "mylist.h"


MyList *creatList()
{
    MyList * head = (MyList *)calloc(1,sizeof(MyList));
    head->pre  = head;
    head->next = head;
    return   head;
}


int listLength(MyList *head)
{
    if(head == NULL)return;
    int len = 0;
    MyList *p = head->next;
    while(p != head){
        p = p->next;
        len++;
    }
    return len;
}


void *listDataAt(MyList *head, int index)
{
    void * data = NULL;
    if(head == NULL)return data;
    int i = 0;
    MyList *p = head->next;
    while(p != head){
        if(i == index){
            data = p->data;
            break;
        }else {
            p = p->next;
            i++;
        }
    }
    return data;
}


int listAppend(MyList *head, void *data, int data_size)
{
    if(head == NULL)return -1;
    MyList *new_list = (MyList *)calloc(1,sizeof(MyList));
    new_list->data = (void *)calloc(1,data_size);
    memcpy(new_list->data,data,data_size);

    MyList *pre = head->pre;
    pre->next = new_list;
    new_list->pre = pre;
    new_list->next = head;
    head->pre = new_list;
    return 0;
}


void listRemoveFirst(MyList *head)
{
    if(head == NULL)return;
    MyList *p = head->next;
    if(p == head)return;

    head->next->next->pre = head;
    head->next = head->next->next;
    free(p->data);
    free(p);
}


void listPop(MyList *head)
{
    if(head == NULL)return;
    MyList *p = head->pre;
    if(p == head)return;

    head->pre->pre->next = head;
    head->pre = head->pre->pre;
    free(p->data);
    free(p);
}


void listClear(MyList *head)
{
    if(head == NULL)return;
    MyList *p = head->pre;
    while (p != head) {
        MyList *pre = p->pre;
        free(p->data);
        free(p);
        p = pre;
    }
    head->pre = head;
    head->next = head;
}


void freeList(MyList **head)
{
    if(head == NULL)return;
    if(*head == NULL)return;

    listClear(*head);
    free(*head);
    *head = NULL;
}


