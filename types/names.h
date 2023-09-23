#ifndef NAMES_H
#define NAMES_H

//#define USE_STRINGS_AS_NAME_T
#ifdef  USE_STRINGS_AS_NAME_T

typedef char* name_t;
typedef char* name_address_t;
#define name_address(NAME) NAME
#define name_declare_tmp(__identifier) char __identifier[128]

#define PRINAME "s"
#define SCNNAME "s"

void   name_destroy(name_t name);
i32    name_is_empty(name_t name);
name_t name_copy(name_t name);
u64    name_hash(name_t name);
i32    name_cmp(name_t name1, name_t name2);

#else

#include <stdint.h>
#include <inttypes.h>

typedef int_least64_t  name_t;
typedef int_least64_t* name_address_t;
#define name_address(NAME) &NAME
#define name_declare_tmp(__identifier) int_least64_t __identifier

#define PRINAME PRIdLEAST64
#define SCNNAME SCNdLEAST64

#define name_destroy(NAME)
#define name_is_empty(NAME)     1
#define name_copy(NAME)         NAME
#define name_hash(NAME)         NAME
#define name_cmp(NAME1, NAME2) (NAME1 > NAME2) - (NAME1 < NAME2)


#endif

#endif
