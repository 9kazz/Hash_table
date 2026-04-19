#ifndef PREPARE_H
#define PREPARE_H

#include <stdio.h>

char* Read_file2buf(FILE* input_file, size_t* size_of_file);
void  Prepare_File (char* text_buf, size_t sizeof_file);


#define SAFE_CALLOC(name, size_of_buf, el_type)                                                             \
    el_type* temp_##name = (el_type*) calloc(size_of_buf, sizeof(el_type));                                 \
                                                                                                            \
    if (temp_##name == NULL)                                                                                \
        fprintf(stderr, "Allocation error of " #name " in %s (%s:%d)\n", __func__, __FILE__, __LINE__);     \
                                                                                                            \
    el_type* name = temp_##name;    
    
#define SAFE_FOPEN(name, file, mode)                                                                        \
    FILE* temp_##name = fopen(file, mode);                                                                  \
                                                                                                            \
    if (temp_##name == NULL)                                                                                \
        fprintf(stderr, "File opening error (" #name ") in %s (%s:%d)\n", __func__, __FILE__, __LINE__);    \
                                                                                                            \
    FILE* name = temp_##name; 

#define SAFE_FSTAT(describtor, ptr_to_stat_struct)                                                          \
    int stat_check_##file = fstat(describtor, ptr_to_stat_struct);                                          \
                                                                                                            \
    if (stat_check_##file == -1)                                                                            \
        fprintf(stderr, "File stat error in function %s in %s:%d\n", __func__, __FILE__, __LINE__);         \

#define SAFE_FREAD(buffer, size_of_elem, count_of_elem, file)                                                                               \
    int fread_check_##file = fread(buffer, size_of_elem, count_of_elem, file);                                                              \
                                                                                                                                            \
    if (fread_check_##file < count_of_elem)                                                                                                 \
        fprintf(stderr, "Warning: error in fread or fread did not read any symbols (%s in %s:%d)\n", __func__, __FILE__, __LINE__);         \



#endif