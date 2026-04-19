#include <stdio.h>
#include <stdlib.h>
#include <assert.h>

#include "mylistlib.h"
#include "hashtable.h"
#include "utils.h"

Hashtab_t* Hashtab_Ctor(size_t capacity, int (*hashfunc)(HashData_t)) {
    assert(hashfunc);

    Hashtab_t* hashtab = (Hashtab_t*) calloc(1, sizeof(Hashtab_t));

    CAP (hashtab) = capacity;
    TAB (hashtab) = (List_t**) calloc(capacity, sizeof(TAB(hashtab)[0]));
    FUNC(hashtab) = hashfunc;

    for (size_t tabcell = 0;  tabcell < capacity;  tabcell++) {
        TAB(hashtab)[tabcell] = List_Ctor(20);
    }

    return hashtab;
}

HashErr_t Hashtab_Dtor(Hashtab_t* hashtab) {
    assert(hashtab);

    for (size_t tabcell = 0;  tabcell < CAP(hashtab);  tabcell++) {
        List_Dtor( TAB(hashtab)[tabcell] );
    }

    free( TAB(hashtab) );
    free(hashtab);
    
    return no_errors;
}

HashErr_t Hashtab_Addelem(Hashtab_t* hashtab, HashData_t obj) {
    assert(hashtab);
    assert(obj);

    size_t hash      = (size_t) FUNC(hashtab)(obj);
    size_t table_idx = hash % CAP(hashtab);
    
    List_Insert_Tail(TAB(hashtab)[table_idx],  obj);
    Collect_Stat(obj, table_idx);

    return no_errors;
}

HashData_t Hashtab_Find(Hashtab_t* hashtab, const HashData_t obj) {
    assert(hashtab);
    assert(obj);

    size_t hash = (size_t) FUNC(hashtab)(obj);
    List_t* list = TAB(hashtab)[hash % CAP(hashtab)];

    HashData_t result = List_Find(list, obj);

    if (result == NULL)  return POISON;
    
    return result;
}