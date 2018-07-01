// C/C++ header file
/***********************************************
# Copyright (c) 2018, Wuhan
# All rights reserved.
#
# @Filename: gttypes.h
# @Version：V1.0
# @Author: Frank Liu - frankliu624@gmail.com
# @Description: 定义一些常量
# @Create Time: 2018-06-30 22:55:27
# @Last Modified: 2018-06-30 22:55:27
***********************************************/
// 最外层的宏ifndef define endif是用来告诉编译器不要重复include我，
// 里面的extern c {}层次是通知c++编译器用c的方式处理。
#ifndef GTLIB_GTTYPES_H
#define GTLIB_GTTYPES_H

#ifdef __cplusplus
extern "C" {
#endif

#define GT_API          extern
#define GT_OK           (0)
#define GT_ERROR_OUTMEM (-1)
#define GT_ERROR_FULL   (-2)
#define GT_ERROR_EMPTY  (-3)

typedef unsigned long size_t;

#ifdef __cplusplus
}
#endif 

#endif
