#ifndef HASHFUNC_H
#define HASHFUNC_H

#include "hashtable.h"

int hf_Const_value (HashData_t obj);
int hf_First_letter(HashData_t obj);
int hf_Word_len    (HashData_t obj);
int hf_Checksum    (HashData_t obj);
int hf_Rol         (HashData_t obj);
int hf_Crc32       (HashData_t obj);
#endif