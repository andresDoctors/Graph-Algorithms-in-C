#ifndef DICT_H
#define DICT_H


#include "../../../types/names.h"
#include "../../../types/integers.h"


typedef struct TreeNode {
    i32    idx;
    name_t name;
    struct TreeNode* left;
    struct TreeNode* right;
} TreeNode;

typedef TreeNode* tree_t;

typedef struct DictSt {
    i32 size;
    i32 capacity;
    tree_t* trees;
} DictSt;

typedef DictSt* dict_t;


dict_t dict_new(i32 capacity);
void dict_destroy(dict_t hash);
i32 dict_get_idx(dict_t dict, name_t name);


#endif
