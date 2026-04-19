#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "mylistlib.h"
#include "hashtable.h"
#include "hashfunc.h"
#include "utils.h"

FILE* Statfile = fopen("Files/Statfile.csv", "w");
FILE* Text     = fopen("Files/Text.txt", "r");

void Garbage_collect(void);

void Garbage_collect(void) {
    fclose(Statfile);
    fclose(Text);
    free(POISON);
}

int main() 
{
    atexit(Garbage_collect);

    Hashtab_t* hashtab = Hashtab_Ctor(1000, &hf_Checksum);

    char* text_buf = Read_file2buf(Text);
    Fill_Hashtable(hashtab, text_buf);

    printf("%s\n", Hashtab_Find(hashtab, "aardwolf"));

    Hashtab_Dtor(hashtab);
    free(text_buf);

    return 0;
}