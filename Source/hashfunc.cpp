#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>

#include "mylistlib.h"
#include "hashtable.h"
#include "hashfunc.h"
#include "utils.h"

int hf_Const_value(HashData_t obj) {
    assert(obj);
    return 1;
}

int hf_First_letter(HashData_t obj) {
    assert(obj);
    return obj[0];
}

int hf_Word_len(HashData_t obj) {
    assert(obj);
    return (int) strlen(obj);
}

int hf_Checksum(HashData_t obj) {
    assert(obj);

    int checksum  = 0;
    char cur_char = obj[0];

    for (size_t char_cnt = 0; cur_char != '\0'; char_cnt++)
    {
        checksum += cur_char;
        cur_char = obj[char_cnt];
    }

    return checksum;
}

int hf_Rol(HashData_t obj) {
    assert(obj);

    int  result   = 0;
    char cur_char = obj[0];
    
    for (size_t char_cnt = 0; cur_char != '\0'; char_cnt++)
    {
        cur_char = obj[char_cnt];
        result = rol(result, 1);
        result |= cur_char;
    }

    return result;
}

int hf_Crc32(HashData_t obj) {
    assert(obj);

    size_t obj_len = strlen(obj);

    const int polynom = 0xEDB88320;

    int crc_table[256] = {0};
    int crc = 1;

    for (size_t byte_cnt = 0; byte_cnt < 256; byte_cnt++)
    {
        crc = 1;

        for (size_t bit_cnt = 0; bit_cnt < 8; bit_cnt++)
            crc = (crc & 1) ?  (crc >> 1) ^ polynom  :  crc >> 1;
        
        crc_table[byte_cnt] = crc;
    }

    crc = 0xFFFFFFFF;

    for (size_t obj_byte = 0; obj_byte < obj_len; obj_byte++)
        crc = crc_table[ (crc ^ obj[obj_byte]) & 0xFF ] ^ (crc >> 8);

    return ~crc;
}