#ifndef UTILS_H
#define UTILS_H

#include <stdio.h>
#include <stdlib.h>

#include "mylistlib.h"
#include "hashtable.h"

int Collect_Stat(HashData_t obj, size_t table_idx);

int rol(int num, int bits2rol);
int ror(int num, int bits2rol);

#endif