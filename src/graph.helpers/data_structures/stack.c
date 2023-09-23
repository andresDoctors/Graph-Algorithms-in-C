#include "stack.h"

#include <stdlib.h>


void push(stack_t* p_stack, i32 elem) {
    StackNode* new_node = malloc(sizeof(StackNode));
    new_node->next = *p_stack;
    new_node->elem = elem;
    *p_stack = new_node;
}

i32 pop(stack_t* p_stack) {
    stack_t old_stack = *p_stack;
    i32 elem = old_stack->elem;
    *p_stack = old_stack->next;
    free(old_stack);
    return elem;
}
