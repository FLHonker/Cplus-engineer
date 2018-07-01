// C source file
/***********************************************
# Copyright (c) 2018, Wuhan
# All rights reserved.
#
# @Filename: main.c
# @Version：V1.0
# @Author: Frank Liu - frankliu624@gmail.com
# @Description: Test my GT_data_structure
# @Create Time: 2018-07-01 14:49:50
# @Last Modified: 2018-07-01 14:49:50
***********************************************/
#include <stdio.h>
#include <stdlib.h>
#include "include/gtstack.h"

int main()
{
    GtStack* stack = gt_stack_create(10);
    gt_stack_push(stack, "顺丰");
    gt_stack_push(stack, "韵达");
    gt_stack_push(stack, "申通");
    gt_stack_push(stack, "圆通");

    char* p;
    int err;
    while((err = gt_stack_pop(stack, (void**)&p)) == GT_OK)
    {
        printf("pop: %s\n", p);
    }
    gt_stack_destroy(&stack);

    return 0;
}
