#ifndef	__TRIGGER_ANALYSIS_H__
#define __TRIGGER_ANALYSIS_H__

#include <stdint.h>


#define TRIGGER_DEBUG


#ifdef TRIGGER_DEBUG
#define mylog(format,...)  printf("trigger_client : "format,##__VA_ARGS__)
#else
#define mylog(format,...)
#endif


void trigger_analysis(uint8_t *buffer,int len);


#endif

