#include <stdio.h>
#include <stdlib.h>
#include <assert.h>

#include "mylistlib.h"
#include "hashtable.h"
#include "utils.h"

int Collect_Stat(HashData_t obj, size_t table_idx) {
    assert(obj);
    return fprintf(Statfile, "%s\t%d\n", obj, table_idx);
}

int rol(int num, int bits2rol) 
{
    int result = num;

    if (bits2rol == 0) {

    } else if (bits2rol < 0) {
        result = ror(num, -bits2rol);

    } else {
        result = (num << bits2rol) | (num >> (sizeof(num) * 8 - bits2rol));
    }

    return result;       
}

int ror(int num, int bits2rol) 
{
    int result = num;

    if (bits2rol == 0) {

    } else if (bits2rol < 0) {
        result = rol(num, -bits2rol);

    } else {
        result = (num >> bits2rol) | (num << (sizeof(num) * 8 - bits2rol));
    }

    return result;       
}