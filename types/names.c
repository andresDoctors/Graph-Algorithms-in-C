#include "names.h"
#ifdef  USE_STRINGS_AS_NAME_T

#include <string.h>
#include <stdlib.h>

void name_destroy(name_t name) {
    free(name);
}

i32 name_is_empty(name_t name) {
    return name == NULL;
}

name_t name_copy(name_t name) {
    i32 n = strlen(name) + 1;
    name_t copy = malloc(n * sizeof(char));
    strcpy(copy, name);
    return copy;
}

/*djb2*/
u64 name_hash(name_t name) {
    unsigned char* str = (unsigned char*) name;

    i32 c;
    u64 hash = 5381;

    while((c = *str++))
        hash = ((hash << 5) + hash) + c;

    return hash;
}

int name_cmp(name_t name1, name_t name2) {
    return strcmp(name1, name2);
}


#endif
