#include <unistd.h>
#include <stdio.h>

#include "mylist.h"


int main()
{
    int i = 0, count = 10;
    MyList *list = creatList();

    for(i=0;i<count;i++){
        listAppend(list,&i,sizeof(i));
    }

    printf("list len ==== %d\n",listLength(list));
    listRemoveFirst(list);
    listRemoveFirst(list);
    listPop(list);
    listPop(list);
    printf("list len ==== %d\n",listLength(list));

    for(i=0;i<count;i++){
        int *d = listDataAt(list,i);
//        if(d)printf("dd === %d\n",*d);
    }
    listClear(list);
    freeList(&list);

    return 0;
}
