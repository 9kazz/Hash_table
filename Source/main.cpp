#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "mylistlib.h"
#include "hashtable.h"
#include "hashfunc.h"

FILE* Statfile = fopen("Statfile.csv", "w");

void Garbage_collect(void);

void Garbage_collect(void) {
    fclose(Statfile);
    free(POISON);
}

int main() 
{
    atexit(Garbage_collect);

    char* str = strdup("abc");

    Hashtab_t* hashtab = Hashtab_Ctor(1000, &hf_Crc32 );

    Hashtab_Addelem(hashtab, str);

    printf("%s\n", DATA(Hashtab_Getlist(hashtab, "abc"))[get_tail(Hashtab_Getlist(hashtab, "abc"))] );

    Hashtab_Dtor(hashtab);
    free(str);

    return 0;
}