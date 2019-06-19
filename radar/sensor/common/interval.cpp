#include <stdio.h>
#include "interval.h"


// 获取时间戳的差值
int time_interval(struct timeval *tv)
{
    if((tv->tv_sec == 0) && (tv->tv_usec == 0)){
        gettimeofday(tv,NULL);
        return 0;
    }
    struct timeval now={0};
    gettimeofday(&now,NULL);
    int ret = (now.tv_sec - tv->tv_sec)*1000 + (now.tv_usec-tv->tv_usec)/1000;
    gettimeofday(tv,NULL);
    return ret;
}



