#ifndef __MY_INFO_H__
#define __MY_INFO_H__




#define ___LEVEL 8

// 数字越大越紧急
#define ___LEVEL_SHOW_ALL  0
#define ___LEVEL_ERROR     1
#define ___LEVEL_WARN	   2
#define ___LEVEL_INFO 	   3
#define ___LEVEL_SHOW_NONE 8
	
#define ___debug(level,format,...) { if(level >= ___LEVEL){printf(format,##__VA_ARGS__);} }
#define my_info(format,...) ___debug(___LEVEL_INFO,format,##__VA_ARGS__)
#define my_error(format,...) ___debug(___LEVEL_ERROR,format,##__VA_ARGS__)




#endif




