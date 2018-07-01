// C source file
/***********************************************
# Copyright (c) 2018, Wuhan
# All rights reserved.
#
# @Filename: gtstack.c
# @Version：V1.0
# @Author: Frank Liu - frankliu624@gmail.com
# @Description: ---
# @Create Time: 2018-06-30 23:10:41
# @Last Modified: 2018-06-30 23:10:41
***********************************************/
#include <stdlib.h>
#include "../include/gtstack.h"

struct GtStack {
    size_t max;
    int index;
    void** elems;
};

GtStack* gt_stack_create(size_t max)
{
    GtStack* out = (GtStack*)malloc(sizeof(GtStack));
    if(!out)    exit(GT_ERROR_OUTMEM);

    if(max<=0)  max = 16;   //默认16
    out->elems = (void**)calloc(max, sizeof(void*));
    if(!out->elems)  exit(GT_ERROR_OUTMEM);

    out->max = max;
    out->index = 0;
    return out;
}

int gt_stack_push(GtStack* in, void* data)
{
    if(in->index >= in->max)    return GT_ERROR_FULL;
    in->elems[in->index++] = data;
    return GT_OK;
}

int gt_stack_pop(GtStack* in, void** data)
{
    if(in->index <= 0)  return GT_ERROR_EMPTY;

    *data = in->elems[--in->index];
    return GT_OK;
}

void gt_stack_destroy(GtStack** in)
{
    if(*in)
    {
        GtStack* stack = *in;
        free(stack->elems);
        free(stack);
        *in = NULL;
    }
}
