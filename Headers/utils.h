#ifndef UTILS_H
#define UTILS_H

#include <stdio.h>
#include <stdlib.h>

#include "mylistlib.h"
#include "hashtable.h"

HashErr_t Fill_Hashtable       (Hashtab_t* hashtab, char** word_buf);
HashErr_t UnitTest_Hashtab_Find(Hashtab_t* hashtab, char** word_buf);

char*     Read_file2buf (FILE* input_file);
char**    Create_Wordbuf(char* text_buf);
int       Collect_Stat  (HashData_t obj, size_t table_idx);
int       skip_space    (char** str);

#endif