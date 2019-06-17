#include <unistd.h>
#include <stdio.h>
#include "ars408.h"
#include <iostream>


using namespace std;


int main(int argc,char *argv[])
{
    char *dev = (char *)"can0";
    if(argc > 1)dev = argv[1];

    ARS408 ars(dev);
    ars.start();


//    int a = 1,i;
//    char *p = (char *)&a;
//    for(i=0;i<4;i++){
//        printf("0x%X === 0x%X\n",p+i,*(p+i));
//    }
//    printf("0x%X,0x%X,0x%X,0x%X\n",*p,*(p+1),*(p+2),*(p+3));

    while(1)sleep(1);

    return 0;
}



