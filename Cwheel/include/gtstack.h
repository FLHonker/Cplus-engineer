// C/C++ header file
/***********************************************
# Copyright (c) 2018, Wuhan
# All rights reserved.
#
# @Filename: gtstack.h
# @Version：V1.0
# @Author: Frank Liu - frankliu624@gmail.com
# @Description: 如非必要，在头文件中只暴露api，任何和实现相关的具体函数，
                变量和结构体尽量不要在头文件中暴露。未来如果你想闭源，
                实现只提供so库，操作灵活性更大。
                
                定义几种基本的栈的操作，包括创建，销毁，push和pop。
# @Create Time: 2018-06-30 22:58:23
# @Last Modified: 2018-06-30 22:58:23
***********************************************/
#ifndef GTLIB_GTSTACK_H
#define GTLIB_GTSTACK_H
#ifdef __cplusplus
extern "C" {
#endif

#include "gttypes.h"
typedef struct GtStack GtStack;

GT_API GtStack* gt_stack_create(size_t);
GT_API int gt_stack_push(GtStack*, void*);
GT_API int gt_stack_pop(GtStack*, void**);
GT_API void gt_stack_destroy(GtStack**);

#ifdef __cplusplus 
}
#endif 

#endif
