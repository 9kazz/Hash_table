#ifndef UTILS_H
#define UTILS_H

#include <stdio.h>
#include <stdlib.h>

#include "mylistlib.h"
#include "hashtable.h"

HashErr_t Fill_Hashtable(Hashtab_t* hashtab, char* text_buf);
char*     Read_file2buf (FILE* input_file);
int       Collect_Stat  (HashData_t obj, size_t table_idx);
int       skip_space    (char** str);

int rol(int num, int bits2rol);
int ror(int num, int bits2rol);

#endif