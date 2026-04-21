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

    Hashtab_t* hashtab = Hashtab_Ctor(4000, &hf_Crc32);

    char*  text_buf = Read_file2buf(Text);
    char** word_buf = Create_Wordbuf(text_buf);

    Fill_Hashtable(hashtab, word_buf);

    for (int cnt = 0; cnt < 100; cnt++)
        UnitTest_Hashtab_Find(hashtab, word_buf); // try to find 120k words

    Hashtab_Dtor(hashtab);
    free(text_buf);
    free(word_buf);

    // system("/usr/bin/python /home/gkazz/prog/hashtable/Hash_table/MakeHist.py");

    return 0;
}