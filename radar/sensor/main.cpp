#include <unistd.h>
#include <stdio.h>
#include "ars408.h"
#include <iostream>


using namespace std;

//

int main(int argc,char *argv[])
{
    char *dev = (char *)"can1";
    if(argc > 1)dev = argv[1];


    ARS408 ars(dev);
    ars.start();


    while(1)sleep(1);
    return 0;
}



