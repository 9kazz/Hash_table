#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>
#include <ctype.h>

#include "mylistlib.h"
#include "hashtable.h"
#include "utils.h"

HashErr_t Fill_Hashtable(Hashtab_t* hashtab, char* text_buf) {
    assert(hashtab);
    assert(text_buf);

    char* word_start = text_buf;
    char* next_char  = text_buf;

    while (*next_char != '$') 
    {
        word_start = next_char;

        while ( ! isspace(*next_char) )
            next_char++ ;

        *next_char = '\0';
        next_char++ ;
        skip_space(&next_char);
        
        Hashtab_Addelem(hashtab, word_start);
    }

    return no_errors;
}

char* Read_file2buf(FILE* input_file) {
    assert(input_file);

    struct stat file_info;

    int file_descriptor = fileno(input_file);

    SAFE_FSTAT(file_descriptor, &file_info);

    size_t size_of_file = file_info.st_size;

    SAFE_CALLOC(text_buf, size_of_file + 2, char);

    SAFE_FREAD(text_buf, sizeof(char), size_of_file, input_file);

    text_buf[size_of_file]     = ' ';
    text_buf[size_of_file + 1] = '$';

    return text_buf;
}

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

int skip_space(char** str) {
    assert(str);
    assert(*str);
    
    int count_of_space = 0;

    while( isspace(**str) ) 
    {
        count_of_space++ ;
        (*str)++ ;
    }

    return count_of_space;
}