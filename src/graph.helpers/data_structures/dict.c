#include <stdlib.h>

#include "dict.h"


void tree_destroy(tree_t tree) {
    if(tree == NULL) return;

    tree_destroy(tree->left);
    tree_destroy(tree->right);
    name_destroy(tree->name);
    free(tree);
}

tree_t tree_node_new(name_t name, i32 idx) {
    tree_t new_tree = malloc(sizeof(TreeNode));

    new_tree->left  = NULL;
    new_tree->right = NULL;
    new_tree->idx   = idx;
    new_tree->name  = name_copy(name);

    return new_tree;
}

void tree_add(tree_t* p_tree, name_t name, i32 idx) {

    if(*p_tree == NULL) {
        *p_tree = tree_node_new(name, idx);
        return;
    }

    tree_t tree = *p_tree;
    i32 cmp = name_cmp(tree->name, name);
    if      (cmp < 0) { return tree_add(&(tree->left),  name, idx); }
    else if (cmp > 0) { return tree_add(&(tree->right), name, idx); }
}

i32 tree_get_idx(tree_t tree, name_t name) {
    if(tree == NULL) return -1;

    i32 cmp = name_cmp(tree->name, name);
    if      (cmp == 0)    { return tree->idx; }
    else if (cmp <  0)    { return tree_get_idx(tree->left,  name); }
    else /* (cmp >  0) */ { return tree_get_idx(tree->right, name); }
}

dict_t dict_new(i32 capacity) {
    dict_t new_dict = malloc(sizeof(DictSt));
    new_dict->capacity = capacity;
    new_dict->size = 0;
    new_dict->trees = calloc(capacity, sizeof(tree_t));
    return new_dict;
}

void dict_destroy(dict_t dict) {
    for(i32 i = 0; i < dict->capacity; i++)
        tree_destroy(dict->trees[i]);
    free(dict->trees);
    free(dict);
}

i32 dict_get_idx(dict_t dict, name_t name) {

    i32 k = name_hash(name) % dict->capacity;
    tree_t* p_tree = &(dict->trees[k]);

    i32 idx = tree_get_idx(*p_tree, name);
    if(idx == -1) {
        idx = dict->size++;
        tree_add(p_tree, name, idx);
    }

    return idx;
}
