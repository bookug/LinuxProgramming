/*=============================================================================
# Filename: defs.h
# Author: bookug 
# Mail: bookug@qq.com
# Last Modified: 2018-10-19 16:57
# Description: 
=============================================================================*/

#ifndef _MY_DEFS_H
#define _MY_DEFS_H

//#ifdef __cplusplus
//extern "C" {
//#endif

typedef struct{
  double x,y;
} point;

extern void input(point*);
extern void display(point*);
extern void func();

//#ifdef __cplusplus
//}
//#endif

#endif //_MY_DEFS_H

