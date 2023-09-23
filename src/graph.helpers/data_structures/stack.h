#ifndef STACK_H
#define STACK_H


#include "../../../types/integers.h"


typedef struct StackNode {
    i32 elem;
    struct StackNode* next;
} StackNode;

typedef StackNode* stack_t;


void push(stack_t* p_stack, i32 elem);
i32  pop (stack_t* p_stack);


#endif
