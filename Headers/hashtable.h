#ifndef HASHTABLE
#define HASHTABLE

#include <stdio.h>
#include "mylistlib.h"

typedef ListData_t  HashData_t;

#define CAP(hashtab)  (hashtab)->capacity
#define TAB(hashtab)  (hashtab)->table
#define FUNC(hashtab) (hashtab)->hashfunc

const size_t List_Capacity = 16;

enum HashErr {
    no_errors = 0
};

struct Hashtab_t {
    size_t capacity;
    List_t** table;
    int (*hashfunc)(HashData_t);
};

Hashtab_t* Hashtab_Ctor   (size_t capacity, int (*hashfunc)(HashData_t));
HashErr    Hashtab_Dtor   (Hashtab_t* hashtab);

HashErr    Hashtab_Addelem(Hashtab_t* hashtab, HashData_t obj);
List_t*    Hashtab_Getlist(Hashtab_t* hashtab, const HashData_t obj);

#endif